obj = reg_table.o disass.o pfx.o utils.o sym.o x86_64_tabl.o modrm.o reconstruct.o x_tuple.o x86_tabl.o operand.o uapi.o elf.o
BDIR = ./build
CFLAGS = -w -fPIC

.PHONY: all
all: $(obj)
	cd $(BDIR); ar rvs libx86binary.a $^

%.o: disass_x86/instr/%.c
	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

%.o: disass_x86/src/%.c
	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

%.o: elf/%.c
	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

# %.o: utils/src/%.c
# 	gcc -c $< -o $(BDIR)/$@ $(CFLAGS)

