SWIFTFLAGS += -Xswiftc -Ir_core
SWIFTFLAGS += -Xswiftc -DUSE_CCALL

all:
	swift build $(SWIFTFLAGS)
	swift run

clean:
	rm -rf .build
	rm -f Package.resolved
	swift package purge-cache
	swift package reset
	swift package clean
