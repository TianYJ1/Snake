#pragma once
/*!
@file Level.h
\defgroup Level Level
@{
@author arseniy899
\brief Level\n
This is for showing and manging gameplay on the level
*/
/** Being called when user selected level. Draw the map
   @param levelNum number of level (taken from array)
   @param playerX default postion of player by x
   @param playerY by y
   @param cratesCount amount of crates on the level

*/
void onLevelFileOpened(int levelNum, int playerX, int playerY, int cratesCount);
/**
   Re-draw the map from array if needed
*/
void renderMap();
/** Being called when user pressed keys (arrows or WASD) to move player)
   @param up direction by vertical. if 1 - move up, 0 - no move, -1 - move down
   @param right direction by vertical. if 1 - move right, 0 - no move, -1 - move left
*/
void movePlayer(int up, int right);
/** Callback for pause button
   @param id id of button clicked
*/
int onPause(int id);
/** Callback for resume button
   @param id id of button clicked
*/
int onResume(int id);
/** Callback when user solves the level. Opens menu with stats and actions (restart, next or exit)
*/
void onLevelComlete();
/**
@}
*/ 