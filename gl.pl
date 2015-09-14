#!/usr/bin/perl
#################################################
#                                               #
# gl 1.0                                        #
#                                               #
# Written by Maximilian E. <mle@multinion.de>,  #
# November 2004.                                #
#                                               #
#################################################

my @GIDs   = ();
my @Groups = ();
my $GID    = undef;
my $GName  = '';
my $LineBreak = "\n";
my $Separator = ' ';
my $DisplayGroup = '';
my $DisplayGID   =  0;
my $ShowIDs    = 1;
my $ShowAdmins = 0;
my $PRG = 'gl';
# If you do not want colors,
# comment out the next 2 lines:
my $M1 = '[1m';
my $M0 = '[0m';

while( my $arg = shift @ARGV ) {
	if (($arg eq '-h') || ($arg eq '--help')) { print
		"usage: $M1$PRG$M0 [${M1}OPTIONS${M0}] [${M1}GROUP NAME${M0}/${M1}ID${M0}]\n" .
		"Lists all groups or all members of a specific group.\n\n" .
		"  ${M1}-n${M0} / ${M1}--omit-ids${M0}   GIDs/UIDs won't be displayed.\n" .
		"  ${M1}-a${M0} / ${M1}--admins${M0}     When displaying members of a specific group,\n" .
		"                    the group administrators  will be shown too.\n" .
		"                    (To use  this feature,  you  must be  root.)\n" .
		"  ${M1}-1${M0} / ${M1}--no-breaks${M0}  When displaying all groups, no linebreaks\n" .
		"                    will  be  printed  between  group  names.\n" .
		"  ${M1}-h${M0} / ${M1}--help${M0}       Shows this help screen.\n" .
		"  ${M1}-v${M0} / ${M1}--version${M0}    Shows program version.\n\n" .
		"When no ${M1}GROUP NAME${M0} is specified, $M1$PRG$M0 shows a list of all groups.\n" .
		"${M1}gl${M0} is an abbrevation for ${M1}g${M0}roup ${M1}l${M0}isting.\n\n";
		exit 0;
	} elsif (($arg eq '-v') || ($arg eq '--version')) { print
		"$PRG 1.0\n" .
		"Written by Maximilian E. <mle\@multinion.de>,\n" .
		"November 2004.\n\n";
		exit 0;
	} elsif (($arg eq '-n') || ($arg eq '--omit-ids')) {
		$ShowIDs = 0;
	} elsif (($arg eq '-a') || ($arg eq '--admins')) {
		$ShowAdmins = 1;
	} elsif (($arg eq '-1') || ($arg eq '--no-breaks')) {
		$LineBreak = ' ';
		$Separator = '';
	} elsif (length $arg) {
		if ($arg =~ m/^\d+$/o) {
			$DisplayGID = int $arg;
		} else {
			$DisplayGroup = $arg;
		}
	}
}

if ((! $DisplayGID) && (! length $DisplayGroup)) {
	
	open GFH, '< /etc/group';
	while( <GFH> ) {
		chomp;
		my @grp = split /:/o;
		$GID = $grp[2];
		push @GIDs, $GID;
		$Groups[$GID] = $grp[0];
	}
	close GFH;
	foreach( sort { $a <=> $b } @GIDs ) {
		print( ($ShowIDs ? "($_)$Separator" : '') . $Groups[$_] . $LineBreak );
	}
	print "\n" unless $LineBreak eq "\n";
	exit 0;
	
} else {
	
	my (%GroupPriMembers, $Pri);
	my (%GroupSecMembers, @GSecM, $Sec);
	my (%GroupAdmins, @GAdm, $Adm);
	
	open GFH, '< /etc/group';
	while( <GFH> ) {
		chomp;
		my @grp = split /:/o;
		next if $DisplayGID && ($DisplayGID != $grp[2]);
		next if length($DisplayGroup) && ($DisplayGroup ne $grp[0]);
		$GID   = $grp[2];
		$GName = $grp[0];
		@GSecM = split /,/o, $grp[3];
		last;
	}
	close GFH;
	if (! defined $GID) {
		print "$PRG: Could not find " . ($DisplayGID ? "GID $DisplayGID" : "group $DisplayGroup") . ".\n";
		exit 1;
	}
	
	if ($ShowAdmins) {
		if ((-r '/etc/gshadow') + (-R '/etc/gshadow')) {
			open SFH, '< /etc/gshadow';
			while( <SFH> ) {
				chomp;
				my @grp = split /:/o;
				next unless $grp[0] eq $GName;
				@GAdm = split /,/o, $grp[2];
				last;
			}
			close SFH;
		} else { $ShowAdmins = 2; }
	}
	
	open PFH, '< /etc/passwd';
	while( <PFH> ) {
		chomp;
		my @user = split /:/o;
		foreach( @GSecM ) { if ($_ eq $user[0]) { $GroupSecMembers{$user[2]} = $_; $Sec++; last; } }
		foreach( @GAdm  ) { if ($_ eq $user[0]) { $GroupAdmins{$user[2]} = $_; $Adm++; last; } }
		if ($GID == $user[3]) { $GroupPriMembers{$user[2]} = $user[0]; $Pri++; }
	}
	close PFH;
	
	print 'Listing members of ' . ($ShowIDs ? "($GID)" : '') . $M1 . $GName . $M0 . "\n\n";
	print "Primary group members:\n";
	foreach( sort {$a <=> $b} keys %GroupPriMembers ) {
		print "\t" . ($ShowIDs ? "($_) " : '') . $M1 . $GroupPriMembers{$_} . $M0 . "\n";
	} if (! $Pri) { print "\t(none)\n"; }

	print "\nSecondary group members:\n";
	foreach( sort {$a <=> $b} keys %GroupSecMembers ) {
		print "\t" . ($ShowIDs ? "($_) " : '') . $M1 . $GroupSecMembers{$_} . $M0 . "\n";
	} if (! $Sec) { print "\t(none)\n"; }
	
	if ($ShowAdmins) {
		print "\nGroup administrators:\n";
		if ($ShowAdmins == 2) {
			print "\t(cannot access /etc/gshadow)\n";
		} else {
			foreach( sort {$a <=> $b} keys %GroupAdmins ) {
				print "\t" . ($ShowIDs ? "($_) " : '') . $M1 . $GroupAdmins{$_} . $M0 . "\n";
			} if (! $Adm) { print "\t(none)\n"; }
		}
	}
}
exit 0;
