#include "LibraryMerger.h"

#define BUTTONS_COUNT 256
char * buttonsTexts[BUTTONS_COUNT] = { 0 };
int spritesId[BUTTONS_COUNT] = { -1 };
int buttonsId[BUTTONS_COUNT] = { 0 };
int buttonsScene[BUTTONS_COUNT] = { 0 };
int (*callBacks[BUTTONS_COUNT])(int id) = {0};
float buttonsPos[BUTTONS_COUNT][2] = { 0 };
float buttonsSize[BUTTONS_COUNT][2] = { 0 };
int buttonsColorsRGB[BUTTONS_COUNT][3]= {255,255,255};
int buttonScount = 0;

void renderButtonsSc()
{
	for (int i = 0; i < buttonScount; i++)
	{
		if (buttonsScene[i] == SCENE_NOW || buttonsScene[i] == -1)
		{
			ALLEGRO_COLOR color = al_map_rgb(buttonsColorsRGB[i][0], buttonsColorsRGB[i][1], buttonsColorsRGB[i][2]);
			if(spritesId[i] == -1)
				al_draw_rounded_rectangle(buttonsPos[i][0], buttonsPos[i][1], buttonsPos[i][0]+buttonsSize[i][0], buttonsPos[i][1]+buttonsSize[i][1], 5, 5, color, 5);
			int textX = (2 * buttonsPos[i][0] + buttonsSize[i][0]) / 2, textY = (2 * buttonsPos[i][1] + buttonsSize[i][1]) / 2;
			al_draw_textf(AllegroFont, color, textX, textY, ALLEGRO_ALIGN_CENTER, "%s", buttonsTexts[i]);
		}
	}
	

	return;
}
void initButtons()
{
	AllegroFont = al_create_builtin_font();
	renderScreen();
}
int addButton(char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId)
{
	buttonsColorsRGB[buttonScount][0] = red; buttonsColorsRGB[buttonScount][1] = blue; buttonsColorsRGB[buttonScount][2] = green;
	buttonsPos[buttonScount][0] = x; buttonsPos[buttonScount][1] = y;
	buttonsSize[buttonScount][0] = w; buttonsSize[buttonScount][1] = h;
	buttonsScene[buttonScount] = scene;
	buttonsTexts[buttonScount] = text;
	buttonsId[buttonScount] = buttonId;
	callBacks[buttonScount] = callback;
	spritesId[buttonScount] = -1;
	buttonScount++;
	renderScreen();
	if (buttonScount < BUTTONS_COUNT)
		return buttonScount;
	else
		return -1;//maxium amount of buttons is reached!
}

int addButtonSprite(char * src, char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId, int layer)
{
	buttonsColorsRGB[buttonScount][0] = red; buttonsColorsRGB[buttonScount][1] = blue; buttonsColorsRGB[buttonScount][2] = green;
	buttonsPos[buttonScount][0] = x; buttonsPos[buttonScount][1] = y;
	buttonsSize[buttonScount][0] = w; buttonsSize[buttonScount][1] = h;
	buttonsScene[buttonScount] = scene;
	buttonsTexts[buttonScount] = text;
	spritesId[buttonScount] = addSprite(src, x, y, w, h, scene, layer);
	buttonsId[buttonScount] = buttonId;
	callBacks[buttonScount] = callback;
	buttonScount++;
	renderScreen();
	if (buttonScount < BUTTONS_COUNT)
		return buttonScount;
	else
		return -1;//maxium amount of buttons is reached!
}
int detectButtons(float x, float y)
{
	int detectedButton = -1;
	for (int i = buttonScount-1; i >=0 ; i--)
	{
		if (x > buttonsPos[i][0] && y > buttonsPos[i][1] && x < (buttonsSize[i][0] + buttonsPos[i][0]) && y < (buttonsSize[i][1] + buttonsPos[i][1]) && buttonsScene[i]== SCENE_NOW)
		{
			detectedButton = i;
			i = buttonScount;
			break;
		}
	}
	if(detectedButton >= 0 && *callBacks[detectedButton] != NULL)
		detectedButton = (*callBacks[detectedButton]) (buttonsId[detectedButton]);
	return detectedButton;
}
void makeList(int count, char **names, int x, int y, int w, int h, int(*callBacks[])(int id), int scene)
{
	for (int i = 0; i < count; i++)
		addButton(names[i], x, y+h*i, w, h, 255, 255, 255, (*callBacks[i]), scene, i);
	renderScreen();
}

void makeListSprites(int count, char **names, char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer)
{
	for (int i = 0; i < count; i++)
		addButtonSprite(src, names[i], x, y + h*i+15, w, h, 255, 255, 255, (*callBacks[i]), scene, i, layer);
	renderScreen();
}
void makeGrid(int rows, int colums, char **names, int x, int y, int w, int h, int(*callBacks[])(int id), int scene)
{
	for (int i = 0; i < rows*colums; i++)
		addButton(names[i], x+w*(i%colums), y + h*(i/rows), w, h, 255, 255, 255, (*callBacks[i]), scene, i);
	renderScreen();
}
void makeGridSprites(int rows, int colums, char **names, char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer)
{
	for (int i = 0; i < rows*colums; i++)
		addButtonSprite(src, names[i], x + w*(i%colums), y + h*(i / rows), w, h, 255, 255, 255, (*callBacks[i]), scene, i, layer);
	renderScreen();
}