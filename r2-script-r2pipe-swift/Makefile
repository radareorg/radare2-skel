all:
	swift build
	swift run

clean:
	rm -rf .build
	rm -f Package.resolved
	swift package purge-cache
	swift package reset
	swift package clean
