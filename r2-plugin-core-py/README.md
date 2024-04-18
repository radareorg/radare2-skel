# r2 Core plugin in Python

This directory contains a core plugin for radare2.

Core plugins have access to the classic r2cmd interface
to execute commands and get the output as a string like
r2pipe does.

But also provide a way to register core plugins which
let you handle new commands and keep a global state
while the instance of r2 is alive.
