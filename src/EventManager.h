#pragma once
/*!
@file EventManager.h
\defgroup EventManager EventManager
@{

@author arseniy899
\brief EventManager\n
This is 'class' for working on user events (keyboard pressing, mouse click)
*/
/**
   Function to proccess key pressing down
   @param key Allgero's key code of button clicked
   @return 0 until overdefinition
*/
int onKeyDown(int key);
/**
   Function to proccess key being pressing (holding)
   @param key Allgero's key code of button being pressed
   @return 0 until overdefinition
*/
int onKeyPressed(int key);
/**
   Function to proccess key releasing
   @param key Allgero's key code of button released
   @return 1 if key was detected, 0 - if not
*/
int onKeyUp(int key);
/**
   Function to proccess mouse wheel rotating
   @param dir distance has changed from last function call
   @return 0 until overdefinition
*/
int onMouseWheel(float dir);
/**
   Function to proccess mouse clicks
   @param x position by x
   @param y position by y
   @return 1 if key was detected, 0 - if not
*/
int onMouseClick(float x, float y);
/**
   Function to proccess mouse holding
   @param button allegro's button of mouse
   @param x position by x
   @param y position by y
   @return 1 if key was detected, 0 - if not
*/
int onMouseHold(int button, float x, float y);
/**
   Function to proccess mouse releasing
   @param x position by x
   @param y position by y
   @return 1 if key was detected, 0 - if not
*/
int onMouseRightClick(float x, float y);
/**
   Function to init Event Manager
   @return 0 if no errors happened
*/
int initEventManager();
/**
@}
*/