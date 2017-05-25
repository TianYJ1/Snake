#pragma once
/*!
@file Constants.h
\defgroup Constants Constants
@{

@author arseniy899
\brief Constants.\n
This is for defining constans for whole project
*/
//DEFINING numbers
#define DEBUG_MODE                  0//!< Debug mode is setting debug mode to true if 1. In this mode screen is half-size and windowned
#define LEVEL_HEIGHT                15 //!< Determines cells amount in height at level
#define LEVEL_WIDTH                 15 //!< Cells amount in width
#define SEED_LENTGH                 5 //!< Requried for level generator, not yet implemented
#define TILE_SIZE                   64 //!< Size of cells on level in pixels
#define SPRITES_LAYERS_AMOUNT       16 //!< Amount of layers for sprites rendering
#define LEVEL_SELECT_ITEMS_PER_PAGE 12 //!< Amount of levels showed on Level Select Scene on any page (max)
#define MAP_OFFSET                  100 //!< Offset of all objects on level

//DEFINING scenes
#define MAINMENU_SCENE              0
#define LEVEL_SELECT_SCENE          1
#define LEVEL_SCENE                 2
#define LEVEL_SCENE_PAUSE           3
#define LEVEL_SCENE_COMPLETE        4
#define LEVEL_EDITOR_SCENE          5

//DEFINING resources
#define RES_FIRS                    "res"
#define RES_SEC                     "../res"
#define RES_THIR                    "../../res"
#define DEF_LEV_FOLD                "Levels"

//DEFINING sprites - GUI
#define SPR_WIN_BACK                "GUI/win_back_hor.png"
#define ACT_BACK_SPR                "GUI/actions_back.png"
#define BACK_TITLE_SPR              "GUI/title_back.png"
#define DEF_BUT_SPR                 "btntile.png"
#define PUASE_SPR                   "GUI/Button_pause.png"
#define REPL_SPR                    "GUI/replay.png"
#define OPEN_SPR                    "GUI/open.png"
#define SAVE_SPR                    "GUI/save.png"
#define NEXT_SPR                    "GUI/next.png"
#define MENU_ICON                   "GUI/menu.png"
#define PLAY_ICON                   "Button_play.png"
#define SELECT_ARROW                "GUI/pointerArray.png"
#define LEV_COMP                    "GUI/level_complete.png"

//DEFINING sprites
#define BG_SPR                      "back.jpg"

//DEFINING sprites - objects
#define SAND_BRD_SPR                "Level/Tiles/Ground_Sand_border.png"
#define WALL_SPR                    "Level/Tiles/WallRound_Brown.png"
#define ENDPO_SPR                   "Level/Tiles/EndPoint_Brown.png"
#define CRATE_SPR                   "Level/Tiles/Crate_Black.png"
#define SAND_SPR                    "Level/Tiles/Ground_Sand.png"

//DEFINING sprites - character
#define LOGO_SPR_LINK               "Level/Player/Character4.png"
#define CHAR_SPR_PL                 "Level/Player/Character"

//DEFINING sounds
#define MENU_SAMPLE                 "Sounds/menu.wav"
#define LEVEL_SAMPLE                "Sounds/level.wav"

//DEFINING texts
#define CH_SOURCE                   "Choose source"
#define CH_FOLDER                   "Choose folder"
#define CH_DEST                     "Choose destination"
#define WH_COMPL                    "Complete"
#define SLICE_SUCC                  "Slicing is done!"
#define LEV_SEL_LABEL               "LEVEL SELECT"
#define NEXT_SYMB                   "->"
#define PREV_SYMB                   "<-"
#define LEV_SEL_MENU                "Level Select"
#define EX_MENU                     "Exit"
#define SLICE_MENU                  "Slice Levels"
#define LE_MENU                     "Level Editor"
#define PAUSE_TEXT                  "PAUSE"
#define CR_LEFT                     "Crates left:" 

//DEFINING fonts
#define TTF_SRC_LINK                "SansPosterBold.ttf"
//DEFINING workking files
#define LOGS_PATH                   "logs.txt"
#define DATA_SAVE_FILE              "saves.data"

/**
@}
*/
