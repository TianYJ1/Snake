#include "LibraryMerger.h"
#define SRPITES_AMOUNT 256
ALLEGRO_BITMAP * sprites[SRPITES_AMOUNT] = { 0 };
int spritesScene[SRPITES_AMOUNT] = { 0 };
int spritesLayer[SRPITES_AMOUNT] = { 0 };
float spritePos[SRPITES_AMOUNT][2] = { 0 };
float spriteSize[SRPITES_AMOUNT][2] = { 0 };
int spritesCount = 0;
int addSprite(char * src, int x, int y, int w, int h, int scene, int layer)
{
	//al_set_path_filename(path, src);
	sprites[spritesCount] = al_load_bitmap(src);
	if (sprites[spritesCount] == NULL)
	{
		printf("ERROR Loading sprite %s:No file\n", src);
		return -1;
	}
	spritePos[spritesCount][0] = x; spritePos[spritesCount][1] = y;
	spriteSize[spritesCount][0] = w; spriteSize[spritesCount][1] = h;
	spritesScene[spritesCount] = scene;
	spritesLayer[spritesCount] = layer;
	printf("Added sprite name:%s\n", src);
	spritesCount++;
	renderScreen();
	return spritesCount - 1;
}
int addSpriteBmp(ALLEGRO_BITMAP * src, int x, int y, int w, int h, int scene, int layer)
{
	sprites[spritesCount] = src;
	spritePos[spritesCount][0] = x; spritePos[spritesCount][1] = y;
	spriteSize[spritesCount][0] = w; spriteSize[spritesCount][1] = h;
	spritesCount++;
	spritesLayer[spritesCount] = layer;
	renderScreen();
	return spritesCount - 1;
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