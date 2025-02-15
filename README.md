# SlitYerELF
A (PoC) Static Binary Instrumentation engine for x86_64.
It can be used to add instructions/bytes in between the original binary's exec segment, pipe/relink instruction patches
(each instruction in a patch originating from ELF/memory pointing to ( A-B ) shall point to ...)

It divides a binary into patches (Headers, Fills/Data) modifies (resize/shift) them and reassembles the binary.

This has been a hobby project of mine for the past ~year - It also contains a working x86_64 disassembler (at `./lib-x86-binary`) made from scratch.

### Run
```
make
./main
./output
```
