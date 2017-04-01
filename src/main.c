// sokoban.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#define KEY_MAX 32
ALLEGRO_KEY
bool keyrel(int k) {

	static bool initialized = false;
	static bool keyp[KEY_MAX];

	if (!initialized)
	{
		// Set the keyp (key pressed) flags to false
		for (int i = 0; i < KEY_MAX; i++) keyp[i] = false;
		initialized = true;
	}

	// Now for the checking
	// Check if the key was pressed
	if (key[k] && !keyp[k])
	{
		// Set the flag and return
		keyp[k] = true;
		return false;
	}
	else if (!key[k] && keyp[k])
	{
		// The key was released
		keyp[k] = false;
		return true;
	}
	// Nothing happened?
	return false;

}
int main()
{
	al_init();
	al_init_font_addon();
	al_init_primitives_addon();
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	printf("%s", al_install_mouse() ? "mouse ok" : "mouse fail");
	ALLEGRO_DISPLAY* display = al_create_display(800, 600);
	ALLEGRO_FONT* font = al_create_builtin_font();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(font, al_map_rgb(255, 0, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!");
	ALLEGRO_COLOR color = al_map_rgb(255, 0, 0);
	
	al_draw_line(700, 0, 720, 40, color, 5.0);
	al_draw_line(720, 0, 700, 40, color, 5.0);
	al_flip_display();
	int loop = 1;
	ALLEGRO_MOUSE_STATE state;

	
	while (loop)
	{
		al_get_mouse_state(&state);
		if (al_mouse_button_down(state.buttons, 1))
			loop = 0;
	}
	//al_rest(5.0);
	system("pause");
	al_destroy_font(font);
	al_destroy_display(display);
	
	return 0;
    
}

