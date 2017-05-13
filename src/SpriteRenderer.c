#include "LibraryMerger.h"
ArrayElement * spritesArr = NULL;
int addSprite(char * src, int x, int y, int w, int h, int scene, int layer)
{
	ALLEGRO_BITMAP * bmp = al_load_bitmap(src);
	if (bmp == NULL)
	{
		Log_e(__func__, "ERROR Loading sprite %s:No file", src);
		return -1;
	}
	return addSpriteBmp(bmp, x, y, w, h, scene, layer);
}
int lastId = 0;
int addSpriteBmp(ALLEGRO_BITMAP * src, int x, int y, int w, int h, int scene, int layer)
{
	Sprite newSprite;
	newSprite.bmp = src;
	newSprite.id = arraySize(spritesArr);
	newSprite.posX = x; newSprite.posY = y;
	newSprite.width = w; newSprite.height = h;
	newSprite.scene = scene; newSprite.layer = layer;
	add(&spritesArr, (byte *)&newSprite, sizeof(newSprite));
	return newSprite.id;
}
void changeSprite(int spriteId, const char * src, ...)
{
	char buf[1024];
	va_list vl;
	va_start(vl, src);
	vsnprintf(buf, sizeof(buf), src, vl);
	va_end(vl);
	ArrayElement *cur = spritesArr;
	int i = 0;
	while (cur->linkToNext)
	{
		Sprite * curSprite = (Sprite *)cur->container;
		if (curSprite->id == spriteId)
			break;
		cur = cur->linkToNext;
		i++;
	}
	Sprite * curSprite = (Sprite *)cur->container;
	ALLEGRO_BITMAP * bmp = al_load_bitmap(buf);
	if (bmp == NULL)
	{
		Log_e(__func__, "ERROR Loading sprite %s:No file", buf);
		return -1;
	}
	curSprite->bmp = bmp;
	set(spritesArr, i, curSprite, sizeof(curSprite));
}
void renderSrpite(int id)
{

}
void renderSprites(int layer)
{
	for (int i = 0; i < arraySize(spritesArr); i++)
	{
		Sprite *curSprite = getStruct(i);

		int sprLayer = curSprite->layer, sprScene = curSprite->scene;
		if ((sprLayer == -1 || sprLayer == layer) && (sprScene == SCENE_NOW || sprScene == -1) && curSprite->bmp)
		{
			al_draw_scaled_bitmap(curSprite->bmp,
				0, 0,                                // source origin
				al_get_bitmap_width(curSprite->bmp),     // source width al_get_bitmap_width(sprites[i])
				al_get_bitmap_height(curSprite->bmp),    // source height al_get_bitmap_height(sprites[i])
				curSprite->posX, curSprite->posY,   // target origin
				curSprite->width, curSprite->height, // target dimensions
				0                                    // flags
			);
		}
	}
}
Sprite *getStruct(int i)
{
	Sprite *curSprite = malloc(sizeof(Sprite));
	Sprite *newSpr = get(spritesArr, i);
	
	if (newSpr)
	{
		memcpy(curSprite, newSpr, sizeof(Sprite));
		return curSprite;
	}
	else
		return NULL;
}
int moveSprite(int spriteId, int x, int y)
{
	if (spriteId <  arraySize(spritesArr))
	{
		Sprite * curSprite = getStruct(spriteId);
		curSprite->posX += x; curSprite->posY += y;
		set(spritesArr, spriteId, curSprite, sizeof(curSprite));
		renderScreen();
		return 0;
	}
	else return -1;
}
int moveSpriteTo(int spriteId, int x, int y)
{
	if (spriteId <  arraySize(spritesArr))
	{
		Sprite * curSprite = getStruct(spriteId);
		curSprite->posX = x; curSprite->posY = y;
		set(spritesArr, spriteId, curSprite, sizeof(curSprite));
		renderScreen();
		return 0;
	}
	else return -1;
}
void recalcSprites(float hC, float vC)
{
	for (int i = 0; i < arraySize(spritesArr); i++)
	{
		Sprite *curSprite = getStruct(i);
		curSprite->posX *= hC; curSprite->posY *= vC;
		curSprite->width *= hC; curSprite->height*= vC;
		set(spritesArr, i, curSprite, sizeof(curSprite));
	}
}
void clearSpritesScene(int scene)
{
	ArrayElement *cur = spritesArr;
	while (cur)
	{
		Sprite * curSprite = (Sprite *)cur->container;
		ArrayElement *next = cur->linkToNext;
		if (curSprite->scene == scene)
			removeElOb(&spritesArr, cur);
		if (!next)
			break;
		cur = next;
	}
}
void clearSpritesLayer(int layer)
{
	ArrayElement *cur = spritesArr;
	while (cur)
	{
		Sprite * curSprite = (Sprite *)cur->container;
		ArrayElement *next = cur->linkToNext;
		if (curSprite->layer == layer)
			removeElOb(&spritesArr, cur);
		if (!next)
			break;
		cur = next;
	}
}
void clearSprites(int scene, int layer)
{
	
	ArrayElement *cur = spritesArr;
	while (cur)
	{
		Sprite * curSprite = (Sprite *)cur->container;
		ArrayElement *next = cur->linkToNext;
		if (curSprite->layer == layer && curSprite->scene == scene)
			removeElOb(&spritesArr, cur);
		if (!next)
			break;
		cur = next;
	}
}