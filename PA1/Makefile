CC = gcc
CFLAGS = -Wall -Iinclude
SRCDIR = src
OBJDIR = obj
BINDIR = bin
EXEC = $(BINDIR)/ed

SRC = $(SRCDIR)/mat.c $(SRCDIR)/matop.c

OBJ = $(OBJDIR)/mat.o $(OBJDIR)/matop.o

all: $(EXEC)

$(EXEC): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)

run: $(EXEC)
	./$(EXEC) -s -x 5 -y 5
	./$(EXEC) -m -x 5 -y 5
	./$(EXEC) -t -x 5 -y 5