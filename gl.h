#ifndef __GL_H
#define __GL_H

/*  Copyright (C) 2009  Maximilian L. Eul
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

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>


#define VERSION "1.2"
#ifndef PROGNAME
  #define PROGNAME "gl"
#endif

#define MAXUSERS 65536
//#define UIDLEN 5

#define M1 "[1m"
#define M0 "[0m"

#define IsDigit(c)          ( (c >= '0') && (c <= '9') )

#define STR_(s) STRb_(s)
#define STRb_(s) #s


int main (int argc, char** argv);

void Help (void);
void Version (void);


#endif // __GL_H
