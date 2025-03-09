MAKE=make
CC=gcc
PRINT=echo
BDIR := ./build
OUT  := ${BDIR}/main
STUB := "$(shell pwd)/${BDIR}/stub"

.PHONY: all
all: clean main

FILE ?= ./specimen/xx

run: all
	rm -f ./ret.o
	@echo "===[++] Running\n"
	${OUT} -i ${FILE} -o ./ret.o --modify ./specimen/yy

FLAGS := -g -w
DISAS_FILES := ./disass/src/*.c ./disass/instr/*.c
PASS_FILES  := ./src/*.c ./src/elf/*.c ./src/utils/*.c ./src/llist/*.c ./src/rel_instr/*.c ./src/instr/*.c ./src/pack/*.c ./src/mods/*.c
FILES := ./main.c $(DISAS_FILES) $(RELF_FILES) $(PASS_FILES)

.PHONY: main
main:
	@$(CC) $(FLAGS) $(FILES) -o ${OUT}

.PHONY: stub
stub:
	@mkdir -p ${BDIR}
	@echo "[~] Compiling the Stub"
	@$(MAKE) -C ./light/stub/ all STUB_OUTPUT=$(STUB)

.PHONY: clean
clean:
# 	@rm -f ./build/main
	@clear
	@#echo "Cleaning Build Folder - " $(BDIR)
	@#@rm ${BDIR}/*.o ${OUT}
