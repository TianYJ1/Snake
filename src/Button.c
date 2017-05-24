#include "LibraryMerger.h"
ArrayElement * buttonsArr = NULL;
Button *getStructButton(int i)
{
	Button *curButt = malloc(sizeof(Button));
	Button *newBt = (Button *)get(buttonsArr, i);
	if (newBt)
	{
		memcpy(curButt, newBt, sizeof(Button));
		return newBt;
	}
	else
		return NULL;
}
void renderButtonsSc()
{
	for (int i = 0; i < arraySize(buttonsArr); i++)
	{
		Button *curButt = getStructButton(i);
		if (curButt->scene == SCENE_NOW || curButt->scene == -1)
		{
			ALLEGRO_COLOR color = al_map_rgb(curButt->r, curButt->g, curButt->b);
			if(curButt->spriteId == -1)
				al_draw_rounded_rectangle(curButt->posX, curButt->posY, curButt->posX+ curButt->width, curButt->posY+ curButt->height, 5, 5, color, 5);
			int textX = curButt->posX + curButt->width/ 2, textY = curButt->posY + curButt->height / 3;
			al_draw_textf(font, color, textX, textY, ALLEGRO_ALIGN_CENTER, "%s", curButt->text);
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
	Button newButton;
	newButton.text = text;
	newButton.id = buttonId;
	newButton.callback = callback;
	newButton.spriteId = -1;
	newButton.posX = x; newButton.posY = y;
	newButton.width = w; newButton.height = h;
	newButton.scene = scene; 
	newButton.r = red; newButton.g = green; newButton.b = blue;
	return add(&buttonsArr, (byte *)&newButton, sizeof(newButton));
}

int addButtonSprite(char * src, char * text, float x, float y, float w, float h, int red, int blue, int green, int(*callback)(int), int scene, int buttonId, int layer)
{
	Button newButton;
	newButton.text = text;
	newButton.id = buttonId;
	newButton.callback = callback;
	newButton.posX = x; newButton.posY = y;
	newButton.width = w; newButton.height = h;
	newButton.scene = scene;
	newButton.r = red; newButton.g = green; newButton.b = blue;
	if(strlen(src) >0)
		newButton.spriteId = addSprite(src, x, y, w, h, scene, layer);
	else
		newButton.spriteId = -1;
	return add(&buttonsArr, (byte *)&newButton, sizeof(newButton));
}
int detectButtons(float x, float y)
{
	int detectedButton = -1;
	Button *curButt = getStructButton(0);
	for (int i = arraySize(buttonsArr)-1; i >=0 ; i--)
	{
		curButt = getStructButton(i);
		if (x > curButt->posX && y > curButt->posY && x < (curButt->posX + curButt->width) && y < (curButt->posY + curButt->height) && curButt->scene== SCENE_NOW)
		{
			detectedButton = i;
			i = arraySize(buttonsArr);
			break;
		}
	}
	if(detectedButton >= 0 && curButt->callback != NULL)
		detectedButton = (*curButt->callback) (curButt->id);
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
	
	int rows = ceil(count / colums)+ ceil(count % colums);
	if (count < colums)
		rows = 1;
	if (count == 0 || colums == 0 || rows == 0)
		return;
	Log_i(__func__, "Grid:%iX%i, count=%i", rows, colums, count);
	for (int i = 0; i < count; i++)
		addButtonSprite(src, names[i], x + (w+15)*(i%(colums)), y + (15+h)*(i / (colums)), w, h, 255, 255, 255, (*callBacks[i]), scene, i, layer);

	renderScreen();
}
void recalcButtons(float hC, float vC)
{
	
	for (int i = 0; i < arraySize(buttonsArr); i++)
	{
		Button *curButt = getStructButton(i);
		curButt->posX *= hC; curButt->posY *= vC;
		curButt->width *= hC; curButt->height *= vC;
		set(buttonsArr, i, (byte *)&curButt, sizeof(curButt));
	}
	renderButtonsSc();
}
void clearButtons(int scene)
{
	ArrayElement *cur = buttonsArr;
	while (cur)
	{
		Button * curButt = (Button *)cur->container;
		ArrayElement *next = cur->linkToNext;
		if (curButt->scene == scene)
			removeElOb(&buttonsArr, cur);
		if (!next)
			break;
		cur = next;
		
	}
	clearSpritesScene(scene);
	clearLabels(scene);
}
