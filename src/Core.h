#pragma once

/*!
@file Core.h
\defgroup Core Core
@{

@author arseniy899
\brief Core\n
This is for managing common and miscellaneous (screen render, logging, opening and reading files, etc.)
*/
/** Run on start, initing allgero5 addons
*/
int initAddons();
/** Changes scene to another (clear and render new screen, clear old sprites) 
   @param scene Id of scene to be shown
*/
void changeScene(int scene);
/** Outputs data to log, marked as INFO(I). Prints to console (if opened) and to log file   
   @see Log_e()
   @param tag tag which will be marked for this log line
   @param str line to be printed as formatted

   Example Usage:
   @code
       Log_i("SpritesCount","count=%i",15); // Output: I/SpritesCount::count=15
   @endcode
*/
void Log_i(const char * tag, const char *str, ...);
/** Outputs data to log, marked as ERROR(E). Prints to console (if opened) and to log file
   @see Log_i()
   @param tag tag which will be marked for this log line
   @param str line to be printed as formatted
   Example Usage:
   @code
      Log_e("Loading Sprite","Res path not found:%s","/home/user/sokoban/../res/"); // Output: E/Loading Sprite::Res path not found: /home/user/sokoban/../res/
   @endcode
*/
void Log_e(const char * tag, const char *str, ...);
int initVars();
/** Open level from file an puts it to #map
   @param num Number of level from list on page which is currently shown to user in LevelSelectScene
   @retval 0 If input file not found
   @retval 1 If level loaded successfully
*/
int openLevel(int num);
/** Method being called when game window was resized
*/
void setNewScreen();
/** Method for rendering screen. MAX 6 layers and one extra -1 for sprites
*/
void renderScreen();

/** Converts char data from source to destination with memory allocation for new one (copying).
   @param source [in] Source for copying
   @param toChr [out] Destination
*/
void convertConstCopy(const char *source, char **toChr);

/** Open dialog for user to choose folder to work with (Callback function)
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int openFolderDialog(int i);
/**
   Shows dialog for slicing file when user clicked. Then slices it and output to selected folder
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int sliceFile(int i);
/**
   Turns user to next page on level select
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int nextPage(int i);
/**
   Turns user to previous page on level select
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int prevPage(int i);
/**
   Show level select when user clicks the following button
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int openLevelSelect(int i);
/**
   When user clicks button to change folder
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int showDirectoryListing(int i);
/**
   When user selects button to open level editor
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int openLevelEditor(int i);
/** Clicked button for exiting game(Callback function)
   @param i number of button clicked
   @return doesn't matter, used int for pointing
*/
int ExitProg(int i);
extern char names [DEFAULT_LENGTH][DEFAULT_LENGTH];//!< Array for storing levels names currently vewing in level select 
extern char * pathCur; //!< Temporary string for storing current chosen 
extern char levelsPaths[DEFAULT_LENGTH][DEFAULT_LENGTH];//!< Array for storing levels pathes currently vewing in level select 
extern char levelsNames[DEFAULT_LENGTH][BUTTONS_NAME_SIZE];//!< Array for storing levels names currently vewing in level select 
extern int levelSelectPage, yOffset;
extern FILE *targetFile;//!< pointer to file where logs are written
/**
@}
*/
