#include "LibraryMerger.h"
int mapLE[LEVEL_HEIGHT][LEVEL_WIDTH];
extern int map[LEVEL_HEIGHT][LEVEL_WIDTH];
int mapSpritesLE[LEVEL_HEIGHT][LEVEL_WIDTH];
int currentInstrument = 0;
int pointerArrayId = 0;
int playerX = 0, playerY = 0;
int lastX = 0, lastY = 0;
int onRightMouseClicked(int x, int y)
{
   int temp = currentInstrument;
   currentInstrument = 0;
   int ret = mouseClicked(x, y);
   currentInstrument = temp;
   return ret;
}
int mouseClicked(int y, int x)
{
   if (lastX == x && lastY == y)
      return 0;
   x -= SCREEN_WIDTH_UNIT * 10;
   y -= SCREEN_WIDTH_UNIT * 10;
   x /= TILE_SIZE*SCREEN_WIDTH_UNIT;
   
   x -= 1;
   y /= round(TILE_SIZE*SCREEN_WIDTH_UNIT);
   //y *= 3 / 2;
   y -= 1;
   Log_i(__func__, "Detected mouse at (%i,%i)", x, y);
   if (x >= 0 && x <= LEVEL_WIDTH && y >= 0 && y <= LEVEL_HEIGHT)
   {
      lastX = x; lastY = y;
      mapLE[y][x] = currentInstrument;
      switch (currentInstrument)
      {
         case 0:
            if(mapLE[y][x] != 5 && mapLE[y][x] != 9)
               changeSprite(mapSpritesLE[y][x], SAND_BRD_SPR);
         break;
         case 1:
            changeSprite(mapSpritesLE[y][x], WALL_SPR);
         break;
         case 2:
            changeSprite(mapSpritesLE[y][x], ENDPO_SPR);
         break;
         case 3:
         case 4:
            changeSprite(mapSpritesLE[y][x], CRATE_SPR);
            break;

         case 5:
            mapLE[y][x] = 9;
            mapLE[playerY][playerX] = 0;
            changeSprite(mapSpritesLE[playerY][playerX], SAND_BRD_SPR);
            changeSprite(mapSpritesLE[y][x], LOGO_SPR_LINK);
            playerX = x; playerY = y;
         break;
      }
      
      //Log_i(__func__, "Placed %i at (%i,%i)", currentInstrument, x, y);
      
      return 1;
   }
   else return 0;
}
int saveDialog(int i)
{
   char * destFileStr;
   ALLEGRO_FILECHOOSER *dialog = al_create_native_file_dialog("", CH_DEST, "*.txt", ALLEGRO_FILECHOOSER_SAVE);
   if (al_show_native_file_dialog(display, dialog))
   {
      convertConstCopy(al_get_native_file_dialog_path(dialog, 0), &destFileStr);
      //al_destroy_native_file_dialog(dialog);
      if (!strstr(destFileStr, ".txt"))
      {
         char * newP = destFileStr;
         destFileStr = malloc(sizeof(newP) + 5);
         sprintf(destFileStr, "%s.txt", newP);
      }
      
      FILE *destFile = fopen(destFileStr, "w+");
      for (int q = 0; q < LEVEL_HEIGHT; q++)
      {
         for (int i = 0; i < LEVEL_WIDTH; i++)
         {
            char c = ' ';
            if(i == playerY && q == playerX)
               c = '@';
            switch (mapLE[i][q])
            {
               case 1:
                  c = '#';
               break;
               case 2:
                  c = '.';
               break;
               case 3:
                  c = '$';
               break;

               case 4:
                  c = '*';
               break;
               case 5:
               case 9:
                  c = '@';
               break;
            }
            fputc(c, destFile);
         }
         fprintf(destFile, "\n");
      }
      fclose(destFile);
   }
   return 0;
}
int selectSand(int i)
{
   currentInstrument = 0;
   moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
   return 0;
}
int selectWall(int i)
{
   currentInstrument = 1;
   moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
   return 0;
}
int clearEl(int i)
{
   clearSprites(LEVEL_EDITOR_SCENE, 2);
   //onLevelEditorOpened();
   for (int q = 0; q < LEVEL_HEIGHT; q++)
   {
      for (int i = 0; i < LEVEL_WIDTH; i++)
      {
         if (q == 0 && i == 0)
            mapLE[q][i] = 9;
         else
            mapLE[q][i] = 0;
      }
   }
   renderMapLE();
   return 0;
}
int selectExit(int i)
{
   currentInstrument = 2;
   moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
   return 0;
}
int selectCrate(int i)
{
   currentInstrument = 3;
   moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
   return 0;
}
int selectEXitCrate(int i)
{
   currentInstrument = 4;
   moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
   return 0;
}

