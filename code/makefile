# CC = gcc
# CFLAGS = -Wall -g
# OBJDIR = obj
# BINDIR = bin
# SRCDIR = src
# INCDIR = include

# # Liste des fichiers .o
# OBJS = $(OBJDIR)/arbre.o $(OBJDIR)/codeBinaire.o $(OBJDIR)/fileDePriorite.o $(OBJDIR)/octet.o $(OBJDIR)/stats.o $(OBJDIR)/table.o

# # Cible par défaut
# all: $(BINDIR)/huffman $(BINDIR)/testArbre $(BINDIR)/testCodeBinaire $(BINDIR)/testFile $(BINDIR)/testOctet


# # Compilation des fichiers .o
# $(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
# 	$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

# # Compilation des tests
# $(BINDIR)/testArbre: $(SRCDIR)/tests/testArbre.c $(OBJS)
# 	$(CC) $(CFLAGS) -I/opt/homebrew/opt/cunit -I$(INCDIR) -o $@ $^

# $(BINDIR)/testCodeBinaire: $(SRCDIR)/tests/testCodeBinaire.c $(OBJS)
# 	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

# $(BINDIR)/testFile: $(SRCDIR)/tests/testFile.c $(OBJS)
# 	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

# $(BINDIR)/testOctet: $(SRCDIR)/tests/testOctet.c $(OBJS)
# 	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

# # Compilation du programme principal
# $(BINDIR)/huffman: $(SRCDIR)/main.c $(OBJS)
# 	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

# # Nettoyage
# clean:
# 	rm -f $(OBJDIR)/*.o $(BINDIR)/huffman $(BINDIR)/testArbre $(BINDIR)/testCodeBinaire $(BINDIR)/testFile $(BINDIR)/testOctet

# .PHONY: all clean

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
LDFLAGS = -lcunit
DOXYGEN = doxygen Doxyfile
DOC = $(DOCDIR)/html

OBJS = $(OBJDIR)/arbre.o $(OBJDIR)/codeBinaire.o $(OBJDIR)/fileDePriorite.o $(OBJDIR)/octet.o $(OBJDIR)/stats.o $(OBJDIR)/table.o

all : $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(SRCDIR)/main.c $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I$(INCLUDEDIR)

doc : $(DOC)

$(DOC) :	
	$(DOXYGEN)
	cd $(DOCDIR)/latex;make;cd ../..

tests : $(TESTDIR)/testArbre $(TESTDIR)/testCodeBinaire $(TESTDIR)/testOctet $(TESTDIR)/testTable

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