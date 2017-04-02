#pragma once
#include <stdio.h>
#include <math.h>

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
extern int AllegroFont, SCREEN_WIDTH, SCREEN_HEIGHT, SCENE_NOW, EventManagerThreadRunning;
float SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font;
extern ALLEGRO_PATH *path;

#define DEBUG_MODE 0

#define LEVEL_SIZE 4
#define TILE_SIZE 64
#define SRPITES_AMOUNT 256
#define BUTTONS_COUNT 256

#define MAINMENU_SCENE 0
#define LEVEL_SELECT_SCENE 1
#define LEVEL_SCENE 2
#define LEVEL_SCENE_PAUSE 3
