# Sample RParse plugin in C

This directory contains a basic RParse plugin for radare2 written in C.

Use this as a template and extend it for your needs.

Note that RParse api is very fragile and badly designed, expect
changes in a near future, so be careful and don't use this thing for
anything else than a toy.

Compilation and Installation:

```
$ make
$ make install
```

Usage:

```
$ r2 -e asm.parser=hello -e asm.pseudo=true /bin/ls
> pd 20
```
