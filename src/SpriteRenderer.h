#pragma once
/*!
@file SpriteRenderer.h
\defgroup SpriteRenderer SpriteRenderer
@{
@author arseniy899
\brief SpriteRenderer\n
This is for managing and rendering sprites
*/
struct SpriteS
{
   ALLEGRO_BITMAP * bmp;//!< Allegro's bitmap for storing bitmap
   int id/*!< Unique id of label for search by it */, layer/*!< At which layer sprite should be rendered*/, scene;//!< scene id on which this label should be rendered
   float posX, posY, width, height;
};
typedef struct SpriteS Sprite;
/** Add new sprite
   @param src [in] path to source of sprite
   @param x [in] postion by x in px
   @param y [in] postion by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param scene [in] scene id on which this label should be rendered
   @param layer [in] layer number on which this label should be rendered
   @return sprite id
*/
int addSprite(char * src, int x, int y, int w, int h, int scene, int layer);
/** Add new sprite
   @param src [in] bitmap of sprite
   @param x [in] postion by x in px
   @param y [in] postion by y in px
   @param w [in] width in px
   @param h [in] height by y in px
   @param layer [in] layer number on which this label should be rendered
   @param scene [in] scene id on which this label should be rendered
   @return sprite id
*/
int addSpriteBmp(ALLEGRO_BITMAP * src, int x, int y, int w, int h, int scene, int layer);
/** Being called when rendering sprites
   @param layer layer to render
*/
void renderSprites(int layer);
/** Change sprite postion
   @param spriteId [in] unique id of sprite
   @param x [in] amount in pixels to move on by x (delta)
   @param y [in] amount in pixels to move on by y (delta)
*/
int moveSprite(int spriteId, int x, int y);
/** Being called when screen was resized
   @param hC [in] coefficient of resizing in horizontal
   @param vC [in] coefficient of resizing in vertical
*/
void recalcSprites(float hC, float vC);
/** Clearing sprites for selected scene to free memory
   @param scene scene id
*/
void clearSpritesScene(int scene);
/** Clearing sprites for selected layer to free memory
   @param layer layer number
*/
void clearSpritesLayer(int layer);
/** Clearing sprites for selected scene and layer to free memory
   @param scene scene id
   @param layer layer number
*/
void clearSprites(int scene, int layer);
/** Change sprite postion
   @param spriteId [in] unique id of sprite
   @param x [in] new x
   @param y [in] new y
*/
int moveSpriteTo(int spriteId, int x, int y);
/** Converts char data from source to destination with memory allocation for new one (copying).
   @param spriteId [in] unique id of
   @param src [in] bitmap of sprite (formatted)
   @return 0 if sprite exists, else -1
*/
void changeSprite(int spriteId, const char * src, ...);
/** Get Sprite by it's index in array
   @return Sprite
*/
Sprite *getStruct(int id);
/** Get Sprite by it's id
   @return Sprite
*/
Sprite *getStructById(int id);

/**
@}
*/