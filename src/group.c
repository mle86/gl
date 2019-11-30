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

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#include "group.h"
#include "gl.h"


void list_all_groups (void) {
	setgrent();
	errno = 0;

	struct group* g;
	while ((g = getgrent())) {
		print_entry(g->gr_name, (unsigned long int)g->gr_gid);
		errno = 0;
	}

	if (errno)
		perror("getgrent");

	endgrent();
}

void list_primary_group_members (const struct group* g) {
	setpwent();
	errno = 0;

	struct passwd* u;
	while ((u = getpwent())) {
		if (u->pw_gid == g->gr_gid)
			print_entry(u->pw_name, (unsigned long int)u->pw_uid);
		errno = 0;
	}

	if (errno)
		perror("getpwent");

	endpwent();
}

void list_secondary_group_members (const struct group* g) {
	for (char** members = g->gr_mem; *members; members++) {
		#define member ((const char*) *members)
		errno = 0;

		// gr_mem contains only names. Try to obtain the numerical id:
		const struct passwd* u = getpwnam(member);

		if (u) {
			print_entry(u->pw_name, (unsigned long int)u->pw_uid);
		} else {
			fprintf(stderr, "getpwnam(%s) failed: %s\n",
					member,
					(errno) ? strerror(errno) : "user not found");
		}
	}
}

const struct group* find_group (const char* input) {
	if (!input || !input[0])
		// empty string always fails
		return NULL;

	// try to read input as a number first:
	char* endptr;
	long int i = strtol(input, &endptr, 10);
	if (*endptr == '\0') {
		// looks like a number!
		return getgrgid((gid_t)i);
	} else {
		return getgrnam(input);
	}
}

