#include "LibraryMerger.h"
#define LEVEL_SIZE 4
#define TILE_SIZE 16
int map[LEVEL_SIZE][LEVEL_SIZE]=
{
	{1,1,1,1},
	{ 1,0,0,1 },
	{ 1,0,0,1 },
	{ 1,1,1,1 }
};
int playerSpriteId = 0;
int mapSprites[LEVEL_SIZE][LEVEL_SIZE];
void onLevelOpened(int levelId)
{
	playerSpriteId = addSprite("Level/Player/Character1.png", TILE_SIZE*5, TILE_SIZE*5, TILE_SIZE, TILE_SIZE, SCENE_NOW, 3);
	renderMap();
}
void renderMap()
{
	for (int i = 0; i < LEVEL_SIZE; i++)
	{
		for (int q = 0; q < LEVEL_SIZE; q++)
		{
			int x = i*TILE_SIZE + TILE_SIZE*5, y = q*TILE_SIZE + TILE_SIZE*5;
			switch (map[i][q])
			{
				case 0:
					mapSprites[i][q] = addSprite("Level/Tiles/Ground_Sand.png", x, y, TILE_SIZE, TILE_SIZE, SCENE_NOW, 2);
					break;
				case 1:
					mapSprites[i][q] = addSprite("Level/Tiles/WallRound_Brown.png", x, y, TILE_SIZE, TILE_SIZE, SCENE_NOW, 2);
					break;
			}
		}
	}
}
void movePlayer(int up, int right)
{
	if (up == 1)
		moveSprite(playerSpriteId, 0, -TILE_SIZE);
	if (up == -1)
		moveSprite(playerSpriteId, 0, TILE_SIZE);
	if (right == 1)
		moveSprite(playerSpriteId, TILE_SIZE, 0);
	if (right == -1)
		moveSprite(playerSpriteId, -TILE_SIZE, 0);
}