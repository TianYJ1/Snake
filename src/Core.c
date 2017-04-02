#include "LibraryMerger.h"
ALLEGRO_FONT* font = NULL;
int AllegroFont, SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0, SCENE_NOW = 0, EventManagerThreadRunning = 1;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_PATH *path;

void initAddons()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_native_dialog_addon();
	al_install_keyboard();
	al_init_image_addon();
}
void renderScreen()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for(int i = 0; i < 64;i++)
		renderSprites(i);
	renderButtonsSc();
	al_flip_display();
	renderSprites(-1);
}
void changeScene(int scene)
{
	SCENE_NOW = scene;
	renderScreen();
	
}
void printLog(char *str)
{
	//al_show_native_message_box(display, "Log:", "",str, 0, 0, ALLEGRO_MESSAGEBOX_WARN);
	printf("%s\n", str);
}
void setNewScreen()
{
	
	
	ALLEGRO_DISPLAY_MODE  disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_acknowledge_resize(display);
	float newWidth = al_get_display_width(display), newHeight = al_get_display_height(display);
	float wC = newWidth/SCREEN_WIDTH, hC = newHeight / SCREEN_HEIGHT ;
	SCREEN_WIDTH = newWidth; SCREEN_HEIGHT = newHeight;
	al_resize_display(display, SCREEN_WIDTH, SCREEN_HEIGHT);
	printf("New screen:%i %i, coef=%f,%f\n", SCREEN_WIDTH, SCREEN_HEIGHT, wC,hC);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	SCREEN_WIDTH_UNIT = SCREEN_WIDTH / 2000.0;
	SCREEN_HEIGHT_UNIT = SCREEN_HEIGHT / 2000.0;
	//SCREEN_WIDTH -= 250; SCREEN_HEIGHT -= 40;
	recalcSprites(wC, hC);
	recalcButtons(wC, hC);
	
	renderScreen();
}
void initVars()
{
	srand(time(NULL));
	AllegroFont = al_create_builtin_font();
	font  = al_load_ttf_font("SansPosterBold.ttf", 24, 0);

	ALLEGRO_DISPLAY_MODE  disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	
	SCREEN_WIDTH = disp_data.width; SCREEN_HEIGHT = disp_data.height;
	printf("Screen:%i %i\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	if (DEBUG_MODE)
	{
		SCREEN_WIDTH /= 2; SCREEN_HEIGHT /= 2;
	}
	else 
		SCREEN_WIDTH /= 2; SCREEN_HEIGHT /= 2;
	//else
		//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "res");
	al_change_directory(al_path_cstr(path, '/'));  // change the working directory
	printf("Res path:%s\n", al_path_cstr(path, '/'));
	SCREEN_WIDTH_UNIT = SCREEN_WIDTH / 2000.0;
	SCREEN_HEIGHT_UNIT = SCREEN_HEIGHT / 2000.0;
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	//SCREEN_WIDTH -= 250; SCREEN_HEIGHT -= 40;
	al_clear_to_color(al_map_rgb(0, 0, 0));
}
int openLevel(int num)
{
	printf("\nOpening Level #%i", num + 1);
	changeScene(LEVEL_SCENE);
	onLevelOpened(num);
	return 1;
}