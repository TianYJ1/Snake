#include "LibraryMerger.h"
/**
\mainpage Sokoban

# Sokoban-project
Sokoban (倉庫番 sōkoban, warehouse keeper) is a type of transport puzzle, in which the player pushes boxes or crates around in a warehouse, trying to get them to storage locations. The puzzle is usually implemented as a video game.

## Getting Started
This game is build using c-language and based on [Allegro](http://liballeg.org/) Library
### Directory structure
The source code is organized as follows:

Subdirectory | Description
-------------|-------------------
src/         | source files
src/tests    | unit tests
doc/         | documentation
res/     | static resources
### Structure
- \ref Main -> \ref Core - menu module
- \ref Level - level drawer, game-play handler
- \ref MemoryWorker - manager of continous memory, based on bare parser
- Managers:
   + \ref SpriteRenderer - manager for rendering sprites from bitmaps
   + \ref Button - button manager for handling clicks, writing text and placing sprites
   + \ref Label - manager for labels

### Dependencies
- [Allegro](http://liballeg.org/) framework \n
Addons using:
   + Font addon
   + Image addon
   + TTF font addon
   + Dialog addon
   + Color addon
   + Primitives addon
   + Audio addon, Audiocodec addon


### Build
To build the project, do the following:
````
make
````
To rebuild everything from scratch, do the following:
````
make clean
````
#### Building Allegro #######

#### Any Linux ####
````
cd ~; git clone git://github.com/liballeg/allegro5cd allegro5;git checkout 5.2; mkdir build; cd build
sudo ccmake -DCMAKE_INSTALL_PREFIX=/usr ..
````
Here press 'c', 'c', 'g', unpack will begin.
If an error connected to OPUS occurs, change WANT_OPUS to 'OFF' in list of packages in white box on the right side
````
sudo make;sudo make install
````
#### On Ubuntu #######
````
sudo add-apt-repository ppa:allegro/5.2
sudo apt-get update
sudo apt-get install liballegro5-dev
````
### Testing #######
#### Installing #######
Tests in project are based on [Unity Test Framework](http://www.throwtheswitch.org/unity). To get it, just type:
````
git clone https://github.com/ThrowTheSwitch/Unity.git
````
#### Building and running tests
Do the following:
````
make tests D_UNITY=<UNITY PATH>
````
where \<UNITY_PATH\> is absolute path to your directory which contains Unity. After building everything, run **test-sokoban**.
All tests will gone, if not - please, let us know
## Authors
* **Arseniy Prosvirin** - arseniy.p@d7ss.com\n
* **Ryabota Igor** - x@x.ru
## License
This project is licensed under the MIT License - see the [LICENSE](https://github.com/arseniy899/sokoban_pub/blob/master/LICENSE) file for details


*/
/*!
@file Main.c
\defgroup Main Main
@{

@author arseniy899
\brief Main\n
There main entry point exists (without tests)
*/
char * pathCur;//!< string for carrying path to folder which was last opened by user. Default: \<resource_path\>/Levels
char names [DEFAULT_LENGTH][DEFAULT_LENGTH] = {0};
char levelsPaths[DEFAULT_LENGTH][DEFAULT_LENGTH] = { 0 };
char levelsNames[DEFAULT_LENGTH][BUTTONS_NAME_SIZE] = { 0 };
int levelSelectPage = 0/*!< Page currently selected for viewing in level select*/, yOffset = 0/*!< Offset by y (needed for moving content by rotating mouse wheel, deprecated)*/;
/*<
   \brief Default entry point
   @retval  0 if no error accurued while init
   @retval -1 if error accurued while init. See runtime logs for more info
*/
int main(void)

{
   //if(!DEBUG_MODE)
      //ShowWindow(GetConsoleWindow(), SW_HIDE);
   if(initAddons() < 0)
   {
      Log_e(__func__, "InitAddons error");
      return -1;
   }
   else if (initVars() < 0)
   {
      Log_e(__func__, "InitVars error");
      return -1;
      al_destroy_font(font);
      al_destroy_display(display);
      al_destroy_path(path);
   }
   else { /* Just nothing, just to meet the criteria*/ }
   initButtons();
   Log_i(__func__, "Initied\n================\n");
   int(*callBacks[])(int id) = { openLevelSelect,ExitProg, sliceFile, openLevelEditor };
   char names[][BUTTONS_NAME_SIZE] = { LEV_SEL_MENU ,EX_MENU,SLICE_MENU,LE_MENU};

   char *p = (char*)malloc(strlen(resourcePath)+16);
   sprintf(p,"%s",resourcePath);
   free(resourcePath);

   resourcePath = (char*)malloc(strlen(resourcePath) + 16);
   sprintf(resourcePath, "%s%s", p, DEF_LEV_FOLD);
   pathCur = resourcePath;
   
   makeListSprites(4,names, DEF_BUT_SPR, SCREEN_WIDTH/2-125, 25, 250, SCREEN_HEIGHT_UNIT *150, callBacks, MAINMENU_SCENE, 1);
   //sliceFile();
   addSprite(BG_SPR, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, -1, 0);
   Log_i(__func__, "Added button");
   renderScreen();
   
   resourcePath = (char*)malloc(strlen(resourcePath) + 16);
   
   
   initEventManager();//last to be called untill die
   saveMem();
   //al_rest(5.0);
   //system("pause");
   al_destroy_font(font);
   al_destroy_display(display);
   al_destroy_path(path);
   return 0;

}
/*<
@}
*/
