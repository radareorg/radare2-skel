# r2 arch plugin in Python

This directory contains an arch plugin for radare2.

An arch plugin adds support for a new processor architecture to radare2. It
does so by implementing handlers that describe the architecture (regs, info),
and for assembling (encode) and disassembling (decode) instructions.
