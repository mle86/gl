#ifndef __GL_H
#define __GL_H

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


// Program info:
#define VERSION "1.3"
#ifndef PROGNAME
  #define PROGNAME "gl"
#endif

// Limits:
#define MAXUSERS 65536

// ANSI coloring:
#define M1 "[1m"
#define M0 "[0m"

// Helper macros:
#define IsDigit(c) ((c >= '0') && (c <= '9'))


// Prototypes:
int main (int argc, char** argv);

void Help    (void);
void Version (void);


#endif // __GL_H
