#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "./include/main.h"

static void init_arguments(int argc, __u8 **argv, struct arg_lst *lst) {
	for (__u64 i = 0; i < argc; i++) {
		__u8 *arg = argv[i];
		if (!strncmp(arg, "-i", 2)) {
			lst->input = argv[++i];
		} else if (!strncmp(arg, "-o", 2)) {
			lst->output = argv[++i];
		} else if (!strncmp(arg, "--modify", 8)) {
			lst->modif = argv[++i];
		}
	}
}

void main(int argc, __u8 *argv[]) {
	struct arg_lst args = {0};
	init_arguments(argc, argv, &args);
	if (!args.input || !args.output) return -1;

	if (file_exists(args.output))
		FDIE("[-] Output file %s exists\n", args.output);

	return do_init(&args);
}
