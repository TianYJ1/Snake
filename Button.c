#include "LibraryMerger.h"
char * buttonsTexts[BUTTONS_COUNT] = { 0 };
int spritesId[BUTTONS_COUNT] = { -1 };
int buttonsId[BUTTONS_COUNT] = { 0 };
int buttonsScene[BUTTONS_COUNT] = { 0 };
int buttonsEmpty[BUTTONS_COUNT] = { -1 };
int (*callBacks[BUTTONS_COUNT])(int id) = {0};
float buttonsPos[BUTTONS_COUNT][2] = { 0 };
float buttonsSize[BUTTONS_COUNT][2] = { 0 };
int buttonsColorsRGB[BUTTONS_COUNT][3]= {255,255,255};
int buttonScount = 0;

void renderButtonsSc()
{
	for (int i = 0; i < buttonScount; i++)
	{
		if (buttonsEmpty[i]== 0 && (buttonsScene[i] == SCENE_NOW || buttonsScene[i] == -1))
		{
			ALLEGRO_COLOR color = al_map_rgb(buttonsColorsRGB[i][0], buttonsColorsRGB[i][1], buttonsColorsRGB[i][2]);
			if(spritesId[i] == -1)
				al_draw_rounded_rectangle(buttonsPos[i][0], buttonsPos[i][1], buttonsPos[i][0]+buttonsSize[i][0], buttonsPos[i][1]+buttonsSize[i][1], 5, 5, color, 5);
			int textX = buttonsPos[i][0] + buttonsSize[i][0] / 2, textY = buttonsPos[i][1] + buttonsSize[i][1] / 3;
			al_draw_textf(font, color, textX, textY, ALLEGRO_ALIGN_CENTER, "%s", buttonsTexts[i]);
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
	int empty = -1;
	if (buttonScount > 5)
	{
		for (int i = 0; i < buttonScount; i++)
		{
			if (buttonsEmpty[i] == 1)
			{
				empty = i;
				break;
			}
		}
		
	}
	if (empty == -1)
	{
		empty = (buttonScount++);
		
	}
	buttonsEmpty[empty] = 0;
	buttonsColorsRGB[empty][0] = red; buttonsColorsRGB[empty][1] = blue; buttonsColorsRGB[empty][2] = green;
	buttonsPos[empty][0] = x; buttonsPos[empty][1] = y;
	buttonsSize[empty][0] = w; buttonsSize[empty][1] = h;
	buttonsScene[empty] = scene;
	buttonsTexts[empty] = text;
	buttonsId[empty] = buttonId;
	callBacks[empty] = callback;
	spritesId[empty] = -1;
	//renderScreen();
	if (buttonScount < BUTTONS_COUNT)
		return empty;
	else
		return -1;//maxium amount of buttons is reached!
}

int addButtonSprite(char * src, char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId, int layer)
{
	int empty = addButton(text,x,y,w,h,red,blue,green,callback,scene,buttonId);
	if(strlen(src) >0)
		spritesId[empty] = addSprite(src, x, y, w, h, scene, layer);
	else
		spritesId[empty] = -1;
	//renderScreen();
	if (buttonScount < BUTTONS_COUNT)
		return empty;
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
void makeList(int count, char names[][BUTTONS_NAME_SIZE], int x, int y, int w, int h, int(*callBacks[])(int id), int scene)
{
	for (int i = 0; i < count; i++)
		addButton(names[i], x, y+h*i, w, h, 255, 255, 255, (*callBacks[i]), scene, i);
	renderScreen();
}

void makeListSprites(int count, char names[][BUTTONS_NAME_SIZE], char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer)
{
	for (int i = 0; i < count; i++)
		addButtonSprite(src, names[i], x, y + (h + 15)*i, w, h, 255, 255, 255, (*callBacks[i]), scene, i, layer);
	renderScreen();
}
void makeGrid(int count, int colums, char names[][BUTTONS_NAME_SIZE], int x, int y, int w, int h, int(*callBacks[])(int id), int scene)
{
	int rows = ceil(count / colums);
	for (int i = 0; i < count; i++)
	{
		if (names[i] != NULL)
			addButton(names[i], x + w*(i%colums), y + h*(i / rows), w, h, 255, 255, 255, (*callBacks[i]), scene, i);
	}
	renderScreen();
}
void makeGridSprites(int count, int colums, char names[][BUTTONS_NAME_SIZE], char * src, int x, int y, int w, int h, int(*callBacks[])(int id), int scene, int layer)
{
	
	int rows = ceil(count / colums);
	
	if (count == 0 || colums == 0 || rows == 0)
		return;
	Log_i(__func__, "Grid:%iX%i, count=%i", rows, colums, count);
	for (int i = 0; i < count; i++)
		addButtonSprite(src, names[i], x + (w+15)*(i%rows), y + (15+h)*(i /rows), w, h, 255, 255, 255, (*callBacks[i]), scene, i, layer);

	renderScreen();
}
void recalcButtons(float hC, float vC)
{
	
	for (int i = buttonScount - 1; i >= 0; i--)
	{
		buttonsPos[i][0] *= hC; buttonsPos[i][1] *= vC;
		buttonsSize[i][0] *= hC; buttonsSize[i][1] *= vC;
	}
	renderButtonsSc();
}
void clearButtons(int scene)
{
	for (int i = buttonScount-1; i >=0 ; i--)
	{
		if (buttonsEmpty[i] == 0 && buttonsScene[i] == scene)
		{
			buttonsEmpty[i] = 1;
			//if (spritesId[i] != -1)
				clearSpritesScene(scene);
		}
	}
}