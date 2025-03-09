#define PAGE_SZ	0x1000
#define PAGE_MASK (~(PAGE_SZ-1))
#define PAGE_ALIGN(x)		(((x) + PAGE_SZ-1) & PAGE_MASK)
#define _align(v, align)	(((v) + ((align)-1)) & ~((align)-1))
