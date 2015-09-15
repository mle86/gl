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

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "aux.h"


void read_arguments (int argc, const char** argv, options_t *o) {
	signed char c;
	while ((c = getopt(argc, (char*const*)argv, "hVnNpsv")) != -1)
		switch(c) {
			case 'h': show_program_help();    exit(0);
			case 'V': show_program_version(); exit(0);

			case 'n': o->show_IDs = false, o->show_names = false; break;
			case 'N': o->show_IDs = true,  o->show_names = true;  break;

			case 'p': o->list_primary_members = true,  o->list_secondary_members = false; break;
			case 's': o->list_primary_members = false, o->list_secondary_members = true;  break;

			case 'v': o->verbose = true; break;
		}
}

void show_program_help () { printf(
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
); }

void show_program_version () { printf(
	PROGNAME" v"VERSION"\n"
	"Written by Maximilian Eul <maximilian@eul.cc>, September 2015.\n"
	"\n"
); }

