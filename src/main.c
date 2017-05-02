#include "LibraryMerger.h"
char * pathCur;
char levelsPaths[256][128] = { 0 };
extern float SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT;
int yOffset = 0;

int openFolderDialog(int i)
{

	ALLEGRO_FILECHOOSER *dialog = al_create_native_file_dialog("D:/School/Info/sokoban/src/res/","Choose folder","*.*",ALLEGRO_FILECHOOSER_FOLDER);
	if (al_show_native_file_dialog(display, dialog))
	{
	    convertConstCopy(al_get_native_file_dialog_path(dialog, 0), &pathCur);
	    showDirectoryListing(0);
	}
	return 1;
}
int openLevelSelect(int i)
{
	clearButtons(LEVEL_SELECT_SCENE);
	clearSpritesScene(LEVEL_SELECT_SCENE);
	changeScene(LEVEL_SELECT_SCENE);
	showDirectoryListing(0);
	renderScreen();

}
char levelsNames[64][BUTTONS_NAME_SIZE];
int levelSelectPage = 0;
int sliceFile(int i)
{
	int c = 0;
	char * pathSource = NULL, *pathTarget = NULL;
	ALLEGRO_FILECHOOSER *dialog = al_create_native_file_dialog("", "Choose source", "*.txt", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
	if (al_show_native_file_dialog(display, dialog))
	{
		convertConstCopy(al_get_native_file_dialog_path(dialog, 0), &pathSource);
		al_destroy_native_file_dialog(dialog);
		dialog = al_create_native_file_dialog("D:/School/Info/sokoban/src/res/", "Choose folder", "*.*", ALLEGRO_FILECHOOSER_FOLDER);
		if (al_show_native_file_dialog(display, dialog))
		{
			convertConstCopy(al_get_native_file_dialog_path(dialog, 0), &pathTarget);
			char destFileStr[256] = { 0 };
			FILE *sourceFile = fopen(pathSource, "r");
			sprintf(destFileStr, "%s/%03i.txt", pathTarget, ++c);
			FILE *destFile = fopen(destFileStr, "w+");
			if (sourceFile == NULL)
			{
				Log_e(__func__, "Source file error!\n");
				return;
			}
			char str[256];
			bool prevStrIsData = false;
			while (fgets(str, sizeof(str), sourceFile) != NULL)
			{

				Log_i(__func__, "destFileStr=%s,str=%s", destFileStr,str);
				int occur = 0;
				if (strstr(str,"#"))
					occur+=2;
				if (strstr(str,"."))
					occur++;
				if (strstr(str,"@"))
					occur+=2;
				if (strstr(str,"$"))
					occur+=2;
				if (strstr(str," "))
					occur++;
				if (occur <= 1)
				{
					//if (prevStrIsData)
						//fprintf(destFile, "%s", str);
					prevStrIsData = false;
					
				}
				else
				{
					
					if (!prevStrIsData)
					{
						sprintf(destFileStr, "%s/%3i.txt", pathTarget, c++);
						fclose(destFile);
						destFile = fopen(destFileStr, "w+");
						fprintf(destFile, "%s", str);
					}
					else fprintf(destFile, "%s", str);
					if (destFile == NULL)
					{
						Log_e(__func__, "destFile file error!\n");
						return;
					}
					
					prevStrIsData = true;
				}
			}
			fclose(destFile);
			fclose(sourceFile);
			al_show_native_message_box(display, "Complete", "Slicing is done!", "", NULL, 0);
			al_destroy_native_file_dialog(dialog);
		}
		
	}
}
int nextPage(int i)
{
	levelSelectPage++;
	clearButtons(LEVEL_SELECT_SCENE);
	clearSpritesScene(LEVEL_SELECT_SCENE);
	showDirectoryListing(0);
	renderScreen();
}
int prevPage(int i)
{
	if (levelSelectPage == 0)
		return;
	levelSelectPage--;

	clearButtons(LEVEL_SELECT_SCENE);
	clearSpritesScene(LEVEL_SELECT_SCENE);
	showDirectoryListing(0);
	renderScreen();
}
int count = 0;
int showDirectoryListing(int i)
{
	clearButtons(LEVEL_SELECT_SCENE);
	clearSpritesScene(LEVEL_SELECT_SCENE);
	addButtonSprite("btntile.png", "Change folder", SCREEN_WIDTH_UNIT * 1600, SCREEN_WIDTH_UNIT * 1, SCREEN_WIDTH_UNIT * 400, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, openFolderDialog, LEVEL_SELECT_SCENE, 1, 4);
	
	addSprite("GUI/win_back_hor.png", SCREEN_WIDTH_UNIT * 350, SCREEN_HEIGHT_UNIT * 100, SCREEN_WIDTH_UNIT * 1300, SCREEN_HEIGHT_UNIT * 1700, SCENE_NOW, 1);
	addSprite("GUI/actions_back.png", SCREEN_WIDTH_UNIT * 750, SCREEN_HEIGHT_UNIT * 1700, 500 * SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT * 200, SCENE_NOW, 1);
	addSprite("GUI/title_back.png", SCREEN_WIDTH_UNIT * 550, SCREEN_HEIGHT_UNIT * 50, 950 * SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT * 200, SCENE_NOW, 1);
	addLabel(SCREEN_WIDTH_UNIT * 1025, SCREEN_HEIGHT_UNIT * 90, 255, 90, 0, SCENE_NOW, ALLEGRO_ALIGN_CENTER, "LEVEL SELECT");


	addButtonSprite("btntile.png", "->", SCREEN_WIDTH_UNIT * 1100, SCREEN_HEIGHT_UNIT * 1700, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, nextPage, LEVEL_SELECT_SCENE, 1, 4);
	addButtonSprite("btntile.png", "<-", SCREEN_WIDTH_UNIT * 800, SCREEN_HEIGHT_UNIT * 1700, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, prevPage, LEVEL_SELECT_SCENE, 1, 4);
	addButtonSprite("GUI/replay.png", "", SCREEN_WIDTH_UNIT * 900, SCREEN_HEIGHT_UNIT * 1700, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, showDirectoryListing, LEVEL_SELECT_SCENE, 1, 4);
	addButtonSprite("GUI/open.png", "", SCREEN_WIDTH_UNIT * 1000, SCREEN_HEIGHT_UNIT * 1700, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, openFolderDialog, LEVEL_SELECT_SCENE, 1, 4);
	
	ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(pathCur);

	while (count > 0)
		sprintf(levelsNames[count--], "");
	renderScreen();
	if (al_open_directory(dir))
	{
		ALLEGRO_FS_ENTRY* file;
		Log_i(__func__, "LISTING");
		int(*callBacks[64])(int id);
        memset(levelsPaths,0,sizeof(levelsPaths));
		while (file = al_read_directory(dir))
		{
			if (file == NULL)
				Log_e(__func__, "ERROR: Level file is null");
			else
			{
				//printf("path:%s\n", al_get_fs_entry_name(file));
				char *path = NULL;
				convertConstCopy(al_get_fs_entry_name(file), &path);
				char *filename;
                filename = strrchr(path, '\\');
				if (filename == NULL)
				{
					filename = strrchr(path, '/');
					if (filename == NULL)
						filename = path;
					else
						filename++;
				}
				else
					filename++;
				if (strstr(filename, ".txt"))
				{
					
					if (count >= levelSelectPage * LEVEL_SELECT_ITEMS_PER_PAGE && (count) < (levelSelectPage + 1) * LEVEL_SELECT_ITEMS_PER_PAGE)
					{
						sprintf(levelsPaths[count - levelSelectPage * LEVEL_SELECT_ITEMS_PER_PAGE], "%s", path);
						filename[strlen(filename) - 4] = 0;
						sprintf(levelsNames[count- levelSelectPage * LEVEL_SELECT_ITEMS_PER_PAGE], "%s", filename);
						callBacks[count- levelSelectPage * LEVEL_SELECT_ITEMS_PER_PAGE] = &openLevel;
						Log_i(__func__, "Level: %s", filename);


					}
					count++;
				}
				if (count > (levelSelectPage + 1) * LEVEL_SELECT_ITEMS_PER_PAGE)
					break;
			}
		}
		al_destroy_fs_entry(file);
		if ((count - levelSelectPage * LEVEL_SELECT_ITEMS_PER_PAGE) > LEVEL_SELECT_ITEMS_PER_PAGE)
			count--;
		if ((count - levelSelectPage * LEVEL_SELECT_ITEMS_PER_PAGE)  <= 0)
			prevPage(0);
		makeGridSprites(count- levelSelectPage * LEVEL_SELECT_ITEMS_PER_PAGE, 4, levelsNames, "btntile.png", SCREEN_WIDTH_UNIT * 650, SCREEN_HEIGHT_UNIT * 400, SCREEN_WIDTH_UNIT * 150, SCREEN_WIDTH_UNIT * 150, callBacks, LEVEL_SELECT_SCENE, 1);
	}
	al_destroy_fs_entry(dir);
	Log_i(__func__, "Folder: %s", pathCur);
}
int ExitProg(int i)
{
	EventManagerThreadRunning = 0;
}
int openLevelEditor(int i)
{
	changeScene(LEVEL_EDITOR_SCENE);
	onLevelEditorOpened();
}
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

