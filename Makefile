SHELL = /bin/sh

PROJECT  := sokoban

# ------------------
# External programs
# ------------------
CC  := gcc -g -w
RM  := rm -rf

# --------------------
# Directories & Files
# --------------------
D_SRC    := ./src
D_TESTS  := $(D_SRC)/tests
D_UNITY	 :=~/Unity

ENTRY_POINT := $(D_SRC)/main.c

FILES_PROGR_C :=  $(filter-out $(ENTRY_POINT), $(wildcard $(D_SRC)/*.c))
FILES_TESTS_C :=  $(wildcard $(D_TESTS)/*.c) $(D_UNITY)/src/unity.c $(D_UNITY)/extras/fixture/src/unity_fixture.c

PROJECT_WITHOUT_TESTS := $(FILES_PROGR_C) $(ENTRY_POINT)
PROJECT_WITH_TESTS := $(FILES_TESTS_C) $(FILES_PROGR_C)

PROJECT_WITHOUT_TESTS_O  := $(PROJECT_WITHOUT_TESTS:.c=.o)
PROJECT_WITH_TESTS_O  := $(PROJECT_WITH_TESTS:.c=.o)

# ------------
# Flags 
# ------------
CFLAGS  := -lm
CFLAGS  += -std=c99
LFLAGS  :=
LIBS := `pkg-config --libs allegro-5 allegro_font-5 allegro_image-5 allegro_image-5 allegro_memfile-5 allegro_primitives-5 allegro_image-5 allegro_image-5 allegro_acodec-5 allegro_ttf-5 allegro_main-5.0 allegro_dialog-5` -lm
INCS := -I $(D_UNITY)/src -I $(D_UNITY)/extras/fixture/src 

# ------------
# Targets 
# ------------
default: $(PROJECT)

tests: test-$(PROJECT)

check: test-$(PROJECT)
	./test-$(PROJECT)

%.o: %.c
	$(CC) -c -I $(D_SRC) $(INCS) $(CFLAGS) $< -o $@

$(PROJECT): $(PROJECT_WITHOUT_TESTS_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(PROJECT_WITHOUT_TESTS_O) -o $@  $(LIBS)

test-$(PROJECT): $(PROJECT_WITH_TESTS_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(PROJECT_WITH_TESTS_O) -o $@ $(LIBS) $(INCS)

.phony:	clean
clean:
	-$(RM) $(PROJECT_WITH_TESTS_O) $(PROJECT) test-$(PROJECT)
