#include "LibraryMerger.h"

ALLEGRO_BITMAP * sprites[SRPITES_AMOUNT] = { 0 };
int spritesScene[SRPITES_AMOUNT] = { 0 };
int spritesLayer[SRPITES_AMOUNT] = { 0 };
int spritesEmpty[SRPITES_AMOUNT] = { 0 };
float spritePos[SRPITES_AMOUNT][2] = { 0 };
float spriteSize[SRPITES_AMOUNT][2] = { 0 };
int spritesCount = 0;
int addSprite(char * src, int x, int y, int w, int h, int scene, int layer)
{
	//al_set_path_filename(path, src);
	ALLEGRO_BITMAP * bmp = al_load_bitmap(src);
	if (bmp == NULL)
	{
		printf("ERROR Loading sprite %s:No file\n", src);
		return -1;
	}
	int empty = addSpriteBmp(bmp,x,y,w,h,scene,layer);
	printf("Added sprite name:%s\n", src);
	renderScreen();
	return empty;
}
int addSpriteBmp(ALLEGRO_BITMAP * src, int x, int y, int w, int h, int scene, int layer)
{
	int empty = -1;
	if (spritesCount > 5)
	{
		for (int i = 0; i < spritesCount; i++)
		{
			if (spritesEmpty[i] == 1)
			{
				empty = i;
				break;
			}
		}

	}
	if (empty == -1)
	{
		empty = (spritesCount++);
		
	}
	spritesEmpty[empty] = 0;
	sprites[empty] = src;
	spritePos[empty][0] = x; spritePos[empty][1] = y;
	spriteSize[empty][0] = w; spriteSize[empty][1] = h;
	spritesLayer[empty] = layer;
	spritesScene[empty] = scene;
	renderScreen();
	return empty;
}
void renderSprites(int layer)
{
	for (int i = 0; i < spritesCount; i++)
	{
		if ((spritesLayer[i] == -1 || spritesLayer[i] == layer) && (spritesScene[i] == SCENE_NOW || spritesScene[i] == -1) && sprites[i] != NULL)

			al_draw_scaled_bitmap(sprites[i],
				0, 0,                                // source origin
				al_get_bitmap_width(sprites[i]),     // source width
				al_get_bitmap_height(sprites[i]),    // source height
				spritePos[i][0], spritePos[i][1],   // target origin
				spriteSize[i][0], spriteSize[i][1], // target dimensions
				0                                    // flags
			);
			
	}
}
int moveSprite(int spriteId, int x, int y)
{
	if (spriteId < spritesCount)
	{
		spritePos[spriteId][0] += x; spritePos[spriteId][1] += y;
		renderScreen();
		return 0;
	}
	else return -1;
}
void recalcSprites(float hC, float vC)
{
	for (int i = spritesCount - 1; i >= 0; i--)
	{
		spritePos[i][0] *= hC; spritePos[i][1] *= vC;
		spriteSize[i][0] *= hC; spriteSize[i][1] *= vC;
	}
}
void clearSpritesScene(int scene)
{
	for (int i = spritesCount - 1; i >=0; i--)
	{
		if (spritesEmpty[i] == 0 && spritesScene[i] == scene)
			spritesEmpty[i] = 1;
	}
}
void clearSpritesLayer(int layer)
{
	for (int i = spritesCount - 1; i >=0; i--)
	{
		if (spritesEmpty[i] == 0 && spritesLayer[i] == layer)
			spritesEmpty[i] = 1;
	}
}
void clearSprites(int scene, int layer)
{
	for (int i = spritesCount - 1; i >=0; i--)
	{
		if (spritesEmpty[i] == 0 && spritesLayer[i] == layer && spritesScene[i] == scene)
			spritesEmpty[i] = 1;
	}
}