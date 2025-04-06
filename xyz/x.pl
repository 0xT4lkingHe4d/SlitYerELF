use feature "say";

use constant {
	SYS_PTRACE => 101,
};

use constant {	
	PTRACE_TRACEME		=> 0,
	PTRACE_PEEKTEXT		=> 1,
	PTRACE_PEEKDATA		=> 2,
	PTRACE_PEEKUSR		=> 3,
	PTRACE_POKETEXT		=> 4,
	PTRACE_POKEDATA		=> 5,
	PTRACE_POKEUSR		=> 6,
	PTRACE_CONT			=> 7,
	PTRACE_KILL			=> 8,
	PTRACE_SINGLESTEP	=> 9,
	PTRACE_ATTACH		=> 16,
	PTRACE_DETACH		=> 17,
	PTRACE_SYSCALL		=> 24,
};

sub ptrace {
	my ($cmd, $pid, $addr, $dat) = @_;
	my $r = syscall(SYS_PTRACE, $cmd, $pid, $addr, $dat);
	say "  [PTRACE] " . $r if ($cmd != PTRACE_DETACH and $r == -1);
	return $r;
}

sub parse_proc_maps {
	open PROCMAP, "/proc/@_[0]/maps" || die "Cannot open /proc/@_[0]/maps";
	while (<PROCMAP>) {
		my ($off, $end, $perm, $file) = $_ =~ m/^([0-9a-f]{,16})-([0-9a-f]{,16}) ([rwx-]{3})[^\/\[]+([\[\/].+)?/g;
		# say "$off, $end, $perm, $file" if $perm =~ /.wx/;
		if ($perm =~ /r../) {
			my $r=0x12345678;
			ptrace(PTRACE_PEEKTEXT, int @_[0], $off, \$r);
			printf "%x\n", $r;
		}
	}
}

my @proc = split(' ', `pidof firefox-esr`);
foreach my $pid (@proc) {
	ptrace(PTRACE_ATTACH, int $pid);
	parse_proc_maps($pid);
	ptrace(PTRACE_DETACH, int $pid);
}