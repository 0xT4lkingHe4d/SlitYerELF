#include <stdio.h>
#include <linux/i2c-dev.h>

__attribute__((constructor)) long long oi(int arg) {
	puts("DIS is INIt");
	return 0xdeadcafe;
}

void main() {
	puts("DIS is Main");
	oi(0x10);
}
