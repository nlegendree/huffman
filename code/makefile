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
CFLAGS_RELEASE = -O3 -s -Wall -pedantic
LDFLAGS = -lcunit
DOXYGEN = doxygen Doxyfile
DOC = $(DOCDIR)/html

OBJS = $(OBJDIR)/arbre.o $(OBJDIR)/codeBinaire.o $(OBJDIR)/fileDePriorite.o $(OBJDIR)/octet.o $(OBJDIR)/stats.o $(OBJDIR)/table.o

all : debug

debug: $(BINDIR)/$(EXEC)

release: CFLAGS = $(CFLAGS_RELEASE)
release: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I$(INCLUDEDIR)

doc : $(DOC)

$(DOC) :	
	$(DOXYGEN)
	cd $(DOCDIR)/latex;make;cd ../..

tests : $(TESTDIR)/testArbre $(TESTDIR)/testCodeBinaire $(TESTDIR)/testFile $(TESTDIR)/testOctet $(TESTDIR)/testTable $(TESTDIR)/testStats

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

$(TESTDIR)/testStats : $(SRCDIR)/$(TESTDIR)/testTable.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -I$(INCLUDEDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

$(OBJDIR)/$(TESTDIR)/%.o : $(SRCDIR)/$(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

clean :
	rm -rf $(BINDIR)/*
	rm -rf $(TESTDIR)/*
	rm -rf $(LIBDIR)/*
	rm -rf $(OBJDIR)/*.o
	rm -rf $(OBJDIR)/$(TESTDIR)/*.o
	rm -rf $(DOCDIR)/*
