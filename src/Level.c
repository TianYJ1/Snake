#include "LibraryMerger.h"

#define MAP_OFFSET 100
int generate(int map[LEVEL_HEIGHT][LEVEL_WIDTH], char * seed, char * cratesSeed);
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
	generateSeed(&seed, &cratesSeed, 8, 1);
	
	addButtonSprite("", seed, SCREEN_WIDTH_UNIT * 500, SCREEN_HEIGHT_UNIT * 1500, SCREEN_WIDTH_UNIT * 800, 150, 255, 255, 255, NULL, LEVEL_SCENE, 0, 0);
	addButtonSprite("", cratesSeed, SCREEN_WIDTH_UNIT * 500, SCREEN_HEIGHT_UNIT * 1700, SCREEN_WIDTH_UNIT * 800, 150, 255, 255, 255, NULL, LEVEL_SCENE, 0, 0);
	generate(map, &seed, &cratesSeed);
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



void onLevelOpened(int levelId)
{
	playerSpriteId = addSprite("Level/Player/Character1.png", SCREEN_WIDTH_UNIT* MAP_OFFSET, SCREEN_WIDTH_UNIT *MAP_OFFSET, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, SCENE_NOW, 3);
	generateSeed(&seed, &cratesSeed, 2, 2);
	generate(map, &seed, &cratesSeed);
	renderMap();
	addButtonSprite("btntile.png", "Regen", SCREEN_WIDTH_UNIT*1500, 0, SCREEN_WIDTH_UNIT * 200, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*regen), LEVEL_SCENE, 0, 0);
	addButtonSprite("Button_pause.png","", 0, 0, SCREEN_WIDTH_UNIT*100, SCREEN_WIDTH_UNIT*100, 255, 255, 255, (*onPause),LEVEL_SCENE, 0, 0);
	renderScreen();
}
void renderMap()
{
	for (int i = 0; i < LEVEL_WIDTH; i++)
	{
		for (int q = 0; q < LEVEL_HEIGHT; q++)
		{
			int x = i*(TILE_SIZE-2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT *MAP_OFFSET, y = q*(TILE_SIZE-2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT * MAP_OFFSET;
			switch (map[i][q])
			{
				case 0:
					mapSprites[i][q] = addSprite("Level/Tiles/Ground_Sand.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, SCENE_NOW, 2);
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
int x = 0, y = 0;
void movePlayer(int up, int right)
{
	if (up == 1 && y>0)
		y--;
	if (up == -1 && y < (LEVEL_HEIGHT-1))
		y++;
	if (right == 1 && x < (LEVEL_WIDTH-1))
		x++;
	if (right == -1 && x>0)
		x--;
	moveSpriteTo(playerSpriteId, (TILE_SIZE-2)*SCREEN_WIDTH_UNIT*x + SCREEN_WIDTH_UNIT* MAP_OFFSET, (TILE_SIZE-2)*SCREEN_WIDTH_UNIT*y+ SCREEN_WIDTH_UNIT* MAP_OFFSET);
}