#include <stdio.h>

static void *hey = NULL;

/*int oi() {
	puts("OI!");
	return 0xdead;
}*/

void main() {
	hey = 0x30;
	puts("HEY!");
	//printf("%lx %lx\n", hey, oi());
}
