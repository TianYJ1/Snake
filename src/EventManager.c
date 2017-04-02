#include "LibraryMerger.h"
int onKeyDown(int key)
{
	return 0;
}
int onKeyPressed(int key)
{
	return 0;
}
int onKeyUp(int key)
{
	switch (key)
	{
		case ALLEGRO_KEY_ESCAPE:
			if (SCENE_NOW == 0)
				EventManagerThreadRunning = false;
			else
				changeScene(SCENE_NOW - 1);
			return 1;
		break;
		case ALLEGRO_KEY_D:
		case ALLEGRO_KEY_RIGHT:
			movePlayer(0, 1);
		break;
		case ALLEGRO_KEY_A:
		case ALLEGRO_KEY_LEFT:
			movePlayer(0, -1);
			break;
		case ALLEGRO_KEY_W:
		case ALLEGRO_KEY_UP:
			movePlayer(1, 0);
			break;
		case ALLEGRO_KEY_S:
		case ALLEGRO_KEY_DOWN:
			movePlayer(-1, 0);
			break;
		default:
			return 0;
		break;
	}
}
int onMouseClick(float x, float y)
{
	if (detectButtons(x, y) > 0)
		return 1;
	else
		return 0;
}
int initEventManager()
{
	
	ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
	EventQueue = al_create_event_queue();
	if (EventQueue == NULL)
	{
		al_show_native_message_box(display, "Error!", "Failed to create the event queue.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	printLog("Initied EventM");
	printf("%s", al_install_mouse() ? "mouse ok" : "mouse fail");
	al_register_event_source(EventQueue, al_get_display_event_source(display));
	al_register_event_source(EventQueue, al_get_keyboard_event_source());
	al_register_event_source(EventQueue, al_get_mouse_event_source());
	

	int keyPressed = -1;
	while (EventManagerThreadRunning)
	{
		ALLEGRO_EVENT Event;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);
		al_wait_for_event(EventQueue, &Event);
		//bool get_event = al_wait_for_event_until(EventQueue, &Event, &timeout);
		if (keyPressed > 0)
			onKeyDown(keyPressed);
		
		switch (Event.type)
		{
			case ALLEGRO_EVENT_KEY_DOWN:
				keyPressed = Event.keyboard.keycode;
				onKeyDown(keyPressed);
			break;
			case ALLEGRO_EVENT_KEY_UP:
				onKeyUp(keyPressed);
				keyPressed = -1;
			break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				onMouseClick(Event.mouse.x, Event.mouse.y);
			break;
		}
		
	}

	return 0;
}