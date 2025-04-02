#include "./include/pack.hh"

int main(int argc, char *argv[]) {
    char *in = argv[1], *out = argv[2];
    if (argc != 3) errf("usage %s <in> <out>", argv[0]);
    auto elf = new Elf(in);
    auto p = pack(elf);
    // p.shift(0x1b000, 0x50000);
    p.rel_exec();
    const char sc[] = "\x6a\xff\x50\x57\x56\x52\x51\x6a\x00\x68\x41\x43\x45\x2e"
                      "\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x48\x89\xe6\xba"
                      "\x05\x00\x00\x00\x0f\x05\xfe\x4c\x24\x38\x80\x7c\x24\x38"
                      "\x00\x75\xe1\x58\x58\x59\x5a\x5e\x5f\x58";
    auto r = p.get_rel(elf, elf->ehdr->e_entry);
    const char sc2[] = "\x48\xc7\x05\x7c\x2e\x00\x00\xef\xbe\xad\xde";
    r->_rel_(RelT::BufInsert,  (void*)"\xe9\x10\x00\x00\x00~R3MainINL1gh7~\x90", 0x10c0, 0x15);
    r->_rel_(RelT::BufInsert, (void*)sc, elf->ehdr->e_entry, sizeof(sc)-1);
    r->_rel_(RelT::BufInsert,  (void*)sc2, 0x1158, 11);
    r->_rel_(RelT::BufInsert,  (void*)"~R3MainINL1gh7~", 0x1188, 15);
    if (p.make(out) == -1) errf("Failed to make %s", out);
}
