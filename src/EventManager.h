#pragma once
/*!
@file EventManager.h
\defgroup EventManager EventManager
@{

@author arseniy899
\brief EventManager\n
This is 'class' for working on user events (keyboard pressing, mouse click)
*/
int onKeyDown(int key);
int onKeyPressed(int key);
int onKeyUp(int key);
int onMouseWheel(float dir);
int onMouseClick(float x, float y);
int initEventManager();
/**
@}
*/