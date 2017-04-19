#pragma once
void onLevelFileOpened(int playerX, int playerY);
void renderMap();
void movePlayer(int up, int right);
int onPause(int id);
int onExit(int id);
int onResume(int id);