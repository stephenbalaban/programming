CC=gcc
SRCDIR=src
BDIR=bin

cat: $(SRCDIR)/cat.c
	mkdir -p $(BDIR)
	gcc -o $(BDIR)/cat $(SRCDIR)/cat.c

ls: $(SRCDIR)/ls.c
	mkdir -p $(BDIR)
	gcc -o $(BDIR)/ls $(SRCDIR)/ls.c

stat: $(SRCDIR)/stat.c
	mkdir -p $(BDIR)
	gcc -o $(BDIR)/stat $(SRCDIR)/stat.c

clean :
	rm -rf $(BDIR)
