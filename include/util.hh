#include <linux/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <iostream>

#ifndef FREAK_UTILS_H
#define FREAK_UTILS_H
#define p(s)    std::cout << s << std::endl

// #define _crossed_(a, sz1, b, sz2)    ((a >= b && a < b + sz2) || (b >= a && b < a + sz1))

typedef struct {
    char *input;
    char *merge;
    char *output;
} arg_list;

#define err(s) { die(s); }
#define errf(s, ...) {                              \
    __u64 sz = snprintf(NULL, 0, s, __VA_ARGS__);   \
    char *str = new char[sz];                       \
    sprintf(str, s, __VA_ARGS__);                   \
    die(str);                                       \
}

#define each(ll, e) for (auto& e : ll)

#define __PAGE_ALIGN(sz)    ((sz & ~0xfff) + 0x1000)

void *map_anon(__u64 sz);
void die(char *str);

enum class PackPtrT { Elf, SC, HEAP, MMAP };
#define PPTR_T(x)   (x >= 0x1000 ? PackPtrT::MMAP : PackPtrT::HEAP)

struct mmsz_t {
    PackPtrT    t;
    void        *mem;
    __u64       sz, alloc_size, off;
    
    ~mmsz_t() {
        if (t==PackPtrT::HEAP) free(mem);
        if (t==PackPtrT::MMAP) munmap(mem, alloc_size);
    }
    
    bool is_alloc() {
        return t != PackPtrT::HEAP && t != PackPtrT::MMAP;
    }
    void alloc() {
        if (!is_alloc()) {
            void *dat = _alloc((t = PPTR_T(sz)), sz);
            memcpy(dat, mem, sz);
            mem = dat;
        }
    }

protected:
    void *_alloc(PackPtrT type, __u64 size) {
        switch (type) {
            case PackPtrT::HEAP:    return malloc(size);
            case PackPtrT::MMAP:    return map_anon(alloc_size = __PAGE_ALIGN(size));
        }
        return NULL;
    }
};

struct mmsz_tup : public mmsz_t {
    mmsz_tup() = delete;
    mmsz_tup(PackPtrT type, __u64 size) : mmsz_t{type, NULL, size} {
        mem = _alloc(t, size);
    }
    mmsz_tup(__u64 size) : mmsz_t{PPTR_T(size), NULL, size} {
        mem = _alloc(t, size);
    }
};
#endif