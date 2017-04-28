#pragma once
void onLevelEditorOpened();
void loadFromFile(const char * src, ...);
void renderMapLE();
int mouseClicked(int x, int y);
int onRightMouseClicked(int x, int y);
int playLevel(int i);