#pragma once
/*! 
@file LibraryMerger.h
\defgroup LibraryMerger Library merger
@{

@author arseniy899
	\brief LibraryMerger.\n
    Here all requried libraries ar included
*/
/*<
	Including system libraries
**/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
/*<
Including allegro5 libraries\n
Refer to [Allegro](http://liballeg.org/)\n
Requeried addons see in README.md\n
**/
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
/*<
Including all psedo-classes (managers) of the project for giving access everything to everything
**/
#include "Button.h"
#include "EventManager.h"
#include "SpriteRenderer.h"
#include "Level.h"
#include "Core.h"
#include "Array.h"
#include "Label.h"
#include "levGen.h"
#include "LevelEditor.h"
#include "MemoryWorker.h"

/*<
Defining constants
**/
#define DEBUG_MODE 0//!< Debug mode is setting debug mode to true if 1. In this mode screen is half-size and windowned

#define LEVEL_HEIGHT 15 //!< Determines cells amount in height at level
#define LEVEL_WIDTH 15 //!< Cells amount in width
#define SEED_LENTGH 5 //!< Requried for level generator, not yet implemented
#define TILE_SIZE 64 //!< Size of cells on level in pixels
#define SPRITES_LAYERS_AMOUNT 16 //!< Amount of layers for sprites rendering
#define LEVEL_SELECT_ITEMS_PER_PAGE 12 //!< Amount of levels showed on Level Select Scene on any page (max)
/*!
 \addgroup Const Constants of scenes id
	\brief Scenes id
	These ids are requried to determine which scene is currenlty running and going to be run. It's much easier to use friendly names.
@{	
*/
#define MAINMENU_SCENE 0
#define LEVEL_SELECT_SCENE 1
#define LEVEL_SCENE 2
#define LEVEL_SCENE_PAUSE 3
#define LEVEL_SCENE_COMPLETE 4
#define LEVEL_EDITOR_SCENE 5
/*! 
@}
*/
#define MAP_OFFSET 100 //!< Offset of all objects on level

extern int SCREEN_WIDTH, SCREEN_HEIGHT, SCENE_NOW, EventManagerThreadRunning; //!< Flag, which control main cycle. If it is false (0), the game stops
extern float SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT;//!< Universal screen units which are inependent from screen size. Max units - 2000. Everything is counted percent-like
extern ALLEGRO_DISPLAY* display; 
extern ALLEGRO_FONT* font, *AllegroFont; //!< Allgero font for rendering
extern ALLEGRO_PATH *path; //!< Temp var for allegro while looping over levels in selected folder
extern char * resourcePath;//!< Path to resources where system find directory if presented or null if no resources found
extern int map[LEVEL_HEIGHT][LEVEL_WIDTH]; //!< Array for storing current running level map
extern char levelsPaths[DEFAULT_LENGTH][DEFAULT_LENGTH]; //!< Array for storing paths to levels from folder selected by user to choose level from
extern char levelsNames[DEFAULT_LENGTH][BUTTONS_NAME_SIZE]; //!< Names of levels for show in level select
extern ArrayElement *spritesArr; //!< Array for storing all sprites in games (Based on Array.h: list array)
extern ALLEGRO_SAMPLE *menuSample /*!< Allegro's sample for playing in menu*/, *levelSample/*!< Allegro's sample for playing on level*/;
/**
@}
*/
