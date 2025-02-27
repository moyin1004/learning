#pragma pack(4)

#include <cstdio>
#include <cstdlib>
#include <atomic>

// g++ mem_align.cpp -Wall -O2

struct TestAlign {
    int64_t a;
    // char b;
    int64_t c;
    char b;
};

struct TestAlign2 {
    char a;
    char b;
    int32_t c;
};

int main() {
    // glibc 的实现（Linux 默认 C 库）: malloc 在 64 位系统上默认对齐到 16 字节
    TestAlign ta1{1, 'a', 2};
    int8_t *p1 = (int8_t *)&ta1;
    printf("data: %c\n", *(char *)(p1 + 8));       // 应该是a
    printf("data: %ld\n", *(int64_t *)(p1 + 16));  // 应该是2
    printf("TestAlign size: %ld\n", sizeof(TestAlign));
    printf("TestAlign2 size: %ld\n", sizeof(TestAlign2));
    printf("atomic size: %ld\n", sizeof(std::atomic<int>));
    return 0;
}