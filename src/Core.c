#include "LibraryMerger.h"
ALLEGRO_FONT* font = NULL;
int AllegroFont, SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0, SCENE_NOW = 0, EventManagerThreadRunning = 1;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_FONT* font;
ALLEGRO_PATH *path;
void initAddons()
{
	al_init();
	al_init_font_addon();
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
void initVars()
{
	AllegroFont = al_create_builtin_font();
	ALLEGRO_DISPLAY_MODE  disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	SCREEN_WIDTH = disp_data.width/2; SCREEN_HEIGHT = disp_data.height/2;
	printf("Screen:%i %i\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "res");
	al_change_directory(al_path_cstr(path, '/'));  // change the working directory
	printf("Res path:%s\n", al_path_cstr(path, '/'));
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	SCREEN_WIDTH -= 250; SCREEN_HEIGHT -= 40;
	al_clear_to_color(al_map_rgb(0, 0, 0));
}
int openLevel(int num)
{
	printf("\nOpening Level #%i", num + 1);
	changeScene(2);
	onLevelOpened(num);
	return 1;
}