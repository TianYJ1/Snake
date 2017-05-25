#pragma once
/*!
@file Button.h
\defgroup Button Button
@{
@author arseniy899
\brief Button\n
This is for managing and rendering buttons
*/   

struct ButtonS
{
   char * text;//<! Text on the button
   int id/*!< Unique id of label for search by it */, spriteId/*!< Unique id of sprite for button*/, scene;//!< scene id on which this label should be rendered
   float posX, posY, width, height;
   int r, g, b;//<! color RGB
   int(*callback)(int);//!< pointer to callback
};
typedef struct ButtonS Button;
void initButtons();
/** Add new button
   @param text [in] text on button
   @param x [in] postion by x in px
   @param y [in] postion by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param red [in] color of text in red
   @param green [in] color of text in green
   @param blue [in] color of text in blue
   @param callback [in] pointer to callback function which should be called when button press
   @param scene [in] scene id on which this label should be rendered
   @param buttonId [in] button's id to be assigned (should be unique), will be sent to callback function as i
   @return button id
*/
int addButton(char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId);
/** Detecting if any button was clicked by user using mouse
   @param x [in] postion by x in px
   @param y [in] postion by y in px
   @return button's clicked id, or -1 if not any
*/
int detectButtons(float x, float y);
/** Being called when rendering buttons
*/
void renderButtonsSc();
/** Add new buttons as list (vertical)
   @param count [in] amount of buttons
   @param names [in] names(texts) of buttons
   @param x [in] postion of list begining by x in px
   @param y [in] postion of list begining by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param (*callBacks[]) [in] pointer to callback function which should be called when button press
   @param scene [in] scene id on which this label should be rendered
*/
void makeList(int count, char names[][BUTTONS_NAME_SIZE], int x, int y, int w, int h, int(*callBacks[])(int id), int scene);
/** Add new buttons as grid
   @param count [in] amount of buttons
   @param colums [in] amount of colums
   @param names [in] names(texts) of buttons
   @param x [in] postion of list begining by x in px
   @param y [in] postion of list begining by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param (*callBacks[]) [in] pointer to callback function which should be called when button press
   @param scene [in] scene id on which this label should be rendered
*/
void makeGrid(int count, int colums, char names[][BUTTONS_NAME_SIZE], int x, int y, int w, int h, int(*callBacks[])(int id), int scene);
/** Add new button with sprite
   @param src [in] path to source of sprite
   @param text [in] text on button
   @param x [in] postion by x in px
   @param y [in] postion by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param red [in] color of text in red
   @param green [in] color of text in green
   @param blue [in] color of text in blue
   @param *callBack [in] pointer to callback function which should be called when button press
   @param scene [in] scene id on which this label should be rendered
   @param buttonId [in] button's id to be assigned (should be unique), will be sent to callback function as i
   @param layer [in] layer number for sprite to appear on the screen
   @return button id
   
*/
int addButtonSprite(char * src, char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId, int layer);
/** Add new buttons as grid
   @param src [in] path to source of sprite
   @param count [in] amount of buttons
   @param colums [in] amount of colums
   @param names [in] names(texts) of buttons
   @param x [in] postion of list begining by x in px
   @param y [in] postion of list begining by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param (*callBacks[]) [in] pointer to callback function which should be called when button press
   @param scene [in] scene id on which this label should be rendered
   @param layer [in] layer number for sprite to appear on the screen
*/
void makeGridSprites(int count, int colums, char names[][BUTTONS_NAME_SIZE], char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer);
/** Being called when screen was resized
   @param hC [in] coefficient of resizing in horizontal
   @param vC [in] coefficient of resizing in vertical
*/
void recalcButtons(float hC, float vC);
void clearButtons(int scene);
/** Add new buttons as grid
   @param src [in] path to source of sprite
   @param count [in] amount of buttons
   @param names [in] names(texts) of buttons
   @param x [in] postion of list begining by x in px
   @param y [in] postion of list begining by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param (*callBacks[]) [in] pointer to callback function which should be called when button press
   @param scene [in] scene id on which this label should be rendered
   @param layer [in] layer number for sprite to appear on the screen
*/
void makeListSprites(int count, char names[][BUTTONS_NAME_SIZE], char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer);

/**
@}
*/