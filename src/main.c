#include "LibraryMerger.h"


int openLevelSelect()
{
	
	changeScene(1);
	int levelsAmount = 10;
	int(*callBacks[64])(int id) ;
	int **names;
	names = malloc((levelsAmount+1) * sizeof(*names));
	for (int i = 0; i < levelsAmount; i++)
	{
		names[i]= malloc(64 * sizeof(char));
		sprintf(names[i],"L%i",i+1);
		callBacks[i] = &openLevel;
		
	}
	char(*namesArr)[64] = names;
	makeGridSprites(3,3, namesArr, "btntile.png", SCREEN_WIDTH / 2 - 200, 150, 50, 50, callBacks, 1, 1);
	
}
void Exit()
{
	EventManagerThreadRunning = 0;
}
int main()
{
	initAddons();
	initVars();
	initButtons();
	printLog("Initied");
	int(*callBacks[3])(int id) = { openLevelSelect,Exit };
	int **names;
	names = malloc(3 * sizeof *names);
	names[0] = "Level Select";
	names[1]= "Exit";
	char(*namesArr) [64]= names;
	
	addButton("TL", 0, 0, 50, 50, 255, 255, 255, NULL,0,0);
	addButton("TR", SCREEN_WIDTH-50, 0, 50, 50, 255, 255, 255, NULL, 0,0);
	addButton("BL", 0, SCREEN_HEIGHT-50, 50, 50, 255, 255, 255, NULL, 0,0);
	addButton("BR", SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 50, 50, 255, 255, 255, NULL, 0,0);
	makeListSprites(2,namesArr, "btntile.png", SCREEN_WIDTH/2-100, 50, 200, 100, callBacks, 0, 1);

	addSprite("back.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, -1, 0);
	printLog("Added button");
	initEventManager();//last to be called untill die
	//al_rest(5.0);
	//system("pause");
	//al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_path(path);
	return 0;
    
}
