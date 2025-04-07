#include <stdio.h>

#define MERGE_MAGIC "_MRG_"
#define F_MERGE_PRE		"h"
#define F_MERGE_POST	"H"
#define MRG(h, name) __attribute__((section(MERGE_MAGIC"."h"_"name)))
#define MRG_PRE(name)	MRG(F_MERGE_PRE, name)
#define MRG_POST(name)	MRG(F_MERGE_POST, name)


MRG_PRE("oi") void __oi() {
	puts("FROM PASS!");
}
