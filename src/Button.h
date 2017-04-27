#pragma once
#define BUTTONS_NAME_SIZE 64
struct ButtonS
{
	char * text;
	int id, spriteId, scene;
	float posX, posY, width, height;
	int r, g, b;
	int(*callback)(int);
};
typedef struct ButtonS Button;
void initButtons();
int addButton(char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId);
int detectButtons(float x, float y);
void renderButtonsSc();
void makeList(int count, char names[][BUTTONS_NAME_SIZE], int x, int y, int w, int h, int(*callBacks[])(int id), int scene);
void makeGrid(int count, int colums, char names[][BUTTONS_NAME_SIZE], int x, int y, int w, int h, int(*callBacks[])(int id), int scene);
int addButtonSprite(char * src, char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId, int layer);
void makeGridSprites(int count, int colums, char names[][BUTTONS_NAME_SIZE], char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer);
void recalcButtons(float hC, float vC);
void clearButtons(int scene);
void makeListSprites(int count, char names[][BUTTONS_NAME_SIZE], char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer);
