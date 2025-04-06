// #include "../include/bblock.hh"
#include "../include/pack.hh"
#define MERGE_MAGIC "_MRG_"
#define IS_MRG_MAGIC(p)		\
		(((char*)p)[0]=='_' && ((char*)p)[1]=='M' && ((char*)p)[2]=='R' && ((char*)p)[3]=='G' && ((char*)p)[4]=='_')

void pack::merge_elf(Elf *_elf) {
	std::shared_ptr<Elf> m_elf{_elf};
	auto bb = BBlock(m_elf);
	
	foreach_shdr(m_elf, sec) {
		__u8 *name = &m_elf->sec.str[sec->sh_name];
		if (IS_MRG_MAGIC(name)) {
			__u64 off = sec->sh_offset;
			//
		}
	}
}