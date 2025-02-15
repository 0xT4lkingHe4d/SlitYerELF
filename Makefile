obj = xtc.o rel_instr.o llist.o utils.o pack.o ptx.o
BDIR = ./build
CFLAGS = -w -fPIC
X86BINARY = -L$(PWD)/lib-x86-binary/build/ $(PWD)/lib-x86-binary/build/*.o -lx86binary
LDFLAGS = $(X86BINARY)

all: libx86binary
	gcc $(X86BINARY) ./main.c ./cfg/cfg.c ./src/instr/xtc.c ./src/pack/*.c ./src/rel/*.c ./utils/*.c -w -o ./main

library: libx86binary libslityerelf

.PHONY: libx86binary
libx86binary:
	make -C ./lib-x86-binary


.PHONY: libslityerelf
libslityerelf: $(obj)
	cd $(BDIR); ar rvs libslityerelf.a $^


%.o: utils/%.c
	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

%.o: src/instr/%.c
	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

%.o: src/rel/%.c
	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

%.o: src/pack/%.c
	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

