#pragma once
struct SpriteS
{
	ALLEGRO_BITMAP * bmp;
	int id,scene, layer;
	float posX, posY, width, height;
};
typedef struct SpriteS Sprite;
int addSprite(char * src, int x, int y, int w, int h, int scene, int layer);
int addSpriteBmp(ALLEGRO_BITMAP * src, int x, int y, int w, int h, int scene, int layer);
void renderSprites(int layer);
int moveSprite(int spriteId, int x, int y);
void recalcSprites(float hC, float vC);
void clearSpritesScene(int scene);
void clearSpritesLayer(int layer);
void clearSprites(int scene, int layer);
int moveSpriteTo(int spriteId, int x, int y);
void changeSprite(int spriteId, const char * src, ...);
Sprite *getStruct(int id);
