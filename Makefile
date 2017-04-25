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
FILES_C  := $(wildcard $(D_SRC)/*.c)
FILES_O  := $(FILES_C:.c=.o)

# ------------
# Flags 
# ------------
CFLAGS  := -lm
LFLAGS  := 
#LIBS := -lallegro -lallegro_font -lallegro_image -lallegro_primitives -lallegro_ttf -lallegro_main -lallegro_dialog
#LIBS :=  -Lhome/allegro5/allegro/build/lib 
LIBS := `pkg-config --libs allegro-5 allegro_font-5 allegro_image-5 allegro_image-5 allegro_memfile-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_main-5.0 allegro_dialog-5`
# ------------
# Targets 
# ------------
	#$(CC) -c -I. $(D_SRC) -L. -lallegro -o $@
	#$(CC) -c -I $(LIBS) $(D_SRC) $(CFLAGS) $< -o  $@
default: $(PROJECT)
%.o: %.c
	$(CC) -c -I $(D_SRC) $(CFLAGS) $< -o  $@

$(PROJECT): $(FILES_O)
#	$(CC) -I -o $(D_SRC) $(FILES_O) ~/$@ -lallegro 
	$(CC) -I $(D_SRC) $(LFLAGS) $(FILES_O) -o $@ $(LIBS) -lm
.phony:	clean
clean:
	-$(RM) $(FILES_O) $(PROJECT)



