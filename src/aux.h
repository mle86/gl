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

#ifndef _AUX_H
#define _AUX_H

#include "gl.h"


void read_arguments (int argc, const char** argv, options_t *o);

void show_program_help    (void);
void show_program_version (void);


#endif  // _AUX_H
