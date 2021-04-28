/// @file    mmpool.c
/// @author  moyin(moyin1004@163.com)
/// @data    2021-04-28 12:48:12

#include "mmpool.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief 分配小块内存
 * @param pool
 * @param size
 * @return 内存地址
 */
static void *mp_alloc_block(struct mp_pool_s *pool, size_t size) {
    unsigned char *m;
    struct mp_node_s *h = pool->head;
    // 内存池的一个小块所占的内存大小
    size_t psize = (size_t)(h->end - (unsigned char *)h);

    int ret = posix_memalign((void **)&m, MP_ALIGNMENT, psize);
    if (ret) return NULL;

    struct mp_node_s *p, *new_node, *current;
    new_node = (struct mp_node_s*)m;

    new_node->end = m + psize;
    new_node->next = NULL;
    new_node->failed = 0;

    // last指向已使用的内存
    m += sizeof(struct mp_node_s);
    m = mp_align_ptr(m, MP_ALIGNMENT);
    new_node->last = m + size;

    current = pool->current;
    // 每块最后剩余的内存，分配4次都失败则不在使用，直接略过
    for (p = current; p->next; p = p->next) {
        if (p->failed++ > 4) {
            current = p->next;
        }
    }
    p->next = new_node;
    pool->current = current ? current : new_node;

    return m;
}

/**
 * @brief 分配大块内存，超过一页
 * @param pool
 * @param size
 * @return 内存地址
 */
static void *mp_alloc_large(struct mp_pool_s *pool, size_t size) {
    void *p = malloc(size);
    if (p == NULL) return NULL;

    // 找到一个位置管理新分配的内存空间
    size_t n = 0;
    struct mp_large_s *large;
    for (large = pool->large; large; large = large->next) {
        if (large->alloc == NULL) {
            large->alloc = p;
            return p;
        }
        if (n++ > 3) break;
    }

    // 大块的头结点
    large = (struct mp_large_s *)mp_alloc(pool, sizeof(struct mp_large_s));
    if (large == NULL) {
        free(p);
        return NULL;
    }
    large->alloc = p;
    large->next = pool->large;
    pool->large = large;

    return p;
}

struct mp_pool_s *mp_create_pool(size_t size) {
    struct mp_pool_s *pool;
    int ret = posix_memalign((void **)&pool, MP_ALIGNMENT,
                             size + sizeof(struct mp_pool_s) + sizeof(struct mp_node_s));
    if (ret) {
        return NULL;
    }

    pool->max = (size < MP_MAX_ALLOC_FROM_POOL) ? size : MP_MAX_ALLOC_FROM_POOL;
    pool->current = pool->head;
    pool->large = NULL;

    pool->head->last = (unsigned char *)pool + sizeof(struct mp_pool_s) + sizeof(struct mp_node_s);
    pool->head->end = pool->head->last + size;

    pool->head->failed = 0;

    return pool;
}

void mp_destory_pool(struct mp_pool_s *pool) {
    if (!pool) return ;

    // 释放大块
    struct mp_large_s *large = NULL;
    for (large = pool->large; large; large = large->next) {
        if (large->alloc) free(large->alloc);
    }

    // 释放小块
    struct mp_node_s *h = pool->head->next;
    struct mp_node_s *next = NULL;
    while (h) {
        next = h->next;
        free(h);
        h = next;
    }
    free(pool);
}

void mp_reset_pool(struct mp_pool_s *pool) {
    if (!pool) return ;
    // 释放大块
    struct mp_large_s *large = NULL;
    for (large = pool->large; large; large = large->next) {
        if (large->alloc) free(large->alloc);
    }
    pool->large = NULL;

    // 恢复小块
    struct mp_node_s *h;
    for (h = pool->head; h; h = h->next) {
        h->last = (unsigned char *)h + sizeof(struct mp_node_s);
    }
}

void *mp_alloc(struct mp_pool_s *pool, size_t size) {
    if (!pool || size < 0) return NULL;
    if (size > MP_PAGE_SIZE) {
        return mp_alloc_large(pool, size);
    } else {
        struct mp_node_s *p = pool->current;
        unsigned char *m = p->last;
        if (p->end - m >= size) {  // 剩余内存够用
            p->last = m + size;
            return m;
        } else {                   // 不够
            return mp_alloc_block(pool, size);
        }
    } 
}

void *mp_calloc(struct mp_pool_s *pool, size_t size) {
    void *p = mp_alloc(pool, size);
    if (p) {
        memset(p, 0, size);
    }
    return p;
}

void mp_free(struct mp_pool_s *pool, void *p) {
    if (!pool) return ;
    struct mp_large_s *large = NULL;
    for (large = pool->large; large; large = large->next) {
        if (p == large->alloc) {
            free(large->alloc);
            large->alloc = NULL;
            return ;
        }
    }
}