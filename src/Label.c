#pragma once
#include "LibraryMerger.h"
ArrayElement * labelsArr = NULL;
Label *getStructLabel(int i)
{
	Label *curButt = malloc(sizeof(Label));
	Label *newBt = get(labelsArr, i);
	if (newBt)
	{
		memcpy(curButt, newBt, sizeof(Label));
		return newBt;
	}
	else
		return NULL;
}
void renderLabelsSc()
{
	for (int i = 0; i < arraySize(labelsArr); i++)
	{
		Label *curButt = getStructLabel(i);
		if (curButt->scene == SCENE_NOW || curButt->scene == -1)
		{
			ALLEGRO_COLOR color = al_map_rgb(curButt->r, curButt->g, curButt->b);
			al_draw_textf(font, color, curButt->posX, curButt->posY, curButt->align, "%s", curButt->text);
		}
	}


	return;
}
int addLabel(float x, float y, int red, int green, int blue, int scene, int align,const char *text, ...)
{
	char buf[1024];
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
		char buf[1024];
		va_list vl;
		va_start(vl, text);
		vsnprintf(buf, sizeof(buf), text, vl);
		va_end(vl);
		Label *curLabel = getStructLabel(labelId);
		curLabel->text = malloc(sizeof(buf));
		memcpy(curLabel->text, buf, sizeof(buf));
		set(labelsArr, labelId, curLabel, sizeof(curLabel));
		renderScreen();
		return 0;
	}
	else return -1;
}
void recalcLabels(float hC, float vC)
{

	for (int i = 0; i < arraySize(labelsArr); i++)
	{
		Label *curButt = getStructLabel(i);
		curButt->posX *= hC; curButt->posY *= vC;
		set(labelsArr, i, curButt, sizeof(curButt));
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