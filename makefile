#MAKEFILE for Oppgave 3 LISTE HÅNDTERING

#Extendable flags
INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

#All header files
_DEPS = list.h main.h
DEPS = $(patsubst %, $(INCLDIR)/%, $(_DEPS))

#All object/source files
_OBJS = main.o list.o
OBJS = $(patsubst %, $(OBJDIR)/%, $(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#NameOfProject:
oppgave_3: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
