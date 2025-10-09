# Sample RCore plugin in Go

This directory contains a basic RCore plugin for radare2 written in Go using cgo.

The plugin registers a new `hello` command that is fully implemented in Go. At runtime the command prints a greeting and lets you override the target name via `hello <name>`.

## Build

```
make
```

The build produces `src/core_hello.dylib` plus the companion C header required by radare2. A local Go build cache (`.gocache/`) is used automatically so the build does not depend on any writable global directories.

To install the plugin into your user plug-in directory:

```
make user-install
```

Use this skeleton as a starting point for authoring Go-based core plugins without a separate C shim.
