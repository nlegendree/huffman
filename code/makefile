CC = gcc
CFLAGS = -Wall -g
OBJDIR = obj
BINDIR = bin
SRCDIR = src
INCDIR = include

# Liste des fichiers .o
OBJS = $(OBJDIR)/arbre.o $(OBJDIR)/codeBinaire.o $(OBJDIR)/fileDePriorite.o $(OBJDIR)/octet.o $(OBJDIR)/stats.o $(OBJDIR)/table.o

# Cible par défaut
all: $(BINDIR)/huffman $(BINDIR)/testArbre $(BINDIR)/testCodeBinaire $(BINDIR)/testFile $(BINDIR)/testOctet

# Compilation des tests
$(BINDIR)/testArbre: $(SRCDIR)/tests/testArbre.c $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

$(BINDIR)/testCodeBinaire: $(SRCDIR)/tests/testCodeBinaire.c $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

$(BINDIR)/testFile: $(SRCDIR)/tests/testFile.c $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

$(BINDIR)/testOctet: $(SRCDIR)/tests/testOctet.c $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

# Compilation des fichiers .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $<

# Compilation du programme principal
$(BINDIR)/huffman: $(SRCDIR)/main.c $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) -o $@ $^

# Nettoyage
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/huffman $(BINDIR)/testArbre $(BINDIR)/testCodeBinaire $(BINDIR)/testFile $(BINDIR)/testOctet

.PHONY: all clean
