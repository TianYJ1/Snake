#pragma once
/*!
@file LevelEditor.h
\defgroup LevelEditor LevelEditor
@{
@author arseniy899
\brief LevelEditor\n
This is for creating and editing levels
*/
/** Being called when level editor was opened and draws map and interface
*/
void onLevelEditorOpened();
/** Being called when level editor was opened and draws map and interface
	@param src Path to source of the file to open (formatted)
*/
void loadFromFile(const char * src, ...);
/**
	Renders map from array
*/
void renderMapLE();
/** When mouse clicked, this detects if it is on map. If so - make there selected object
	@param x postion by x
	@param y postion by í
	@return 1 if clicked on map, 0 - if not
*/
int mouseClicked(int x, int y);
/** When mouse clicked, this detects if it is on map. If so - clear cell selected
	@param x postion by x
	@param y postion by í
	@return 1 if clicked on map, 0 - if not
*/
int onRightMouseClicked(int x, int y);
int playLevel(int i);

int selectEXitCrate(int i);
int selectPlayer(int i);
int selectSand(int i);
int selectWall(int i);
int selectExit(int i);
int selectCrate(int i);
/**
@}
*/