#include "LibraryMerger.h"

ALLEGRO_FONT* AllegroFont = NULL;
ALLEGRO_DISPLAY* display;
int SCENE_NOW = 0;
int EventManagerThreadRunning = 1;
int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;
void initAddons()
{
	al_init();
	al_init_font_addon();
	al_init_primitives_addon();
	al_init_native_dialog_addon();
	al_install_keyboard();
}
void changeScene(int scene)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	SCENE_NOW = scene;
	renderButtonsSc();
}
void printLog(char *str)
{
	//al_show_native_message_box(display, "Log:", "",str, 0, 0, ALLEGRO_MESSAGEBOX_WARN);
	printf("%s\n", str);
}
void initVars()
{
	AllegroFont = al_create_builtin_font();
	ALLEGRO_DISPLAY_MODE   disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	SCREEN_WIDTH = disp_data.width/2; SCREEN_HEIGHT = disp_data.height/2;
	printf("Screen:%i %i", SCREEN_WIDTH, SCREEN_HEIGHT);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	SCREEN_WIDTH -= 240; SCREEN_HEIGHT -= 30;
	al_clear_to_color(al_map_rgb(0, 0, 0));
}
int openLevel(int num)
{
	printf("\nOpening Level #%i", num+1);
	return 1;
}
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
		sprintf(names[i],"L%i",i);
		callBacks[i] = &openLevel;
		
	}
	char(*namesArr)[64] = names;
	makeGrid(3,3, namesArr, SCREEN_WIDTH / 2 - 200, 150, 150, 150, callBacks, 1);
	
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
	makeList(2, namesArr, SCREEN_WIDTH/2-100, 50, 200, 100, callBacks, 0);

	printLog("Added button");
	initEventManager();//last to be called untill die
	//al_rest(5.0);
	//system("pause");
	//al_destroy_font(font);
	al_destroy_display(display);
	
	return 0;
    
}
