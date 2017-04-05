#include "LibraryMerger.h"

void generateSeed(char * seed, int difficul)
{
	for (int i = 0; i < difficul *8; i += 8)
	{
		if (i >= SEED_LENTGH * 8)
			break;
		seed[i] = rand() % 8 + 65;
		seed[i + 1] = rand() % 15 + 65;
		seed[i + 2] = i/10 + '0';
		seed[i + 3] = rand() %10 + '0';
		int x = rand() % LEVEL_WIDTH,  y = rand() % LEVEL_HEIGHT;
		seed[i + 4] = x / 10 + '0';
		seed[i + 5] = x % 10 + '0';
		seed[i + 6] = y / 10 + '0';
		seed[i + 7] = y % 10 + '0';
		//CB0B0000
	}
	
	Log_i(__func__, "Seed:%s", seed);
}
/*
	
	//rooms seeds
	1 A-Z //rooms sizes
		A - 3*3
		B - 3*4
		C - 4*3
		D -	5*5
		E - 3*5
		F - 5*3
		G - 5*4
		H - 4*5
	2 A-F //empty wall
		A - left
		B - right
		C - top
		D - bottom
		E - top and left
		F - top and right
		G - bottom and left
		H - bottom and right
		I - left and right
		J - top and bottom
		K - all, except left
		L - all, except right
		M - all, except top
		N - all, except bottom
	3 0-9 //count max walls
	4 0-9 //roomd id
	56 0-9 0-9 //postion x
	78 0-9 0-9 //postion y
	12345678
	01234567
	1 A-Z //rooms sizes
	2 A-F //empty wall
	3 1-9 //amount of empty
	4 A-F //crates amount in room
	5 0-9
	6 0-9 //postion x
	7 0-9 
	8 0-9 //postion y
*/

int generate(int map[LEVEL_HEIGHT][LEVEL_WIDTH] ,char * seed, int cratesCount)
{
	for (int i = 0; i < LEVEL_WIDTH; i++)
	{
		for (int q = 0; q < LEVEL_HEIGHT; q++)
			map[i][q] = 0;
	}
	int steps = 0;
	for (int i = 0; i < strlen(seed); i += 8)
	{
		int width = 0, height = 0, emptyLeft = 0, emptyTop = 0, emptyBottom = 0, emptyRight = 0;
		int crateSeedStart =-1;
		
		Log_i(__func__, "crateSeedStart=%i", crateSeedStart);
		int emptyLimit = seed[i+2],y = seed[i+4]-'0'+ seed[i + 5] - '0', x = seed[i + 6] - '0' + seed[i + 7] - '0';
		switch (seed[i+0])
		{
			case 'A':
				width = 3; height = 3;
			break;

			case 'B':
				width = 3; height = 4;
			break;

			case 'C':
				width = 4; height = 3;
				break;

			case 'D':
				width = 5; height = 5;
				break;

			case 'E':
				width = 3; height = 5;
				break;

			case 'F':
				width = 5; height = 3;
				break;

			case 'G':
				width = 5; height = 4;
				break;

			case 'H':
				width = 4; height = 5;
				break;
		}
		char wallEmpty = seed[i + 1];
		int wallsCount = seed[i + 3] - '0';
		/*
		A - left
		B - right
		C - top
		D - bottom
		E - top and left
		F - top and right
		G - bottom and left
		H - bottom and right
		I - left and right
		J - top and bottom
		*/
		for (int q = 0; q < width; q++)
		{
			if(wallEmpty != 'C' && wallEmpty != 'A' && wallEmpty != 'E' && wallEmpty != 'F' && wallEmpty != 'B' && wallEmpty != 'J' && wallEmpty != 'M' && map[y][x + q]==0 && (wallsCount--)>=0)
				map[y][x + q] = 1;
			if (wallEmpty != 'D' && wallEmpty != 'G' && wallEmpty != 'H' && wallEmpty != 'J' && wallEmpty != 'I' && wallEmpty != 'N' && map[y + height][x + q] == 0 && (wallsCount--) >= 0)
				map[y+height][x + q] = 1;
		}
		
		for (int q = 0; q <= height; q++)
		{
			if (wallEmpty != 'A' && wallEmpty != 'E' && wallEmpty != 'G' && wallEmpty != 'I' && wallEmpty != 'K' && map[y + q][x] == 0 && (wallsCount--) >= 0)
				map[y+q][x] = 1;
			if (wallEmpty != 'B' && wallEmpty != 'F' && wallEmpty != 'E' && wallEmpty != 'H' && wallEmpty != 'I' && wallEmpty != 'L' && map[y + q][x + width] == 0 && (wallsCount--) >= 0)
				map[y + q][x + width] = 1;
		}
		for (int q = 1; q < height; q++)
		{
			for (int m = 1; m < width; m++)
			{
				if(map[m][q] == 1)
					map[m][q] = 0;
			}
		}
		for (int q = 0; q < LEVEL_WIDTH; q++)
		{
			if(map[q][0] == 0)
				map[q][0] = 1;
			if(map[q][LEVEL_HEIGHT - 1] == 0)
				map[q][LEVEL_HEIGHT - 1] = 1;
		}
		for (int q = 0; q < LEVEL_HEIGHT; q++)
		{
			if(map[0][q] == 0)
				map[0][q] = 1;
			if(map[LEVEL_WIDTH - 1][q] == 0)
				map[LEVEL_WIDTH - 1][q] = 1;
		}
		if (wallEmpty >= 'A' && (--cratesCount) > 0)
		{
			
			int crateX = x + width / 2, crateY = y + height / 2;
			map[crateY][crateX] = 2;
			map[LEVEL_HEIGHT - crateY - 1][LEVEL_WIDTH - crateX - 1] = 3;
		}
	}
}
int wallCountAround(int x, int y)
{
	int count = 0;
	if (x > 0 && map[y][x - 1] == 1)
		count++;
	if (y > 0 && map[y-1][x] == 1)
		count++;
	if (x < (LEVEL_WIDTH-1) && map[y][x + 1] == 1)
		count++;
	if (x < (LEVEL_HEIGHT-1) && map[y + 1][x] == 1)
		count++;
	return count;
}