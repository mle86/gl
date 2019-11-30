/*  Copyright (C) 2015,2019  Maximilian L. Eul
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
#define _GNU_SOURCE
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include "aux.h"


void read_arguments (int argc, const char** argv, options_t *o) {
	const char* short_options = "hVnNpsv0";
	const struct option long_options [] = {
		{ "help",	0, NULL, 'h' },
		{ "version",	0, NULL, 'V' },
		{ "primary",	0, NULL, 'p' },
		{ "secondary",	0, NULL, 's' },
		{ "ids",	0, NULL, 'N' },
		{ "names",	0, NULL, 'n' },
		{ "verbose",	0, NULL, 'v' },
		{ "print0",	0, NULL, '0' },
		{ 0,0,0,0 }
	};

	signed char c;
	while ((c = getopt_long(argc, (char*const*)argv, short_options, long_options, NULL)) != -1)
		switch(c) {
			case 'h': show_program_help();    exit(0);
			case 'V': show_program_version(); exit(0);

			case 'n': o->show_IDs = false, o->show_names = true;  break;
			case 'N': o->show_IDs = true,  o->show_names = false; break;

			case 'v':
				o->show_IDs   = true,
				o->show_names = true,
				o->verbose    = true;
				break;

			case '0': o->separator = '\0'; break;

			case 'p': o->list_primary_members = true,  o->list_secondary_members = false; break;
			case 's': o->list_primary_members = false, o->list_secondary_members = true;  break;
		}
}

void show_program_help () { printf(
	"%s lists all groups or all members of one group.\n"
	"Usage: %s [OPTIONS] [GROUP]\n"
	"Options:\n"
	"  -n, --names     Print group/member names only (default).\n"
	"  -N, --ids       Print group/member IDs only.\n"
	"  -p, --primary   Print primary group members only.\n"
	"  -s, --secondary Print secondary group members only.\n"
	"  -v, --verbose   Separate primary/secondary members, show names and IDs.\n"
	"  -0, --print0    Separate output lines with NUL instead of linebreaks.\n"
	"  -h, --help      This help.\n"
	"  -V, --version   Program version information.\n"
	"\n",
	PROGNAME, PROGNAME
); }

void show_program_version () { printf(
	PROGNAME" v"VERSION"\n"
	"Written by Maximilian Eul <maximilian@eul.cc>, November 2019.\n"
	"License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
	"\n"
); }

