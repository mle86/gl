#ifndef __GL_H
#define __GL_H

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#define VERSION "1.1"
#define MAXUSERS 65536

#define M1 "[1m"
#define M0 "[0m"

#define IsDigit(c)          ( (c >= '0') && (c <= '9') )


int main (int argc, char** argv);

void Help (void);
void Version (void);


#endif // __GL_H
