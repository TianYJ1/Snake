#pragma once
struct LabelS
{
	char * text;
	int id, scene;
	float posX, posY;
	int r, g, b, align;
};
typedef struct LabelS Label;

void renderLabelsSc();
int addLabel(float x, float y, int red, int blue, int green, int scene, int align, const char *text, ...);
int changeText(int labelId, const char *text, ...);
void recalcLabels(float hC, float vC);
void clearLabels(int scene);