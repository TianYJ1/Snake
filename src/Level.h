#pragma once
void onLevelFileOpened(int levelNum, int playerX, int playerY, int cratesCount);
void renderMap();
void movePlayer(int up, int right);
int onPause(int id);
int onExit(int id);
int onResume(int id);