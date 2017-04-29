#include "LibraryMerger.h"
int mapLE[LEVEL_HEIGHT][LEVEL_WIDTH];
extern int map[LEVEL_HEIGHT][LEVEL_WIDTH];
int mapSprites[LEVEL_HEIGHT][LEVEL_WIDTH];
int currentInstrument = 0;
int pointerArrayId = 0;
int playerX = 0, playerY = 0;
int lastX = 0, lastY = 0;
int onRightMouseClicked(int x, int y)
{
	int temp = currentInstrument;
	currentInstrument = 0;
	mouseClicked(x, y);
	currentInstrument = temp;
}
int mouseClicked(int y, int x)
{
	if (lastX == x && lastY == y)
		return;
	x -= SCREEN_WIDTH_UNIT * 10;
	y -= SCREEN_WIDTH_UNIT * 10;
	x /= TILE_SIZE*SCREEN_WIDTH_UNIT;
	
	x -= 1;
	y /= round(TILE_SIZE*SCREEN_WIDTH_UNIT);
	//y *= 3 / 2;
	y -= 1;
	Log_i(__func__, "Detected mouse at (%i,%i)", x, y);
	if (x >= 0 && x <= LEVEL_WIDTH && y >= 0 && y <= LEVEL_HEIGHT)
	{
		lastX = x; lastY = y;
		mapLE[y][x] = currentInstrument;
		switch (currentInstrument)
		{
			case 0:
				if(mapLE[y][x] != 5 && mapLE[y][x] != 9)
					changeSprite(mapSprites[y][x], "Level/Tiles/Ground_Sand_border.png");
			break;
			case 1:
				changeSprite(mapSprites[y][x], "Level/Tiles/WallRound_Brown.png");
			break;
			case 2:
				changeSprite(mapSprites[y][x], "Level/Tiles/EndPoint_Brown.png");
			break;
			case 3:
				changeSprite(mapSprites[y][x], "Level/Tiles/Crate_Black.png");
			break;
			case 4:
				changeSprite(mapSprites[y][x], "Level/Tiles/Crate_Black.png");
				break;

			case 5:
				mapLE[y][x] = 9;
				mapLE[playerY][playerX] = 0;
				changeSprite(mapSprites[playerY][playerX], "Level/Tiles/Ground_Sand_border.png");
				changeSprite(mapSprites[y][x], "Level/Player/Character4.png");
				playerX = x; playerY = y;
			break;
		}
		
		//Log_i(__func__, "Placed %i at (%i,%i)", currentInstrument, x, y);
		
		return 1;
	}
	else return 0;
}
int saveDialog(int i)
{
	char * destFileStr;
	ALLEGRO_FILECHOOSER *dialog = al_create_native_file_dialog("", "Choose destination", "*.txt", ALLEGRO_FILECHOOSER_SAVE);
	if (al_show_native_file_dialog(display, dialog))
	{
		convertConstCopy(al_get_native_file_dialog_path(dialog, 0), &destFileStr);
		//al_destroy_native_file_dialog(dialog);
		if (!strstr(destFileStr, ".txt"))
		{
			char * newP = destFileStr;
			destFileStr = malloc(sizeof(newP) + 5);
			sprintf(destFileStr, "%s.txt", newP);
		}
		
		FILE *destFile = fopen(destFileStr, "w+");
		for (int q = 0; q < LEVEL_HEIGHT; q++)
		{
			for (int i = 0; i < LEVEL_WIDTH; i++)
			{
				char c = ' ';
				if(i == playerY && q == playerX)
					c = '@';
				switch (mapLE[i][q])
				{
					case 1:
						c = '#';
					break;
					case 2:
						c = '.';
					break;
					case 3:
						c = '$';
					break;

					case 4:
						c = '*';
					break;
					case 5:
					case 9:
						c = '@';
					break;
				}
				fputc(c, destFile);
			}
			fprintf(destFile, "\n");
		}
		fclose(destFile);
	}
}
int selectSand(int i)
{
	currentInstrument = 0;
	moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
	
}
int selectWall(int i)
{
	currentInstrument = 1;
	moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
	
}
int clearEl(int i)
{
	clearSprites(LEVEL_EDITOR_SCENE, 2);
	//onLevelEditorOpened();
	for (int q = 0; q < LEVEL_HEIGHT; q++)
	{
		for (int i = 0; i < LEVEL_WIDTH; i++)
		{
			if (q == 0 && i == 0)
				mapLE[q][i] = 9;
			else
				mapLE[q][i] = 0;
		}
	}
	renderMapLE();
}
int selectExit(int i)
{
	currentInstrument = 2;
	moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
}
int selectCrate(int i)
{
	currentInstrument = 3;
	moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
}
int selectEXitCrate(int i)
{
	currentInstrument = 4;
	moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
}

