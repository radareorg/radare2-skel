# Swift RCore plugin example

This sample shows how to write a tiny `RCore` plugin for radare2 in Swift using `swift build`. The plugin exposes a `hello` command that:
- executes `ij` via the native `r_core_cmd_str` API
- parses the JSON response with `JSONSerialization`
- prints a short summary through `r_cons_print`

## Build
```sh
$ swift build -c release
# or use the helper to copy the expected filename next to the sources
$ make
```
Set `R2_PREFIX=/path/to/radare2/prefix` if radare2 is not installed in one of the default prefixes (`/usr/local`, `/usr`, `/opt/homebrew`). The package manifest automatically injects the matching header search paths.

## Install
```sh
$ make user-install        # copies core_hello.<ext> into $(r2 -H R2_USER_PLUGINS)
# clean up with: make user-uninstall
```

## Use inside r2
```text
[0x00000000]> e cmd.plugin=true         # ensure plugin command routing is enabled
[0x00000000]> hello
Hello from Swift! Fetching binary info...
Binary arch: x86 (64 bits)
```

Use this as a starting point for your own plugins. The Swift code in `Sources/CoreHello/CoreHello.swift` interacts with the radare2 C API directly so it is easy to extend with additional commands.
