# SlitYerELF

A (so far) PoC project for static binary instrumentation
Containing a x86_64 disassembler, ELF parser, pack(split an elf into patches, move them around/resize them and relocate dynamic & rela entries to fit the new output file), xtc(find each instruction with same name and different operands - eg. mov imm8 and mov imm32) and rel(relocate each instruction in each "patch" to point where the destination is now)

-This is just a PoC - 
"Shut up and look at the code" ;)