int onExitLE(int i)
{
	clearButtons(LEVEL_EDITOR_SCENE);
	changeScene(MAINMENU_SCENE);
}
int playLevel(int i)
{
	if (SCENE_NOW != LEVEL_SCENE)
		changeScene(LEVEL_SCENE);
	int cratesCount = 0;
	for (int q = 0; q < LEVEL_HEIGHT; q++)
	{
		for (int i = 0; i < LEVEL_WIDTH; i++)
		{
			map[i][q] = mapLE[i][q];
			if (mapLE[q][i] == 3)
				cratesCount++;
		}
	}
	onLevelFileOpened(-1, playerY, playerX, cratesCount);
	
}
int selectPlayer(int i)
{
	currentInstrument = 5;
	moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
}
int openFileLoadDialog(int i)
{
	char * pathSource = NULL;
	ALLEGRO_FILECHOOSER *dialog = al_create_native_file_dialog("", "Choose source", "*.txt", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
	if (al_show_native_file_dialog(display, dialog))
	{
		convertConstCopy(al_get_native_file_dialog_path(dialog, 0), &pathSource);
		al_destroy_native_file_dialog(dialog);
		loadFromFile("%s", pathSource);
		
	}
}
void onLevelEditorOpened()
{
	for (int q = 0; q < LEVEL_HEIGHT; q++)
	{
		for (int i = 0; i < LEVEL_WIDTH; i++)
		{
			if(q == 0 && i == 0)
				mapLE[q][i] = 9;
			else
				mapLE[q][i] = 0;
		}
	}
	pointerArrayId = addSprite("GUI/pointerArray.png", SCREEN_WIDTH_UNIT * 1750, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, LEVEL_EDITOR_SCENE, 3);
	addButtonSprite("Level/Tiles/WallRound_Brown.png", "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectWall), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("Level/Tiles/Ground_Sand.png", "", SCREEN_WIDTH_UNIT * 1870, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectSand), LEVEL_EDITOR_SCENE, 0, 3);
	
	addButtonSprite("Level/Tiles/EndPoint_Brown.png", "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 240, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectExit), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("Level/Tiles/Crate_Black.png", "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 360, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectCrate), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("Level/Tiles/EndPoint_Brown.png", "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 510, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectEXitCrate), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("Level/Tiles/Crate_Black.png", "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 480, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectEXitCrate), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("Level/Player/Character4.png", "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 680, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectPlayer), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("GUI/open.png", "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*openFileLoadDialog), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("GUI/save.png", "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*saveDialog), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("Button_play.png", "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 240, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*playLevel), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("GUI/menu.png", "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 360, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*onExitLE), LEVEL_EDITOR_SCENE, 0, 3);
	addButtonSprite("GUI/replay.png", "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 480, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*clearEl), LEVEL_EDITOR_SCENE, 0, 3);
	

	renderMapLE();
	
}
void loadFromFile(const char * src, ...)
{
	clearSprites(LEVEL_EDITOR_SCENE, 2);
	char buf[1024];
	va_list vl;
	va_start(vl, src);
	vsnprintf(buf, sizeof(buf), src, vl);
	va_end(vl);
	if (strlen(buf) >= 0)
	{
		FILE *sourceFile = fopen(buf, "r");
		char str[256];
		bool prevStrIsData = false;
		int y = 0;
		for (int q = 0; q < LEVEL_HEIGHT; q++)
		{
			for (int i = 0; i < LEVEL_WIDTH; i++)
				mapLE[q][i] = 0;
		}
		int cratesCount = 0;
		while (fgets(str, sizeof(str), sourceFile) != NULL)
		{
			for (int i = 0; i < strlen(str); i++)
			{
				switch (str[i])
				{
				case '1':
				case '#':
					mapLE[i][y] = 1;
					break;
				case '3':
				case '$':
					mapLE[i][y] = 3;
					break;
				case '2':
				case '.':
					mapLE[i][y] = 2;
					break;
				case '9':
				case '@':
					playerY = i; playerX = y;
					mapLE[0][0] = 0;
					mapLE[i][y] = 9;
					break;
				case '0':
				case ' ':
					mapLE[i][y] = 0;
					break;
				case '4':
				case '*':
					mapLE[i][y] = 4;
					break;
				}
			}
			y++;
			Log_i(__func__, "levelStr=%s", str);


		}
		fclose(sourceFile);
	}
	pointerArrayId;
	//pointerArrayId = addSprite("GUI/pointerArray.png", SCREEN_WIDTH_UNIT * 1750, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, LEVEL_EDITOR_SCENE, 2);
	renderMapLE();
	pointerArrayId;
}
void renderMapLE()
{
	addSprite("Level/Tiles/Ground_Sand.png", SCREEN_WIDTH_UNIT *MAP_OFFSET, SCREEN_WIDTH_UNIT *MAP_OFFSET, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*LEVEL_WIDTH, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*LEVEL_HEIGHT, LEVEL_EDITOR_SCENE, 2);
	for (int q = 0; q < LEVEL_WIDTH; q++)
	{
		for (int i = 0; i < LEVEL_HEIGHT; i++)
		{
			int x = i*(TILE_SIZE - 2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT *MAP_OFFSET, y = q*(TILE_SIZE - 2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT * MAP_OFFSET;
			switch (mapLE[i][q])
			{
				case 0:
					mapSprites[i][q] = addSprite("Level/Tiles/Ground_Sand_border.png", x,y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT,LEVEL_EDITOR_SCENE, 2);
				break;
				case 1:
					mapSprites[i][q] = addSprite("Level/Tiles/WallRound_Brown.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
				break;
				case 2:
					mapSprites[i][q] = addSprite("Level/Tiles/EndPoint_Brown.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
				break;
				case 3:
					mapSprites[i][q] = addSprite("Level/Tiles/Crate_Black.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
				break;
				case 4:
					addSprite("Level/Tiles/EndPoint_Brown.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
					mapSprites[i][q] = addSprite("Level/Tiles/Crate_Black.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
				break;

				case 5:
				case 9:
					mapSprites[i][q] = addSprite("Level/Player/Character4.png", x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2); 
					//changeSprite(mapSprites[playerX][playerY], "Level/Player/Character4.png");
				break;
			}
		}
	}
	renderScreen();
}