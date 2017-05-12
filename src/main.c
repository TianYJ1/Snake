#include "LibraryMerger.h"
char * pathCur;
char names [128][128] = {0};
char levelsPaths[256][128] = { 0 };
char levelsNames[64][BUTTONS_NAME_SIZE];
extern float SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT;
int levelSelectPage = 0, yOffset = 0;

int main(void)
{
	//if(!DEBUG_MODE)
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
	printf("qqq\n");
	initAddons();
	if (initVars() < 0)
	{
		Log_e(__func__, "InitVars error");
		return -1;
	}
	initButtons();
	Log_i(__func__, "Initied\n================\n");
	int(*callBacks[])(int id) = { openLevelSelect,ExitProg, sliceFile, openLevelEditor };
	char names[][BUTTONS_NAME_SIZE] = { "Level Select\0" ,"Exit\0" ,"Slice Levels","Level Editor"};

	char *p = (char*)malloc(strlen(resourcePath)+16);
	sprintf(p,"%s",resourcePath);
	free(resourcePath);

	resourcePath = (char*)malloc(strlen(resourcePath) + 16);
	sprintf(resourcePath, "%sLevels", p);
	pathCur = resourcePath;
	addButton("TL", 0, 0, 50, 50, 255, 255, 255, NULL,0,0);
	addButton("TR", SCREEN_WIDTH-50, 0, 50, 50, 255, 255, 255, NULL, MAINMENU_SCENE,0);
	addButton("BL", 0, SCREEN_HEIGHT-50, 50, 50, 255, 255, 255, NULL, MAINMENU_SCENE,0);
	addButton("BR", SCREEN_WIDTH-50, SCREEN_HEIGHT-50, 50, 50, 255, 255, 255, NULL, MAINMENU_SCENE,0);
	
	makeListSprites(4,names, "btntile.png", SCREEN_WIDTH/2-125, 25, 250, SCREEN_HEIGHT_UNIT *150, callBacks, MAINMENU_SCENE, 1);
	//sliceFile();
	addSprite("back.jpg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, -1, 0);
	Log_i(__func__, "Added button");
	renderScreen();
	
	resourcePath = (char*)malloc(strlen(resourcePath) + 16);
	putMem(getUnformatted("tt_%i", 0), getUnformatted("m_%i", 1));
	putMem(getUnformatted("tt_%i", 2), getUnformatted("m_%i", 1));
	
	
	initEventManager();//last to be called untill die
	saveMem();
	//al_rest(5.0);
	//system("pause");
	//al_destroy_font(font);
	//al_destroy_display(display);
	//al_destroy_path(path);
	return 0;

}


