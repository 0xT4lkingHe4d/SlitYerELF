#include <stdio.h>

#define MERGE_ELF_FLAG "\xca\xfe\xad\xd1\xc7@"

#define MERGE_ELF(fn) __attribute__((section(MERGE_ELF_FLAG fn)))

MERGE_ELF("oi") void fn(int arg) {
	printf("You got fucked  %lx!\n", arg);
}

MERGE_ELF("main") void main_ovrd() {
	printf("DIS IS FROM ME MATE!\n");
}


void main() {
	fn(0x20);
}
