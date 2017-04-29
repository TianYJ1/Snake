#pragma once
void onLevelEditorOpened();
void loadFromFile(const char * src, ...);
void renderMapLE();
int mouseClicked(int x, int y);
int onRightMouseClicked(int x, int y);
int playLevel(int i);

int selectEXitCrate(int i);
int selectPlayer(int i);
int selectSand(int i);
int selectWall(int i);
int selectExit(int i);
int selectCrate(int i);