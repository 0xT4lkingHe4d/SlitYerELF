#include "./include/pack.hh"
#include "./include/util.hh"

int main(int argc, char *argv[]) {
    arg_list al = {0};
    for (int i = 0; i < argc; i++) {
        if (!strncmp(argv[i], "-i", 3) || !strncmp(argv[i], "--input", 8))
            al.input = argv[++i];
        if (!strncmp(argv[i], "-m", 3) || !strncmp(argv[i], "--merge", 8))
            al.merge = argv[++i];
        if (!strncmp(argv[i], "-o", 3) || !strncmp(argv[i], "--output", 9))
            al.output = argv[++i];
    }

    if (!al.input || !al.merge || !al.output) {
        printf("  usage %s [OPTS]\n", argv[0]);
        printf("    -i, --input     input elf file\n");
        printf("    -m, --merge     ELF to merge with input\n");
        printf("    -o, --output    output filename\n");
        exit(0);
    }

    auto s_elf = new Elf(al.input);
    auto m_elf = new Elf(al.merge);

    auto p = pack(s_elf);
    p.rel_exec();
    p.merge_elf(m_elf);
    char *buf = new char[0x500];
    memset(buf, 0x90, 0x500);
    const char sc[] = "\x6a\xff\x50\x57\x56\x52\x51\x6a\x00\x68\x41\x43\x45\x04\xb8\x01\x00\x00\x00\xbf\x01\x00\x00\x00\x48\x89\xe6\xba\x05\x00\x00\x00\x0f\x05\xfe\x4c\x24\x38\x80\x7c\x24\x38\x00\x75\xe1\x58\x58\x59\x5a\x5e\x5f\x58";
    auto r = p.get_rel(s_elf, s_elf->ehdr->e_entry);
    // const char sc2[] = "\x48\xc7\x05\x7c\x2e\x00\x00\xef\xbe\xad\xde";
    r->_rel_(r->_rx_(0x10c0)->ll, RelT::BufInsert,  (void*)"\xe9\x10\x00\x00\x00~R3MainINL1gh7~\x90", 0x10c0, 0x15);
    // If done with shellcode - needs `tokens`
    auto rx = r->_rx_(s_elf->ehdr->e_entry);
    r->_rel_(rx->ll, RelT::BufInsert, (void*)buf, s_elf->ehdr->e_entry, 0x500);
    // auto rx = r->_rel_(RelT::InsInsert, (void*)"\xe9\x00\x00\x00\x00", 0x118b, 5);
    // r->hook(rx, 0, s_elf, 0x1149);

    // r->_rel_(RelT::BufInsert,  (void*)sc2, 0x1158, 11);
    // r->_rel_(RelT::BufInsert,  (void*)"~R3MainINL1gh7~", 0x1188, 15);

    if (p.make(al.output) == -1) errf(" [-] Failed to make %s", al.output);
    printf(" [+] Output file - %s\n", al.output);
}