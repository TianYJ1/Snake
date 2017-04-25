#pragma once
#pragma warnings 1591
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>


#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>


#include "Button.h"
#include "EventManager.h"
#include "SpriteRenderer.h"
#include "Level.h"
#include "Core.h"
#include "levGen.h"
#define DEBUG_MODE 1

#define LEVEL_HEIGHT 15
#define LEVEL_WIDTH 15
#define SEED_LENTGH 5
#define TILE_SIZE 64
#define SRPITES_AMOUNT 2048
#define BUTTONS_COUNT 1024

#define LEVEL_SELECT_ITEMS_PER_PAGE 12

#define MAINMENU_SCENE 0
#define LEVEL_SELECT_SCENE 1
#define LEVEL_SCENE 2
#define LEVEL_SCENE_PAUSE 3



extern int SCREEN_WIDTH, SCREEN_HEIGHT, SCENE_NOW, EventManagerThreadRunning;
extern float SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font, *AllegroFont;
extern ALLEGRO_PATH *path;
extern char * resourcePath;
extern int map[LEVEL_HEIGHT][LEVEL_WIDTH];
extern char levelsPaths[256][128];

void showDirectoryListing();
