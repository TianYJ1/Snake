#include "LibraryMerger.h"
extern int yOffset;
int onKeyDown(int key)
{
	return 0;
}
int onKeyPressed(int key)
{
	return 0;
}

int onMouseWheel(float dir)
{
	if (dir != 0)
	{

		if (SCENE_NOW == LEVEL_SELECT_SCENE)
		{
			Log_i(__func__, "Mouse wheel:%f", dir);
			yOffset += dir;
			if (yOffset > 0)
				yOffset = 0;
			showDirectoryListing();

		}
		return 1;
	}
	else
		return 0;
}
int onKeyUp(int key)
{
	switch (key)
	{
		case ALLEGRO_KEY_ESCAPE:
			if (SCENE_NOW == MAINMENU_SCENE)
				EventManagerThreadRunning = false;
			else if (SCENE_NOW == LEVEL_SELECT_SCENE)
			{
				clearButtons(LEVEL_SELECT_SCENE);
				clearSpritesScene(LEVEL_SELECT_SCENE);
				changeScene(MAINMENU_SCENE);
				
			}
			else if (SCENE_NOW == LEVEL_SCENE_PAUSE)
				onResume(0);
			else if (SCENE_NOW == LEVEL_SCENE)
				onPause(0);
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
		case ALLEGRO_KEY_PAD_0:
		case ALLEGRO_KEY_0:
			if (SCENE_NOW == LEVEL_EDITOR_SCENE)
				selectSand(0);
		break;
		case ALLEGRO_KEY_PAD_1:
		case ALLEGRO_KEY_1:
			if (SCENE_NOW == LEVEL_EDITOR_SCENE)
				selectWall(0);
		break;
		case ALLEGRO_KEY_PAD_2:
		case ALLEGRO_KEY_2:
			if (SCENE_NOW == LEVEL_EDITOR_SCENE)
				selectExit(0);
		break;
		case ALLEGRO_KEY_PAD_3:
		case ALLEGRO_KEY_3:
			if (SCENE_NOW == LEVEL_EDITOR_SCENE)
				selectCrate(0);
		break;
		case ALLEGRO_KEY_PAD_4:
		case ALLEGRO_KEY_4:
			if (SCENE_NOW == LEVEL_EDITOR_SCENE)
				selectEXitCrate(0);
		break;
		case ALLEGRO_KEY_5:
		case ALLEGRO_KEY_9:
		case ALLEGRO_KEY_PAD_5:
		case ALLEGRO_KEY_PAD_9:
			if (SCENE_NOW == LEVEL_EDITOR_SCENE)
				selectPlayer(0);
		break;
		default:
			return 0;
		break;
	}
}
int mouseButton = -1;
int onMouseClick(float x, float y)
{
	if ((SCENE_NOW == LEVEL_EDITOR_SCENE && mouseClicked(x, y)) || detectButtons(x, y) > 0)
	{
		renderScreen();
		return 1;
	}
	else
		return 0;
}
int onMouseHold(int button, float x, float y)
{
	if (SCENE_NOW == LEVEL_EDITOR_SCENE)
	{
		if(button == 1)
			mouseClicked(x, y);
		else if (button == 2)
			onRightMouseClicked(x, y);
		return 1;
	}
	else
		return 0;
}
int onMouseRightClick(float x, float y)
{
	if ((SCENE_NOW == LEVEL_EDITOR_SCENE && onRightMouseClicked(x, y)) || detectButtons(x, y) > 0)
	{
		renderScreen();
		return 1;
	}
	else
		return 0;
}
int initEventManager()
{
	
	ALLEGRO_EVENT_QUEUE *EventQueue = NULL;
	EventQueue = al_create_event_queue();
	if (EventQueue == NULL)
	{
		Log_e(__func__, "Failed to create the event queue");
		return -1;
	}
	Log_i(__func__, "Initied EventM");
	Log_i(__func__, "%s", al_install_mouse() ? "mouse ok" : "mouse fail");
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
		if (mouseButton > 0)
			onMouseHold(mouseButton, Event.mouse.x, Event.mouse.y);
		switch (Event.type)
		{
			case ALLEGRO_EVENT_KEY_DOWN:
				keyPressed = Event.keyboard.keycode;
				onKeyDown(keyPressed);
			break;
			case ALLEGRO_EVENT_KEY_UP:
				onKeyUp(keyPressed);
				keyPressed = -1;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				mouseButton = Event.mouse.button;
			break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if(Event.mouse.button == 1)
					onMouseClick(Event.mouse.x, Event.mouse.y);
				else if(Event.mouse.button == 2)
					onMouseRightClick(Event.mouse.x, Event.mouse.y);
				mouseButton = -1;
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				EventManagerThreadRunning = false;
			break;
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				setNewScreen();
			break;
			case ALLEGRO_EVENT_MOUSE_AXES:
				onMouseWheel(Event.mouse.dz);
			break;
		}
		
	}

	return 0;
}