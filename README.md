# gl(1) - group listing and group member listing

Version 1.3, September 2015

```
gl [-hV] [-nNpsv0] [GROUP]
```

# Description

**gl** is a command line tool which lists all members of the speficied user group.
If no _GROUP_ (name or numerical id) is given, **gl** lists all groups.

# Options


* **-n, --names**  
  Print the names of groups/group members only.  
  This is the default.
* **-N, --ids**  
  Print the numerical IDs of groups/group members only.  
  Usually, **gl** prints only their names.
* **-p, --primary**  
  When listing group members, list primary members only.  
  Usually, **gl** lists primary and secondary members.
* **-s, --secondary**  
  When listing group members, list secondary members only.  
  Usually, **gl** lists primary and secondary members.
* **-v, --verbose**  
  Verbose mode:
  When listing group members, separate the primary and secondary member list.
  Also show names and numerical IDs.
* **-0, --print0**  
  Output lines will be separated with NUL instead on linebreaks.
  Suitable for **xargs**' **--null** input option.
* **-h, --help**  
  **gl** will print a short help summary and exit.
* **-V, --version**  
  **gl** will print its program version and exit.

# Example


* $ **gl -v staff**  
  Lists all members of the **staff** group.

# Installation

To compile gl, just use make:

	$ make

To install gl, run 'make install' as the superuser:

	# make install

This will copy the binary to /usr/local/bin/gl
and the manpage to /usr/local/share/man/man1/gl.1.gz.



# Standards and Dependencies

gl is written in C99 (*ISO/IEC 9899:1999*).
It mostly conforms to SUSv3 (*POSIX.1-2001*),
except that it's using GNU libc's *getopt_long()* function.

Tested with:
* _gcc_ 4.9.1
* _libc6_ 2.19
* _GNU Make_ 4.0



# See Also

**getgrent**(3),
**getgrnam**(3)

# License

[GNU GPL v3](http://gnu.org/licenses/gpl.html)

# Author

Maximilian Eul
&lt;[maximilian@eul.cc](mailto:maximilian@eul.cc)&gt;
(https://github.com/mle86)
