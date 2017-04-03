#pragma once
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#if     _WIN32_WINNT < 0x0500
#undef  _WIN32_WINNT
#define _WIN32_WINNT   0x0500
#endif
#include <windows.h>

#include <allegro5/allegro.h>
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

#define LEVEL_HEIGHT 10
#define LEVEL_WIDTH 10
#define SEED_LENTGH 3
#define TILE_SIZE 64
#define SRPITES_AMOUNT 2048
#define BUTTONS_COUNT 1024


#define MAINMENU_SCENE 0
#define LEVEL_SELECT_SCENE 1
#define LEVEL_SCENE 2
#define LEVEL_SCENE_PAUSE 3

extern int AllegroFont, SCREEN_WIDTH, SCREEN_HEIGHT, SCENE_NOW, EventManagerThreadRunning;
float SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font;
extern ALLEGRO_PATH *path;

extern int map[LEVEL_HEIGHT][LEVEL_WIDTH];