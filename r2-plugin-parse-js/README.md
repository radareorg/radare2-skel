# Sample RParse plugin in r2js

This directory contains a basic RParse plugin for radare2 written in r2js

Running:

```
$ make
$ make install
```

Usage:

```
$ r2 -e asm.parser=hello -e asm.pseudo=true /bin/ls
> pd 20
```
