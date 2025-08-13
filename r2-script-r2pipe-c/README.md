# Hello r2pipe C example

This small example demonstrates using the r2pipe C API
provided by libr_socket to spawn radare2 and send a command.

## Run:

To build the program just run `make`.

```bash
r2 -c '#!pipe ./hello' -qcq --
```

## Notes:

- The example calls `r2pipe_open("radare2 -N -q0 -")` which spawns radare2 in non-interactive quiet mode. Adjust the command if you need a different radare2 binary or arguments.
- The program uses `r2pipe_cmd(r, "?e hello world");` which mirrors tests in the radare2 tree that evaluate expressions.
- Run `make test` to ensure the implementation works
