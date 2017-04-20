#include "LibraryMerger.h"

ALLEGRO_FONT* font = NULL;
int AllegroFont, SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0, SCENE_NOW = 0, EventManagerThreadRunning = 1;
ALLEGRO_DISPLAY* display = NULL;
float SCREEN_WIDTH_UNIT = 0, SCREEN_HEIGHT_UNIT = 0;
ALLEGRO_PATH *path;
FILE *targetFile;
char * resourcePath;
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

int threadsCount = 0;
void renderScreen()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for (int i = 0; i < 6; i++)
		renderSprites(i);
	renderSprites(-1);
	renderButtonsSc();
	al_flip_display();
	
	//al_create_thread(renderSpriteThr, NULL, -1);
	
}
void changeScene(int scene)
{
	SCENE_NOW = scene;
	renderScreen();
	
}
void Log_i(char * tag, const char *str, ...)
{
	char buf[128];
	va_list vl;
	va_start(vl, str);
	vsnprintf(buf, sizeof(buf), str, vl);
	va_end(vl);
	printf("I/%s::%s\n", tag, buf);
	fprintf(targetFile, "I/%s::%s\n",tag, buf);
	fflush(targetFile);
}
void Log_e(char * tag, const char *str, ...)
{
	char buf[128];
	va_list vl;
	va_start(vl, str);
	vsnprintf(buf, sizeof(buf), str, vl);
	va_end(vl);
	printf("E/%s::%s\n", tag, buf);
	fprintf(targetFile, "E/%s::%s\n", tag, buf);

	fflush(targetFile);
	al_show_native_message_box(display, "Error!", buf, 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
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
	Log_i(__func__, "New screen:%i %i, coef=%f,%f", SCREEN_WIDTH, SCREEN_HEIGHT, wC,hC);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	SCREEN_WIDTH_UNIT = SCREEN_WIDTH / 2000.0;
	SCREEN_HEIGHT_UNIT = SCREEN_HEIGHT / 2000.0;
	//SCREEN_WIDTH -= 250; SCREEN_HEIGHT -= 40;
	recalcSprites(wC, hC);
	recalcButtons(wC, hC);
	font = al_load_ttf_font("SansPosterBold.ttf", SCREEN_HEIGHT_UNIT * 60, 0);
	renderScreen();
}
void initVars()
{
	srand(time(NULL));
	AllegroFont = al_create_builtin_font();
	
	targetFile = fopen("logs.txt", "a+");
	if (targetFile == NULL)
	{
		printf("Target file error!\n");
		return 2;
	}
	
	ALLEGRO_DISPLAY_MODE  disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	
	SCREEN_WIDTH = disp_data.width; SCREEN_HEIGHT = disp_data.height;
	
	Log_i(__func__,"Screen:%i %i", SCREEN_WIDTH, SCREEN_HEIGHT);
	
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
	//SCREEN_WIDTH /= 2; SCREEN_HEIGHT /= 2;
	//else
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	
	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

	al_append_path_component(path, "res");
	if (!al_change_directory(al_path_cstr(path, '/')))
	{
		path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
		al_append_path_component(path, "../res");
		if (!al_change_directory(al_path_cstr(path, '/')))
		{
			Log_e(__func__, "Res path not found", al_path_cstr(path, '/'));
		}
	}
	Log_i(__func__, "Res path:%s", al_path_cstr(path, '/'));
	resourcePath = al_path_cstr(path, '/');
	SCREEN_WIDTH_UNIT = SCREEN_WIDTH / 2000.0;
	SCREEN_HEIGHT_UNIT = SCREEN_HEIGHT / 2000.0;
	font = al_load_ttf_font("SansPosterBold.ttf", -SCREEN_HEIGHT_UNIT * 80, ALLEGRO_TTF_MONOCHROME);
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	//SCREEN_WIDTH -= 250; SCREEN_HEIGHT -= 40;
	al_clear_to_color(al_map_rgb(0, 0, 0));

}
int openLevel(int num)
{
	printf("\nOpening Level #%i", levelsPaths[num]);
	FILE *sourceFile = fopen(levelsPaths[num], "r");
	char str[256];
	bool prevStrIsData = false;
	int y = 0;
	for (int q = 0; q < LEVEL_HEIGHT; q++)
	{
		for (int i = 0; i < LEVEL_WIDTH; i++)
			map[q][i] = 0;
	}
	int playerX = 0, playerY = 0;
	while (fgets(str, sizeof(str), sourceFile) != NULL)
	{
		for (int i = 0; i < strlen(str); i++)
		{
			switch (str[i])
			{
				case '1':
				case '#':
					map[y][i] = 1;
				break;
				case '3':
				case '$':
					map[y][i] = 3;
				break;
				case '2':
				case '.':
					map[y][i] = 2;
				break;
				case '9':
				case '@':
					playerX = i; playerY=y;
				break;
				case '0':
				case ' ':
					map[y][i] = 0;
				break;
			}
		}
		y++;
		Log_i(__func__, "levelStr=%s", str);
		
		
	}
	fclose(sourceFile);
	changeScene(LEVEL_SCENE);
	//onLevelOpened(num);
	onLevelFileOpened(playerX, playerY);
	return 1;
}

