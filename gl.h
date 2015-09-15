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

#ifndef _GL_H
#define _GL_H

#include <stdbool.h>


typedef struct options {
	char separator;
	bool show_IDs;
	bool show_names;
	bool list_primary_members;
	bool list_secondary_members;
	bool verbose;
} options_t;

#define default_options {			\
	.separator  = '\n',			\
	.show_IDs   = false,			\
	.show_names = true,			\
	.list_primary_members   = true,		\
	.list_secondary_members = true,		\
	.verbose = false,			\
}


// Program info:
#define VERSION "1.3"
#ifndef PROGNAME
  #define PROGNAME "gl"
#endif

// ANSI coloring:
#define M1 "[1m"
#define M0 "[0m"


int main (int argc, const char** argv);

void print_entry (const char* name, unsigned long int id);


#endif // _GL_H
