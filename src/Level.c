#include "LibraryMerger.h"
int map[LEVEL_HEIGHT][LEVEL_WIDTH];
int levelNumC = 0;
int onExit(int id)
{
   if (levelNumC >= 0)
      changeScene(MAINMENU_SCENE);
   else
      changeScene(LEVEL_EDITOR_SCENE);
   clearButtons(LEVEL_SCENE);
   clearButtons(LEVEL_SCENE_PAUSE);
   renderScreen();
   return 0;
}
int playerSpriteId = 0, cratesLeftLabelId = 0, pushesMade = 0, pushesMadeLabelId = 0, movesMade = 0;
int mapSprites[LEVEL_HEIGHT][LEVEL_WIDTH];
int onPause(int id)
{
   changeScene(LEVEL_SCENE_PAUSE);
   //clearButtons(LEVEL_SCENE);
   addButtonSprite(MENU_ICON, "", SCREEN_WIDTH_UNIT * 1100, SCREEN_HEIGHT_UNIT * 800, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*onExit), LEVEL_SCENE_PAUSE, 0, 4);
   addButtonSprite(PLAY_ICON, "", SCREEN_WIDTH_UNIT * 900, SCREEN_HEIGHT_UNIT * 800, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*onResume), LEVEL_SCENE_PAUSE, 0, 4);
   addSprite(SPR_WIN_BACK, SCREEN_WIDTH_UNIT * 600, SCREEN_HEIGHT_UNIT * 500, 900 * SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT * 700, LEVEL_SCENE_PAUSE, 3);
   addSprite(ACT_BACK_SPR, SCREEN_WIDTH_UNIT * 800, SCREEN_HEIGHT_UNIT * 800, 500 * SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT * 200, LEVEL_SCENE_PAUSE, 3);
   addSprite(BACK_TITLE_SPR, SCREEN_WIDTH_UNIT * 800, SCREEN_HEIGHT_UNIT * 400, 500 * SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT * 200, LEVEL_SCENE_PAUSE, 3);
   addLabel(SCREEN_WIDTH_UNIT * 1050, SCREEN_HEIGHT_UNIT * 450, 255, 90, 0, LEVEL_SCENE_PAUSE, ALLEGRO_ALIGN_CENTER, PAUSE_TEXT);
   renderScreen();

   return 0;
}

int onResume(int id)
{
   clearButtons(LEVEL_SCENE_PAUSE);
   changeScene(LEVEL_SCENE);
   renderScreen();
   return 0;
}
char seed[SEED_LENTGH * 8] = { 0 };
char cratesSeed[SEED_LENTGH * 8] = { 0 };
int regen(int id)
{
   /*clearSprites(LEVEL_SCENE, 2);
   memset(seed, 0, SEED_LENTGH * 8);
   memset(cratesSeed, 0, SEED_LENTGH * 8);
   //generateSeed(&seed,25);

   addButtonSprite("", seed, SCREEN_WIDTH_UNIT * 500, SCREEN_HEIGHT_UNIT * 1500, SCREEN_WIDTH_UNIT * 800, 150, 255, 255, 255, NULL, LEVEL_SCENE, 0, 0);
   addButtonSprite("", cratesSeed, SCREEN_WIDTH_UNIT * 500, SCREEN_HEIGHT_UNIT * 1700, SCREEN_WIDTH_UNIT * 800, 150, 255, 255, 255, NULL, LEVEL_SCENE, 0, 0);
   generate(map, 3);
   renderMap();
   renderScreen();*/
   return 0;
}
/*
1 A-Z //rooms sizes
2 0-9 //empty wall
3 1-9 //amount of empty
4 A-F //crates amount in room
5 0-9
6 0-9 //postion x
7 0-9
8 0-9 //postion y
*/
int restart(int i)
{
   clearButtons(LEVEL_SCENE);

   if (levelNumC >= 0)
      openLevel(levelNumC);
   else
      playLevel(0);
   //renderMap();
   return 0;
}

