# R2AI_USERDIR=$(shell r2ai -HR2AI_USERDIR)
R2AI_USERDIR=$(HOME)/.r2ai.plugins

all:
	mkdir -p $(R2AI_USERDIR)
	cp -f plugin.py $(R2AI_USERDIR)/plugin.py

uninstall:
	rm -f $(R2AI_USERDIR)/plugin.py
