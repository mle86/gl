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

#define _XOPEN_SOURCE 500

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "gl.h"
#include "aux.h"
#include "group.h"


static options_t options = default_options;


int main (int argc, const char** argv) {
	read_arguments(argc, argv, &options);

	if (optind >= argc) {
		// no further arguments, list all groups:
		list_all_groups();

	} else {
		// list members of one group:

		const struct group* g = find_group(argv[optind]);
		if (! g) {
			fprintf(stderr, "getgrnam(%s) failed: %s\n",
					argv[optind],
					(errno) ? strerror(errno) : "group not found");
			return 1;
		}

		if (options.list_primary_members) {
			if (options.verbose)
				printf("Primary group members:\n");

			list_primary_group_members(g);
		}

		if (options.list_secondary_members) {
			if (options.verbose && options.list_primary_members)
				printf("\n");
			if (options.verbose)
				printf("Secondary group members:\n");

			list_secondary_group_members(g);
		}
	}

	return 0;
}

void print_entry (const char* name, unsigned long int id) {
	if (options.show_IDs && options.show_names)
		printf("(%lu)%s%c", id, name, options.separator);
	else if (options.show_IDs)
		printf("%lu%c", id, options.separator);
	else if (options.show_names)
		printf("%s%c", name, options.separator);
}

