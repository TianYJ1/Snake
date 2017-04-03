#include "LibraryMerger.h"


int openLevelSelect()
{
	clearButtons(LEVEL_SELECT_SCENE);
	changeScene(LEVEL_SELECT_SCENE);
	int cratesAmount = 10;
	int(*callBacks[64])(int id) ;
	char names[64][BUTTONS_NAME_SIZE];
	for (int i = 0; i < cratesAmount; i++)
	{
		sprintf(names[i],"%i",i+1);
		callBacks[i] = &openLevel;
		
	}
	
	ALLEGRO_COLOR color = al_map_rgb(255, 80, 80);
	addButtonSprite("","Choose crates amount:", SCREEN_WIDTH_UNIT*500, SCREEN_WIDTH_UNIT * 10, SCREEN_HEIGHT*1/8, 150, 255, 255, 255, NULL, LEVEL_SELECT_SCENE, 0, 1);
	makeGridSprites(cratesAmount,3,names, "btntile.png", SCREEN_WIDTH*4/8, SCREEN_HEIGHT * 1 / 8, 100, 100, callBacks, LEVEL_SELECT_SCENE, 1);

}
void Exit()
{
	EventManagerThreadRunning = 0;
}
int main()
{
	if(!DEBUG_MODE)
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	initAddons();
	initVars();
	initButtons();
	Log_i(__func__, "Initied\n================\n");
	int(*callBacks[3])(int id) = { openLevelSelect,Exit };
	char names[][BUTTONS_NAME_SIZE] = { "Level Select\0" ,"Exit\0" };
	
	addButton("TL", 0, 0, 50, 50, 255, 255, 255, NULL,0,0);
	addButton("TR", SCREEN_WIDTH-50, 0, 50, 50, 255, 255, 255, NULL, MAINMENU_SCENE,0);
	addButton("BL", 0, SCREEN_HEIGHT-50, 50, 50, 255, 255, 255, NULL, MAINMENU_SCENE,0);
	addButton("BR", SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 50, 50, 255, 255, 255, NULL, MAINMENU_SCENE,0);
	makeListSprites(2,names, "btntile.png", SCREEN_WIDTH/2-125, 50, 250, 150, callBacks, MAINMENU_SCENE, 1);

	addSprite("back.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, -1, 0);
	Log_i(__func__, "Added button");
	renderScreen();
	initEventManager();//last to be called untill die
	//al_rest(5.0);
	//system("pause");
	//al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_path(path);
	return 0;
    
}
