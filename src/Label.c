#include "LibraryMerger.h"
ArrayElement * labelsArr = NULL;
Label *getStructLabel(int i)
{
   Label *curLab = malloc(sizeof(Label));
   Label *newLab = (Label *)get(labelsArr, i);
   if (newLab)
   {
      memcpy(curLab, newLab, sizeof(Label));
      return newLab;
   }
   else
   {
      if (curLab)
         free(curLab);
      return NULL;
   }
}
void renderLabelsSc()
{
   for (int i = 0; i < arraySize(labelsArr); i++)
   {
      Label *curLab = getStructLabel(i);
      if (curLab->scene == SCENE_NOW || curLab->scene == -1)
      {
         ALLEGRO_COLOR color = al_map_rgb(curLab->r, curLab->g, curLab->b);
         al_draw_textf(font, color, curLab->posX, curLab->posY, curLab->align, "%s", curLab->text);
      }
   }


   return;
}
int addLabel(float x, float y, int red, int green, int blue, int scene, int align,const char *text, ...)
{
   char buf[DEFAULT_LENGTH_STR];
   va_list vl;
   va_start(vl, text);
   vsnprintf(buf, sizeof(buf), text, vl);
   va_end(vl);
   Label newLabel;
   newLabel.text = malloc(sizeof(buf));
   sprintf(newLabel.text, "%s", buf);
   newLabel.id = arraySize(labelsArr);
   newLabel.posX = x; newLabel.posY = y;
   newLabel.scene = scene;
   newLabel.align = align;
   newLabel.r = red; newLabel.g = green; newLabel.b = blue;
   return add(&labelsArr, (byte *)&newLabel, sizeof(newLabel));
}
int changeText(int labelId, const char *text, ...)
{
   if (labelId <  arraySize(labelsArr))
   {
      char buf[DEFAULT_LENGTH_STR];
      va_list vl;
      va_start(vl, text);
      vsnprintf(buf, sizeof(buf), text, vl);
      va_end(vl);
      Label *curLabel = getStructLabel(labelId);
      curLabel->text = malloc(sizeof(buf));
      memcpy(curLabel->text, buf, sizeof(buf));
      set(labelsArr, labelId, (byte *)curLabel, sizeof(curLabel));
      renderScreen();
      return 0;
   }
   else return -1;
}
void recalcLabels(float hC, float vC)
{

   for (int i = 0; i < arraySize(labelsArr); i++)
   {
      Label *curLab = getStructLabel(i);
      curLab->posX *= hC; curLab->posY *= vC;
      set(labelsArr, i, (byte *)curLab, sizeof(curLab));
   }
   renderLabelsSc();
}
void clearLabels(int scene)
{
   ArrayElement *cur = labelsArr;
   while (cur)
   {
      Label * curButt = (Label *)cur->container;
      ArrayElement *next = cur->linkToNext;
      if (curButt->scene == scene)
         removeElOb(&labelsArr, cur);
      if (!next)
         break;
      cur = next;
   }
}
