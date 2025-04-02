#include "./include/pack.hh"

int main(int argc, char *argv[]) {
    char *in = argv[1], *out = argv[2];
    if (argc != 3) errf("usage %s <in> <out>", argv[0]);
    auto elf = new Elf(in);
    auto p = pack(elf);
    // p.shift(0x1b000, 0x50000);
    p.rel_exec();
    // const char sc[] = "\x6a\xff\x50\x57\x56\x52\x51\x6a\x00\x68\x44\x44\x44\x04\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x48\x89\xe6\xba\x05\x00\x00\x00\x0f\x05\xfe\x4c\x24\x38\x80\x7c\x24\x38\x00\x75\xe1\x58\x58\x59\x5a\x5e\x5f\x58";
    auto r = p.get_rel(elf, elf->ehdr->e_entry);
    // r->_rel_(RelT::BufInsert, (void*)sc, elf->ehdr->e_entry, sizeof(sc)-1);
    if (p.make(out) == -1) errf("Failed to make %s", out);

    // __u64 y[4] = {_WORD_, _WORD_, 0, 0};
    // printf("%x %i LONG\n", xin[1]->size(), x.get((__u8*)mysc, xin, y));
}