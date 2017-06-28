SHELL = /bin/sh

PROJECT  := snake
# ------------------
# External programs
# ------------------
CC  := gcc
RM  := rm -rf
DG  := doxygen

# --------------------
# Directories & Files
# --------------------
D_SRC    := ./src
D_DOC    := ./doc
FILES_C  := $(wildcard $(D_SRC)/*.c)
FILES_O  := $(FILES_C:.c=.o)

# ------------
# Flags
# ------------
CFLAGS  := -Wall
LFLAGS  :=

# ------------
# Targets
# ------------
default: $(PROJECT)

%.o: %.c
	$(CC) -c -I $(D_SRC) $(CFLAGS) $< -o $@

$(PROJECT): $(FILES_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(FILES_O) -o $@

.phony: doxygen
doxygen:
	$(DG) $(D_DOC)/doxygen.config

.phony: html
html: doxygen

.phony: pdf
pdf: doxygen
	make -C $(D_DOC)/output/latex

.phony:	clean
clean:
	-$(RM) $(FILES_O) $(PROJECT) $(D_DOC)/output
