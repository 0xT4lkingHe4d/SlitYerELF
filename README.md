# SlitYerELF
A (so far PoC) Linux ELF binary instrumentation engine for x86_64 ELF binaries containing it's own disassembler

### How it works
This project consists of 3 parts
#### [+] pack
Split an ELF into `patches` for each header which is also relocated/patched based of its type (eg. `DYNSYM`, `RELA`), in between `fill` patches are set. each header has its own type and is patched off it

#### [+] xtc
Find each instruction with the same mnemon ic and different operand types (eg. - `mov imm8` and `mov imm32`)

#### [+] rel_instr
Contains a linked-list of outlined instruction chunks - each instruction in each chunk is relocated so it points where the IMM is supposed to be now.

### Run
```
make
./main
./output
```
