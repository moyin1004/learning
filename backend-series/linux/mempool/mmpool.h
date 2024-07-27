/// @file    mmpool.h
/// @author  moyin(moyin1004@163.com)
/// @data    2021-04-28 12:39:39

#ifndef __MMPOOL__
#define __MMPOOL__

#include <unistd.h>

#define MP_ALIGNMENT           32
#define MP_PAGE_SIZE           4096
#define MP_MAX_ALLOC_FROM_POOL (MP_PAGE_SIZE-1)

#define mp_align(n, alignment) (((n)+(alignment-1)) & ~(alignment-1))
#define mp_align_ptr(p, alignment) (void *)((((size_t)p)+(alignment-1)) & ~(alignment-1))

struct mp_large_s {
    struct mp_large_s *next;
    void *alloc;
};

struct mp_node_s {
    unsigned char *end;
    unsigned char *last;

    struct mp_node_s *next;
    size_t failed;
};

/**
 * 内存池，包含大块与小块
 */
struct mp_pool_s {
    size_t max;
    struct mp_node_s *current;
    struct mp_large_s *large;
    struct mp_node_s head[0];
};

struct mp_pool_s *mp_create_pool(size_t size);
void mp_destory_pool(struct mp_pool_s *pool);
void mp_reset_pool(struct mp_pool_s *pool);
void *mp_alloc(struct mp_pool_s *pool, size_t size);
void *mp_calloc(struct mp_pool_s *pool, size_t size);

/**
 * @brief 释放内存，仅限大块
 * @param pool
 * @param p    内存地址
 */
void mp_free(struct mp_pool_s *pool, void *p);

#endif