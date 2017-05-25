#include "LibraryMerger.h"
ArrayElement * spritesArr = NULL;
int addSprite(char * src, int x, int y, int w, int h, int scene, int layer)
{
   if(strlen(src) == 0)
      return -3;
   if(layer > SPRITES_LAYERS_AMOUNT)
      return -2;
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
   if(layer > SPRITES_LAYERS_AMOUNT)
      return -2;
   if(!src)
      return -1;
   Sprite newSprite;
   newSprite.bmp = src;
   newSprite.id = lastId++;// arraySize(spritesArr);
   newSprite.posX = x; newSprite.posY = y;
   newSprite.width = w; newSprite.height = h;
   newSprite.scene = scene; newSprite.layer = layer;
   add(&spritesArr, (byte *)&newSprite, sizeof(newSprite));
   return newSprite.id;
}
void changeSprite(int spriteId, const char * src, ...)
{
   char buf[DEFAULT_LENGTH_STR];
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
      return;
   }
   curSprite->bmp = bmp;
   set(spritesArr, i, (byte *)curSprite, sizeof(curSprite));
}
void renderSprites(int layer)
{
   for (int i = 0; i < arraySize(spritesArr); i++)
   {
      Sprite *curSprite = getStruct(i);
      if (curSprite == NULL)
         continue;
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
   Sprite *newSpr = (Sprite *)get(spritesArr, i);
   if (newSpr)
   {
      memcpy(curSprite, newSpr, sizeof(Sprite));
      return curSprite;
   }
   else
   {
      if (curSprite)
         free(curSprite);
      return NULL;
   }
}
Sprite *getStructById(int id)
{
   Sprite *curSprite = malloc(sizeof(Sprite));
   ArrayElement *cur = spritesArr;
   while (cur)
   {
      curSprite = (Sprite *)cur->container;
      ArrayElement *next = cur->linkToNext;
      if (curSprite->id == id)
         break;
      if (!next)
         return NULL;
      cur = next;
   }
   return curSprite;
}
int moveSprite(int spriteId, int x, int y)
{
   Sprite * curSprite = getStructById(spriteId);
   if (curSprite)
   {
      curSprite->posX += x; curSprite->posY += y;
      set(spritesArr, spriteId, (byte *)curSprite, sizeof(curSprite));
      renderScreen();
      return 0;
   }
   else return -1;
}
int moveSpriteTo(int spriteId, int x, int y)
{
   Sprite * curSprite = getStructById(spriteId);
   if (curSprite)
   {
      
      curSprite->posX = x; curSprite->posY = y;
      set(spritesArr, spriteId, (byte *)curSprite, sizeof(curSprite));
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
      set(spritesArr, i, (byte *)curSprite, sizeof(curSprite));
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
