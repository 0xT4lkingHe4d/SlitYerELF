#include <linux/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <iostream>
#include <elflib/elf.hpp>

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

#define ALIGN(n, sz)        ((sz & ~((n)-1)) + (n))
#define __PAGE_ALIGN(sz)    ((sz & ~0xfff) + 0x1000)

void *map_anon(__u64 sz);
void die(char *str);

enum class PackPtrT { Elf, SC, HEAP, MMAP };
#define PPTR_T(x)   (x >= 0x1000 ? PackPtrT::MMAP : PackPtrT::HEAP)

template <typename T> struct acon_st {
    T       *ptr;
    __u64   num;
};

struct mmsz_t {
    PackPtrT    t;
    void        *mem;
    __u64       sz, alloc_size, off;
    
    ~mmsz_t() {
        free_mem();
    }
    void free_mem() { free_mem(t, mem, alloc_size); }
    void free_mem(PackPtrT type, void *ptr, __u64 sz) {
        if (type==PackPtrT::HEAP) free(ptr);
        if (type==PackPtrT::MMAP) munmap(ptr, sz);
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
    void extend(__u64 add) {
        __u64 size = sz + add;
        PackPtrT type = PPTR_T(size);
        __u64 asz = alloc_size;
        void *ptr = _alloc(type, size);
        memcpy(ptr, mem, sz);

        free_mem(t, mem, asz);
        t   = type;
        mem = ptr;
        sz  = size;
    }
    
    bool merge(__u64 off, mmsz_t *mm) {
        if (!mm || !mm->mem || !mm->sz)
            return false;
        __u64 size = sz;
        extend(mm->sz);
        
        memcpy(mem + off + mm->sz, mem + off, size - off);
        memcpy(mem + off, mm->mem, mm->sz);

        return true;
    }
    template <typename T> acon_st<T> ptr() {
        return acon_st<T>{
            .ptr = reinterpret_cast<T*>(mem),
            .num = sz / sizeof(T)
        };
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