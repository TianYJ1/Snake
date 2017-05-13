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
void initAddons();
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
int openFolderDialog(int i);

int sliceFile(int i);
int nextPage(int i);
int prevPage(int i);
int openLevelSelect(int i);
int showDirectoryListing(int i);
int openLevelEditor(int i);
int ExitProg(int i);
extern char names [128][128];
extern char * pathCur;
extern char names [128][128];
extern char levelsPaths[256][128];
extern char levelsNames[64][BUTTONS_NAME_SIZE];
extern int levelSelectPage, yOffset;
/**
@}
*/