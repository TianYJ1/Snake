#include "LibraryMerger.h"

#define MAP_OFFSET 100
int generate(int map[LEVEL_HEIGHT][LEVEL_WIDTH], int cratesCount);
int map[LEVEL_HEIGHT][LEVEL_WIDTH];/* =
{
	{1,1,1,1},
	{ 1,0,0,1 },
	{ 1,0,0,1 },
	{ 1,1,1,1 }
};*/
int playerSpriteId = 0;
int mapSprites[LEVEL_HEIGHT][LEVEL_WIDTH];
int onPause(int id)
{
	changeScene(LEVEL_SCENE_PAUSE);
	//clearButtons(LEVEL_SCENE);
	addButtonSprite("Button_exit.png", "", SCREEN_WIDTH_UNIT * 1100, SCREEN_HEIGHT_UNIT * 1000, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*onExit), LEVEL_SCENE_PAUSE, 0, 0);
	addButtonSprite("Button_play.png", "", SCREEN_WIDTH_UNIT * 900, SCREEN_HEIGHT_UNIT * 1000, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*onResume), LEVEL_SCENE_PAUSE, 0, 0);
	renderScreen();

	return 1;
}
int onExit(int id)
{
	changeScene(MAINMENU_SCENE);
	clearButtons(LEVEL_SCENE);
	clearButtons(LEVEL_SCENE_PAUSE);
	renderScreen();
	return 1;
}
int onResume(int id)
{
	clearButtons(LEVEL_SCENE_PAUSE);
	changeScene(LEVEL_SCENE);
	renderScreen();
	return 1;
}
char seed[SEED_LENTGH * 8] = { 0 };
char cratesSeed[SEED_LENTGH * 8] = { 0 };
int regen(int id)
{
	clearSprites(LEVEL_SCENE, 2);
	memset(seed, 0, SEED_LENTGH * 8);
	memset(cratesSeed, 0, SEED_LENTGH * 8);
	generateSeed(&seed,25);
	
	addButtonSprite("", seed, SCREEN_WIDTH_UNIT * 500, SCREEN_HEIGHT_UNIT * 1500, SCREEN_WIDTH_UNIT * 800, 150, 255, 255, 255, NULL, LEVEL_SCENE, 0, 0);
	addButtonSprite("", cratesSeed, SCREEN_WIDTH_UNIT * 500, SCREEN_HEIGHT_UNIT * 1700, SCREEN_WIDTH_UNIT * 800, 150, 255, 255, 255, NULL, LEVEL_SCENE, 0, 0);
	generate(map, 3);
	renderMap();
	renderScreen();
}
/*
1 A-Z //rooms sizes
2 0-9 //empty wall
3 1-9 //amount of empty
4 A-F //crates amount in room
5 0-9
6 0-9 //postion x
7 0-9
8 0-9 //postion y
*/


int x = 0, y = 0;
void onLevelOpened(int levelId)
{
	
	generateSeed(&seed, 5);
	generate(map, 3);
	renderMap();
	addButtonSprite("btntile.png", "Regen", SCREEN_WIDTH_UNIT*1500, 0, SCREEN_WIDTH_UNIT * 200, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*regen), LEVEL_SCENE, 0, 0);
	addButtonSprite("Button_pause.png","", 0, 0, SCREEN_WIDTH_UNIT*100, SCREEN_WIDTH_UNIT*100, 255, 255, 255, (*onPause),LEVEL_SCENE, 0, 0);
	
	int i = 0;
	for (; i < LEVEL_HEIGHT - 5; i++)
	{
		if (map[i][i] == 0)
			break;
	}
	x = i; y = i;
	playerSpriteId = addSprite("Level/Player/Character1.png", SCREEN_WIDTH_UNIT* MAP_OFFSET + TILE_SIZE*SCREEN_WIDTH_UNIT*i, SCREEN_WIDTH_UNIT *MAP_OFFSET + TILE_SIZE*SCREEN_WIDTH_UNIT*i, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, SCENE_NOW, 3);
	renderScreen();
}
void renderMap()
{
	addSprite("Level/Tiles/Ground_Sand.png", SCREEN_WIDTH_UNIT *MAP_OFFSET, SCREEN_WIDTH_UNIT *MAP_OFFSET, (TILE_SIZE-2)*SCREEN_WIDTH_UNIT*LEVEL_WIDTH, (TILE_SIZE-2)*SCREEN_WIDTH_UNIT*LEVEL_HEIGHT, SCENE_NOW, 2);
	for (int q = 0; q < LEVEL_HEIGHT; q++)
	{
		for (int i = 0; i < LEVEL_WIDTH; i++)
		{
			int x = i*(TILE_SIZE-2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT *MAP_OFFSET, y = q*(TILE_SIZE-2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT * MAP_OFFSET;
			switch (map[i][q])
			{
				case 0:
					
					break;
				case 1:
					mapSprites[i][q] = addSprite("Level/Tiles/WallRound_Brown.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, SCENE_NOW, 2);
					break;
				case 2:
					mapSprites[i][q] = addSprite("Level/Tiles/EndPoint_Brown.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, SCENE_NOW, 2);
					break;
				case 3:
					mapSprites[i][q] = addSprite("Level/Tiles/Crate_Black.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, SCENE_NOW, 2);
					break;
			}
		}
	}
}

void movePlayer(int up, int right)
{ 
	int newX = x, newY = y;
	bool assign = true;
	newX += right; newY -= up;
	if (map[newX][newY] == 1)
		assign = false;
	Log_i(__func__, "\n\t%i\n%i\t\t%i\n\t%i", map[newX][newY - 1], map[newX - 1][newY], map[newX + 1][newY], map[newX][newY + 1]);
	if (map[newX][newY] == 3)
	{
		Log_i(__func__, "Crate detected");
		if (map[newX + right][newY - up ] == 0 || map[newX + right][newY - up] == 2)
		{
			if (map[newX + right][newY - up] == 0)
			{
			}
			
				
				Log_i(__func__, "Changed crate place");
				
			mapSprites[newX + right][newY - up] = mapSprites[newX][newY];
			map[newX + right][newY - up] = 3;
			map[newX][newY] = 0;
			moveSpriteTo(mapSprites[newX][newY], (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*(newX + right) + SCREEN_WIDTH_UNIT* MAP_OFFSET, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*(newY - up) + SCREEN_WIDTH_UNIT* MAP_OFFSET);
		}
		else
			assign = false;
	}
	if (assign)
	{
		x = newX; y = newY;
		if (up == 1)
			changeSprite(playerSpriteId, "Level/Player/Character7.png");
		if (up == -1)
			changeSprite(playerSpriteId, "Level/Player/Character4.png");
		if (right == 1)
			changeSprite(playerSpriteId, "Level/Player/Character2.png");
		if (right == -1)
			changeSprite(playerSpriteId, "Level/Player/Character1.png");
		moveSpriteTo(playerSpriteId, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*x + SCREEN_WIDTH_UNIT* MAP_OFFSET, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*y + SCREEN_WIDTH_UNIT* MAP_OFFSET);
	}
}