int x = 0, y = 0, cratesCountN =0;
void onLevelFileOpened(int levelNum, int playerX, int playerY, int cratesCount)
{
   renderMap();
   cratesCountN = cratesCount;
   levelNumC = levelNum;
   pushesMade = 0; movesMade = 0;
   x = playerX; y = playerY;
   addButtonSprite(REPL_SPR, "", SCREEN_WIDTH_UNIT * 1870, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*restart), LEVEL_SCENE, 0, 0);
   addButtonSprite(PUASE_SPR, "", SCREEN_WIDTH_UNIT * 1750, 0, SCREEN_WIDTH_UNIT * 120, SCREEN_WIDTH_UNIT * 120, 255, 255, 255, (*onPause), LEVEL_SCENE, 0, 0);
   cratesLeftLabelId = addLabel(SCREEN_WIDTH_UNIT * 2000, SCREEN_HEIGHT_UNIT * 1900, 255, 255, 255, LEVEL_SCENE, ALLEGRO_ALIGN_RIGHT,"$S%i", CR_LEFT,cratesCountN);
   pushesMadeLabelId = addLabel(SCREEN_WIDTH_UNIT * 2000, SCREEN_HEIGHT_UNIT * 1800, 255, 255, 255, LEVEL_SCENE, ALLEGRO_ALIGN_RIGHT, "Pushes:%i", pushesMade);
   addLabel(SCREEN_WIDTH_UNIT * 2000, SCREEN_HEIGHT_UNIT * 1700, 255, 255, 255, LEVEL_SCENE, ALLEGRO_ALIGN_RIGHT, "Level name:%s", levelsNames[levelNum]);
   playerSpriteId = addSprite(LOGO_SPR_LINK, SCREEN_WIDTH_UNIT* MAP_OFFSET + TILE_SIZE*SCREEN_WIDTH_UNIT*playerX, SCREEN_WIDTH_UNIT *MAP_OFFSET + TILE_SIZE*SCREEN_WIDTH_UNIT*playerY, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_SCENE, 3);
   renderScreen();
}
void onLevelOpened(int levelId)
{

   /*generateSeed(&seed, 5);
   //generate(map, 3);
   renderMap();
   //addButtonSprite("btntile.png", "Regen", SCREEN_WIDTH_UNIT*1500, 0, SCREEN_WIDTH_UNIT * 200, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*regen), LEVEL_SCENE, 0, 0);
   addButtonSprite("btntile.png", "Restart", SCREEN_WIDTH_UNIT * 1500, 0, SCREEN_WIDTH_UNIT * 200, SCREEN_WIDTH_UNIT * 200, 255, 255, 255, (*restart), LEVEL_SCENE, 0, 0);
   addButtonSprite("Button_pause.png","", 0, 0, SCREEN_WIDTH_UNIT*100, SCREEN_WIDTH_UNIT*100, 255, 255, 255, (*onPause),LEVEL_SCENE, 0, 0);

   int i = 0;
   for (; i < LEVEL_HEIGHT - 5; i++)
   {
      if (map[i][i] == 0)
         break;
   }
   x = i; y = i;
   playerSpriteId = addSprite("Level/Player/Character1.png", SCREEN_WIDTH_UNIT* MAP_OFFSET + TILE_SIZE*SCREEN_WIDTH_UNIT*i, SCREEN_WIDTH_UNIT *MAP_OFFSET + TILE_SIZE*SCREEN_WIDTH_UNIT*i, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, SCENE_NOW, 3);
   renderScreen();*/
}
void renderMap()
{
   addSprite(SAND_SPR, SCREEN_WIDTH_UNIT *MAP_OFFSET, SCREEN_WIDTH_UNIT *MAP_OFFSET, (TILE_SIZE-2)*SCREEN_WIDTH_UNIT*LEVEL_WIDTH, (TILE_SIZE-2)*SCREEN_WIDTH_UNIT*LEVEL_HEIGHT, SCENE_NOW, 2);
   for (int q = 0; q < LEVEL_WIDTH; q++)
   {
      for (int i = 0; i < LEVEL_HEIGHT; i++)
      {
         int x = i*(TILE_SIZE-2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT *MAP_OFFSET, y = q*(TILE_SIZE-2)*SCREEN_WIDTH_UNIT + SCREEN_WIDTH_UNIT * MAP_OFFSET;
         switch (map[i][q])
         {
            case 0:
               //mapSprites[i][q] = addSprite("Level/Tiles/Ground_Sand.png", x,y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT,SCENE_NOW, 2);
            break;
            case 1:
               mapSprites[i][q] = addSprite(WALL_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_SCENE, 2);
            break;
            case 2:
               mapSprites[i][q] = addSprite(ENDPO_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_SCENE, 2);
            break;
            case 3:
               mapSprites[i][q] = addSprite(CRATE_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_SCENE, 2);
            break;
            case 4:
               addSprite(ENDPO_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_SCENE, 2);
               mapSprites[i][q] = addSprite(CRATE_SPR, x, y, TILE_SIZE*SCREEN_WIDTH_UNIT, TILE_SIZE*SCREEN_WIDTH_UNIT, LEVEL_SCENE, 2);
            break;
         }
      }
   }
}
int openNextLevel(int i)
{
   clearButtons(LEVEL_SCENE);
   openLevel(levelNumC+1);
   return 0;
}
void onLevelComlete()
{
   clearButtons(LEVEL_SCENE);
   clearButtons(LEVEL_SCENE_COMPLETE);
   
   
   addSprite(LEV_COMP, SCREEN_WIDTH_UNIT * 600, SCREEN_HEIGHT_UNIT * 50, 900 * SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT * 1800, LEVEL_SCENE_COMPLETE, 5);
   
   if (levelNumC >= 0)
      addButtonSprite(NEXT_SPR, "", SCREEN_WIDTH_UNIT * 1200, SCREEN_HEIGHT_UNIT * 1580, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*openNextLevel), LEVEL_SCENE_COMPLETE, 1, 6);
   else { /* Just nothing, just to meet the criteria*/ }
   renderScreen();
   addButtonSprite(MENU_ICON, "", SCREEN_WIDTH_UNIT * 800, SCREEN_HEIGHT_UNIT * 1580, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*onExit), LEVEL_SCENE_COMPLETE, 1, 6);
   addButtonSprite(REPL_SPR , "", SCREEN_WIDTH_UNIT * 1000, SCREEN_HEIGHT_UNIT * 1580, SCREEN_WIDTH_UNIT * 100, SCREEN_WIDTH_UNIT * 100, 255, 255, 255, (*restart), LEVEL_SCENE_COMPLETE, 1, 6);
   
   int movesBest = atoi(getMem(getUnformatted("level_%s_steps", levelsPaths[levelNumC])));
   int pushesBest = atoi(getMem(getUnformatted("level_%s_pushes", levelsPaths[levelNumC])));
   movesMade++;
   addLabel(SCREEN_WIDTH_UNIT * 1300, SCREEN_HEIGHT_UNIT * 1100, 255, 255, 255, LEVEL_SCENE_COMPLETE, ALLEGRO_ALIGN_RIGHT, "%i B(%i)", pushesMade, pushesBest);
   addLabel(SCREEN_WIDTH_UNIT * 1300, SCREEN_HEIGHT_UNIT * 1250, 255, 255, 255, LEVEL_SCENE_COMPLETE, ALLEGRO_ALIGN_RIGHT, "%i B(%i)", movesMade, movesBest);
   if(movesBest == 0 || movesBest > movesMade)
      putMem(getUnformatted("level_%s_steps", levelsPaths[levelNumC]), getUnformatted("%i", movesMade));
   else { /* Just nothing, just to meet the criteria*/ }
   if (pushesBest == 0 || pushesBest > pushesMade)
      putMem(getUnformatted("level_%s_pushes", levelsPaths[levelNumC]), getUnformatted("%i", pushesMade));
   else { /* Just nothing, just to meet the criteria*/ }
   changeScene(LEVEL_SCENE_COMPLETE);
   renderScreen();
   
}
int step = 0, spriteNum = 0;
void movePlayer(int up, int right)
{
   if (SCENE_NOW != LEVEL_SCENE)
      return;
   int newX = x, newY = y;
   bool assign = true;
   newX += right; newY -= up;
   if (map[newX][newY] == 1 || newX >= LEVEL_WIDTH || newY >=LEVEL_HEIGHT || newX < 0 || newY < 0)
      assign = false;
   else { /* Just nothing, just to meet the criteria*/ }
   Log_i(__func__, "\n\t%i\n%i\t\t%i\n\t%i", map[newX][newY - 1], map[newX - 1][newY], map[newX + 1][newY], map[newX][newY + 1]);
   if (map[newX][newY] == 3 || map[newX][newY] == 4)
   {
      Log_i(__func__, "Crate detected");
      if (map[newX + right][newY - up ] == 0 || map[newX + right][newY - up] == 2)
      {
         Log_i(__func__, "Changed crate place");
         changeText(pushesMadeLabelId ,"Pushes:%i", ++pushesMade);
         mapSprites[newX + right][newY - up] = mapSprites[newX][newY];
         if (map[newX + right][newY - up] == 2)
         {
            if(map[newX][newY] != 4)
               changeText(cratesLeftLabelId, "Crates left:%i", --cratesCountN);
            if (cratesCountN == 0)
               onLevelComlete();
            map[newX + right][newY - up] = 4;
         }
         else 
         {
            if(map[newX][newY] == 4)
               changeText(cratesLeftLabelId, "Crates left:%i", ++cratesCountN);
            map[newX + right][newY - up] = 3;
            
         }
         if(map[newX][newY] == 3)
            map[newX][newY] = 0;
         else
            map[newX][newY] = 2;
         
         moveSpriteTo(mapSprites[newX][newY], (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*(newX + right) + SCREEN_WIDTH_UNIT* MAP_OFFSET, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*(newY - up) + SCREEN_WIDTH_UNIT* MAP_OFFSET);
      }
      else
         assign = false;
   }
   if (assign)
   {
      x = newX; y = newY;
      movesMade++;
      if (up == 1)
         spriteNum = 6;
      if (up == -1)
         spriteNum = 4;
      if (right == 1)
         spriteNum = 2;
      if (right == -1)
         spriteNum = 0;
      changeSprite(playerSpriteId, "%s%i.png", CHAR_SPR_PL,((step++)%2+spriteNum));
      moveSpriteTo(playerSpriteId, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*x + SCREEN_WIDTH_UNIT* MAP_OFFSET, (TILE_SIZE - 2)*SCREEN_WIDTH_UNIT*y + SCREEN_WIDTH_UNIT* MAP_OFFSET);
   }
   else { /* Just nothing, just to meet the criteria*/ }
}
