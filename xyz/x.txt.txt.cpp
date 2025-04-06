d.iter(px.src.mem, px.src.sz, [&](__u64 i, insn_t& in) {
	if (in.IsNull() || !in.IsRip()) return;
});
// __u64 off =  px.out.off;
// printf("%lx %lx %lx\n", static_cast<__u8>(px.t), off, px.src.sz);



if (px.s_elf == s_tup.elf) {
	__u64 virt	= in.PtrAddr(px.s_elf->ftov(px.orig.off + i));
	__u64 off	= px.s_elf->vtof(virt);
	if (_contain_(mm_src->off, mm_src->sz, off)) {
		auto _px = get_patch(s_tup.elf, off);
		if (!!_px)
			printf(BRED"PIN %lx %lx \t"CRST, _px->orig.off, _px->orig.sz);
	}
	auto sec = px.s_elf->vtosh(virt);
	if (!!sec)
		printf(BRED"%s\n"CRST, (char*)&px.s_elf->sec.str[sec->sh_name]);
}

			if (!!px.s_elf) {
				auto dst	= in.PtrAddr(px.s_elf->ftov(px.orig.off));
				auto p		= px.s_elf->vtoph(dst);
				auto sec	= px.s_elf->vtosh(dst);
				if (!!sec)
					printf("  ---> [" BBLUE "0x%lx" CRST "] \t [" BGRN "%s" CRST "] | ",
						dst, &px.s_elf->sec.str[sec->sh_name]);
				if (!!p)
					switch (p->p_flags) {
						case PF_R: 			printf(BRED "R" CRST);	break;
						case PF_R|PF_W:		printf(BRED "RW" CRST);	break;
						case PF_R|PF_X:		printf(BRED "RX" CRST);	break;
						case PF_R|PF_W|PF_X:printf(BRED "RWX" CRST);break;
						default:			printf(BRED "OTHER" CRST);break;
					}
				puts("");
			}
		// for (auto& _bb : tuple.bb) {
		// 	printf("%lx\n", _bb);
		// }
		// }
	// 	_disasm(mm.mem, __off, p.out.off, i, iter) {
	// 		iter.Print();
	// 	}
	// 	// printf("%lx (+%lx) - %lx\n", off, size, p.out.off);
	// 	_hexdump(p.src.mem, p.src.sz);
	// 	size += p.src.sz;
	// 	__off = p.out.off - mm.off;
	// }
	// _disasm(mm.mem, __off, mm.sz - (__off - mm.off), i, iter) {
	// 	iter.Print();
	// }
	// printf("%lx (+%lx) - %lx\n", __off, size, mm.sz);


// printf("+ %lx %lx %lx // %lx\n", off, px->orig.off, dst_px->src.off, off_align((off - dst_px->orig.off) - dst_px->src.off));
				// memcpy(ptr + l_off, px->src.mem + i, in.size());
				// l_off += in.size();