/*  Copyright (C) 2015  Maximilian L. Eul
    This file is part of gl.

    gl is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    gl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with gl.  If not, see <http://www.gnu.org/licenses/>.
*/

#define _XOPEN_SOURCE 500

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "gl.h"


int main (int argc, char** argv) {

	bool Break	= true,  // show linebreaks after each user?

	     ShowIDs	= true,  // show numerical user IDs?
	     ShowNames	= true,  // show user names?

	     ShowPrimaryMembers		= true,  // show primary group members?
	     ShowSecondaryMembers	= true,  // show secondary group members?

	     Verbose			= false;  // show extra output?

	struct passwd* u;
	struct group* g;

	{ // Get command line arguments
		register signed char c;
		while ( (c = getopt(argc, argv, "hVnNrpsv")) != -1 )
		switch(c) {
			case 'h': Help(); return 0;
			case 'V': Version(); return 0;
			case 'n': ShowNames=true;  ShowIDs=false; break;
			case 'N': ShowNames=false; ShowIDs=true;  break;
			case 'p': ShowPrimaryMembers=true;  ShowSecondaryMembers=false; break;
			case 's': ShowPrimaryMembers=false; ShowSecondaryMembers=true;  break;
			case 'r': Break=false; break;
			case 'v': Verbose=true; break;
		}
	}

	const char* fmt =
		(ShowIDs && ShowNames) ?
		  (Verbose ? (" (%1$i) "M1"%2$s"M0) : " (%1$i)%2$s") : // id & name
		(ShowIDs ?
		   " %1$i" : // id
		   " %2$s"); // name

	if (optind < argc) {
		// List one group
		char** m;
		long int gid;

		errno = 0;
		if (IsDigit(argv[optind][0]))
			g = getgrgid(atoi(argv[optind]));
		else
			g = getgrnam(argv[optind]);
		if (! g) {
			fprintf(stderr, PROGNAME": getgrnam(%s) failed: %s\n", argv[optind], errno ? strerror(errno) : "group not found");
			exit(1);
		}
		gid = g->gr_gid;

		if (ShowPrimaryMembers) {
			if (Verbose)
				printf("Primary members:\n");

			setpwent();
			while(( u = getpwent() )) {
				if (u->pw_gid != gid)
					continue;

				printf(fmt, u->pw_uid, u->pw_name);
				if (Break)
					printf("\n");
			}
			endpwent();
		}

		if (ShowSecondaryMembers) {
			if (Verbose)
				printf("%sSecondary members:\n", ShowPrimaryMembers ? "\n" : "");

			m = g->gr_mem;
			if (! m) {
				fprintf(stderr, PROGNAME": could not read secondary group members\n");
				exit(1);
			}
			while( *m ) {
				if (ShowIDs || ShowPrimaryMembers) {
					u = getpwnam(*m);
					if (! u) {
						fprintf(stderr, PROGNAME": getpwnam(%s) failed: %s\n", *m, errno ? strerror(errno) : "user not found");
						goto skip;
					}
				}

				printf(fmt, u->pw_uid, *m);
				if (Break)
					printf("\n");

				skip:
				m++;
			}
		}

		if (! Break) // && *(g->gr_mem))
			printf("\n");
		exit(0);
	}

	// all group names
	
	setgrent();
	while(( g = getgrent() )){

		printf(fmt, g->gr_gid, g->gr_name);
		if (Break)
			printf("\n");
	}
	endgrent();

	if (! Break)
		printf("\n");
	exit(0);
}

void Help () { printf(
	M1 "%s" M0"  lists all groups or all members of one group.\n"
	"Usage: "M1 PROGNAME M0" ["M1"OPTIONS"M0"] ["M1"GROUP"M0"]\n"
	"Options:\n"
	M1"  -n    "M0"Print names only instead of names and IDs of groups/members.\n"
	M1"  -N    "M0"Print IDs only   instead of names and IDs of groups/members.\n"
	M1"  -p    "M0"Print primary group members only\n"
	  "        "  "instead of primary and secondary members.\n"
	M1"  -s    "M0"Print secondary group members only\n"
	  "        "  "instead of primary and secondary members.\n"
	M1"  -r    "M0"No linebreaks after each group/member.\n"
	M1"  -h    "M0"This help.\n"
	M1"  -V    "M0"Program version information.\n"
	"\n",
	PROGNAME
); exit(0); }

void Version () { printf(
	PROGNAME" v"VERSION"\n"
	"Written by Maximilian Eul <maximilian@eul.cc>, September 2015.\n"
	"\n"
); exit(0); }

