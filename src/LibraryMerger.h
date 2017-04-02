#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <allegro5/allegro_native_dialog.h>
#include "Button.h"
#include "EventManager.h"
#include "SpriteRenderer.h"
#include "Level.h"
#include "Core.h"
extern int AllegroFont, SCREEN_WIDTH, SCREEN_HEIGHT, SCENE_NOW, EventManagerThreadRunning;
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_FONT* font;
extern ALLEGRO_PATH *path;
