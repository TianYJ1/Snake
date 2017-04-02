#pragma once

void initButtons();
int addButton(char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId);
int detectButtons(float x, float y);
void renderButtonsSc();
void makeList(int count, char **names, int x, int y, int w, int h, int(*callBacks[])(int id), int scene);
void makeGrid(int rows, int colums, char **names, int x, int y, int w, int h, int(*callBacks[])(int id), int scene);
int addButtonSprite(char * src, char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId, int layer);
void makeGridSprites(int rows, int colums, char **names, char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer);