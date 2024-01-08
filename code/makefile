BINDIR = bin
DOCDIR = doc
INCLUDEDIR = include
LIBDIR = lib
OBJDIR = obj
SRCDIR = src
TESTDIR = tests
EXEC = huffman
CC = gcc
CFLAGS = -g -Wall -pedantic
CFLAGS_RELEASE = -O3 -Wall -pedantic
LDFLAGS = -lcunit
DOXYGEN = doxygen Doxyfile
DOC = $(DOCDIR)/html

OBJS = $(OBJDIR)/arbre.o $(OBJDIR)/codeBinaire.o $(OBJDIR)/fileDePriorite.o $(OBJDIR)/octet.o $(OBJDIR)/stats.o $(OBJDIR)/table.o

# Rule to create directories
directories:
	mkdir -p $(BINDIR) $(DOCDIR) $(INCLUDEDIR) $(LIBDIR) $(OBJDIR) $(SRCDIR) $(TESTDIR)

# Main targets
all : directories debug

debug: $(BINDIR)/$(EXEC)

release: CFLAGS = $(CFLAGS_RELEASE)
release: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I$(INCLUDEDIR)

doc : directories $(DOC)

$(DOC) :
	$(DOXYGEN)
	cd $(DOCDIR)/latex; make; cd ../..

# Test targets
tests : directories $(TESTDIR)/testArbre $(TESTDIR)/testCodeBinaire $(TESTDIR)/testFile $(TESTDIR)/testOctet $(TESTDIR)/testTable $(TESTDIR)/testStats

$(TESTDIR)/testArbre : $(SRCDIR)/$(TESTDIR)/testArbre.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -I$(INCLUDEDIR)

$(TESTDIR)/testCodeBinaire : $(SRCDIR)/$(TESTDIR)/testCodeBinaire.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -I$(INCLUDEDIR)

$(TESTDIR)/testFile : $(SRCDIR)/$(TESTDIR)/testFile.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -I$(INCLUDEDIR)

$(TESTDIR)/testOctet : $(SRCDIR)/$(TESTDIR)/testOctet.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -I$(INCLUDEDIR)

$(TESTDIR)/testTable : $(SRCDIR)/$(TESTDIR)/testTable.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -I$(INCLUDEDIR)

$(TESTDIR)/testStats : $(SRCDIR)/$(TESTDIR)/testStats.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -I$(INCLUDEDIR)

# Object file rules
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

$(OBJDIR)/$(TESTDIR)/%.o : $(SRCDIR)/$(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

# Clean rule
clean :
	rm -rf $(BINDIR)/*
	rm -rf $(TESTDIR)/*
	rm -rf $(LIBDIR)/*
	rm -rf $(OBJDIR)/*.o
	rm -rf $(OBJDIR)/$(TESTDIR)/*.o
	rm -rf $(DOCDIR)/*
