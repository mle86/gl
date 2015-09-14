#include "gl.h"

int main (int argc, char** argv) {

	short Break = 1;
	short ShowIDs=1, ShowNames=1;
	short ShowPrimaryMembers=1, ShowSecondaryMembers=1;
	
	int KnownUsers [MAXUSERS];
	int ku = 0;

	struct passwd* u;
	struct group* g;
	char c;

	while ( (c = getopt(argc, argv, "hVnNrps")) != -1 )
		switch(c) {
			case 'h': Help(); return 0;
			case 'V': Version(); return 0;
			case 'n': ShowNames=1; ShowIDs=0; break;
			case 'N': ShowNames=0; ShowIDs=1; break;
			case 'p': ShowPrimaryMembers=1; ShowSecondaryMembers=0; break;
			case 's': ShowPrimaryMembers=0; ShowSecondaryMembers=1; break;
			case 'r': Break=0; break;
		}

	if (optind < argc) {
		// Mitglieder einer Gruppe
		char** m;
		int gid;
		if (IsDigit(argv[optind][0]))
			g = getgrgid(atoi(argv[optind]));
		else
			g = getgrnam(argv[optind]);
		if (! g) {
			fprintf(stderr, PROGNAME ": group %s not found\n", argv[optind]);
			exit(1);
		}
		gid = g->gr_gid;

		if (ShowPrimaryMembers) {
			setpwent();
			while(( u = getpwent() )) {
				if (u->pw_gid != gid)
					continue;
				if (ShowSecondaryMembers)
					KnownUsers[ku++] = u->pw_uid;
				if (ShowIDs && ShowNames)
					printf("%i(%s)", u->pw_uid, u->pw_name);
				else if (ShowIDs)
					printf("%i", u->pw_uid);
				else	printf("%s", u->pw_name);

				printf(Break ? "\n" : " ");
			}
			endpwent();
		}

		if (ShowSecondaryMembers) {
			m = g->gr_mem;
			if (! m) {
				fprintf(stderr, PROGNAME ": could not read group members\n");
				exit(1);
			}
			while(*m) {
				if (ShowIDs || ShowPrimaryMembers) {
					u = getpwnam(*m);
					if (! u) {
						fprintf(stderr, PROGNAME ": could not fetch user info for %s\n", *m);
						goto skip;
					}
					if (ShowPrimaryMembers && ku) {
						register int i;
						for (i=0; i<ku; i++)
							if (KnownUsers[i] == u->pw_uid)
								goto skip;
					}
				}

				if (ShowIDs && ShowNames)
					printf("%i(%s)", u->pw_uid, *m);
				else if (ShowIDs)
					printf("%i", u->pw_uid);
				else	printf("%s", *m);

				printf(Break ? "\n" : " ");
skip:
				m++;
			}
		}

		if (! Break) // && *(g->gr_mem))
			printf("\n");
		exit(0);
	}

	// Alle Gruppennamen
	
	setgrent();
	while(( g = getgrent() )){

		if (ShowIDs && ShowNames)
			printf("%i(%s)", g->gr_gid, g->gr_name);
		else if (ShowIDs)
			printf("%i", g->gr_gid);
		else	printf("%s", g->gr_name);

		printf(Break ? "\n" : " ");
	}
	endgrent();

	if (! Break)
		printf("\n");
	exit(0);
}

void Help () { printf(
	M1 PROGNAME M0 "  lists all groups or all members of one group.\n"
	"Usage: " M1 PROGNAME M0 " [" M1 "OPTIONS" M0 "] [" M1 "GROUP" M0 "]\n"
	"Options:\n"
	M1 "  -n        " M0 "Only print names instead of names _and_ IDs of groups/members.\n"
	M1 "  -N        " M0 "Only print IDs   instead of names _and_ IDs of groups/members.\n"
	M1 "  -p        " M0 "Only print primary   group members\n"
	   "            "    "instead of primary _and_ secondary members.\n"
	M1 "  -s        " M0 "Only print secondary group members\n"
	   "            "    "instead of primary _and_ secondary members.\n"
	M1 "  -r        " M0 "No linebreaks after each group/member.\n"
	M1 "  -h        " M0 "This help.\n"
	M1 "  -V        " M0 "Program version information.\n"
	"\n"
); exit(0); }

void Version () { printf(
	PROGNAME " v" VERSION "\n"
	"Written by Maximilian Eul <mle@multinion.de>, November 2007.\n"
	"\n"
); exit(0); }
