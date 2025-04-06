#include <sys/mman.h>
#include "../include/util.hh"

void *map_anon(__u64 sz) {
    return mmap(0, sz, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
}

void die(char *str) {
    printf("[DEAD]  %s\n", str);
    printf("  - errno %u - %s\n", errno, strerror(errno));
    exit(-1);
}