int onExitLE(int i)
{
   clearButtons(LEVEL_EDITOR_SCENE);
   changeScene(MAINMENU_SCENE);
   return 0;
}
int playLevel(int i)
{
   if (SCENE_NOW != LEVEL_SCENE)
      changeScene(LEVEL_SCENE);
   int cratesCount = 0;
   for (int q = 0; q < LEVEL_HEIGHT; q++)
   {
      for (int i = 0; i < LEVEL_WIDTH; i++)
      {
         map[i][q] = mapLE[i][q];
         if (mapLE[q][i] == 3)
            cratesCount++;
      }
   }
   onLevelFileOpened(-1, playerY, playerX, cratesCount);
   return 0;   
}
int selectPlayer(int i)
{
   currentInstrument = 5;
   moveSpriteTo(pointerArrayId, SCREEN_WIDTH_UNIT * 1750, SCREEN_WIDTH_UNIT * 120 * currentInstrument);
   return 0;
}
int openFileLoadDialog(int i)
{
   char * pathSource = NULL;
   ALLEGRO_FILECHOOSER *dialog = al_create_native_file_dialog("", CH_SOURCE, "*.txt", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
   if (al_show_native_file_dialog(display, dialog))
   {
      convertConstCopy(al_get_native_file_dialog_path(dialog, 0), &pathSource);
      al_destroy_native_file_dialog(dialog);
      loadFromFile("%s", pathSource);
      
   }
   return 0;
}
void onLevelEditorOpened()
{
   for (int q = 0; q < LEVEL_HEIGHT; q++)
   {
      for (int i = 0; i < LEVEL_WIDTH; i++)
      {
         if(q == 0 && i == 0)
            mapLE[q][i] = 9;
         else
            mapLE[q][i] = 0;
      }
   }
   pointerArrayId = addSprite(SELECT_ARROW, SCREEN_WIDTH_UNIT * 1750, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, LEVEL_EDITOR_SCENE, 3);
   addButtonSprite(WALL_SPR, "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectWall), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(SAND_SPR, "", SCREEN_WIDTH_UNIT * 1870, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectSand), LEVEL_EDITOR_SCENE, 0, 3);
   
   addButtonSprite(ENDPO_SPR, "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 240, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectExit), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(CRATE_SPR, "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 360, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectCrate), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(ENDPO_SPR, "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 510, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectEXitCrate), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(CRATE_SPR, "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 480, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectEXitCrate), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(LOGO_SPR_LINK, "", SCREEN_WIDTH_UNIT * 1870, SCREEN_WIDTH_UNIT * 680, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*selectPlayer), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(OPEN_SPR, "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*openFileLoadDialog), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(SAVE_SPR, "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*saveDialog), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(PLAY_ICON, "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 240, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*playLevel), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(MENU_ICON, "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 360, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*onExitLE), LEVEL_EDITOR_SCENE, 0, 3);
   addButtonSprite(REPL_SPR, "", SCREEN_WIDTH_UNIT * 0, SCREEN_WIDTH_UNIT * 480, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*clearEl), LEVEL_EDITOR_SCENE, 0, 3);

   renderMapLE();   
}
void loadFromFile(const char * src, ...)
{
   clearSprites(LEVEL_EDITOR_SCENE, 2);
   char buf[DEFAULT_LENGTH_STR];
   va_list vl;
   va_start(vl, src);
   vsnprintf(buf, sizeof(buf), src, vl);
   va_end(vl);
   if (strlen(buf) >= 0)
   {
      FILE *sourceFile = fopen(buf, "r");
      char str[DEFAULT_LENGTH_STR];
      int y = 0;
      for (int q = 0; q < LEVEL_HEIGHT; q++)
      {
         for (int i = 0; i < LEVEL_WIDTH; i++)
            mapLE[q][i] = 0;
      }
      while (fgets(str, sizeof(str), sourceFile) != NULL)
      {
         for (int i = 0; i < strlen(str); i++)
         {
            switch (str[i])
            {
            case '1':
            case '#':
               mapLE[i][y] = 1;
               break;
            case '3':
            case '$':
               mapLE[i][y] = 3;
               break;
            case '2':
            case '.':
               mapLE[i][y] = 2;
               break;
            case '9':
            case '@':
               playerY = i; playerX = y;
               mapLE[0][0] = 0;
               mapLE[i][y] = 9;
               break;
            case '0':
            case ' ':
               mapLE[i][y] = 0;
               break;
            case '4':
            case '*':
               mapLE[i][y] = 4;
               break;
            }
         }
         y++;
         Log_i(__func__, "levelStr=%s", str);


      }
      fclose(sourceFile);
   }
   //pointerArrayId = addSprite("GUI/pointerArray.png", SCREEN_WIDTH_UNIT * 1750, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, LEVEL_EDITOR_SCENE, 2);
   renderMapLE();
}
void renderMapLE()
{
   addSprite(SAND_SPR, SCREEN_WIDTH_UNIT *MAP_OFFSET, SCREEN_WIDTH_UNIT *MAP_OFFSET, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*LEVEL_WIDTH, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*LEVEL_HEIGHT, LEVEL_EDITOR_SCENE, 2);
   for (int q = 0; q < LEVEL_WIDTH; q++)
   {
      for (int i = 0; i < LEVEL_HEIGHT; i++)
      {
         int x = i*(TILE_SIZE - 2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT *MAP_OFFSET, y = q*(TILE_SIZE - 2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT * MAP_OFFSET;
         switch (mapLE[i][q])
         {
            case 0:
               mapSpritesLE[i][q] = addSprite(SAND_BRD_SPR, x,y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT,LEVEL_EDITOR_SCENE, 2);
            break;
            case 1:
               mapSpritesLE[i][q] = addSprite(WALL_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
            break;
            case 2:
               mapSpritesLE[i][q] = addSprite(ENDPO_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
            break;
            case 3:
               mapSpritesLE[i][q] = addSprite(CRATE_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
            break;
            case 4:
               addSprite(ENDPO_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
               mapSpritesLE[i][q] = addSprite(CRATE_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
            break;

            case 5:
            case 9:
               mapSpritesLE[i][q] = addSprite(LOGO_SPR_LINK, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_EDITOR_SCENE, 2);
               //changeSprite(mapSprites[playerX][playerY], "Level/Player/Character4.png");
            break;
         }
      }
   }
   renderScreen();
}
