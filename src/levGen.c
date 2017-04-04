#include "LibraryMerger.h"

void generateSeed(char * seed, char * cratesSeed, int difficul, int crates)
{
	for (int i = 0; i < difficul *8; i += 8)
	{
		if (i >= SEED_LENTGH * 8)
			break;
		seed[i] = rand() % 8 + 65;
		seed[i + 1] = rand() % 15 + 65;
		seed[i + 2] = i/10 + '0';
		seed[i + 3] = i%10 + '0';
		int x = rand() % LEVEL_WIDTH,  y = rand() % LEVEL_HEIGHT;
		seed[i + 4] = x / 10 + '0';
		seed[i + 5] = x % 10 + '0';
		seed[i + 6] = y / 10 + '0';
		seed[i + 7] = y % 10 + '0';
		//CB0B0000
	}
	for (int i = 0; i < crates * 8; i += 8)
	{
		if (i >= SEED_LENTGH * 8)
			break;
		int randI = rand() % difficul;
		if(randI / 10 > 0)
			cratesSeed[i] = randI/10 + '0';
		else
			cratesSeed[i] = 'Y';
		cratesSeed[i + 1] = randI % 10 + '0';
		cratesSeed[i + 2] = rand() % 9 + 65;
		cratesSeed[i + 3] = rand() % 9 + 65;
		cratesSeed[i + 4] = rand() % 9 + 65;
		cratesSeed[i + 5] = rand() % 9 + 65;
		cratesSeed[i + 6] = rand() % 9 + 65;
		cratesSeed[i + 7] = rand() % 9 + 65;

		//CB0B0000
	}
	Log_i(__func__, "Seed:%s,cratesSeed:%s", seed, cratesSeed);
}
/*
	//crates seeds
	0-9 -
	0-9 - room id
	A-I
	1	A - no
	2	B - 1 top
	3	C - 2 top
	4	D - 1 right
	5	E - 2 right
	6	F - 1 left
	7	G - 2 left
	8	H - 1 bottom
	9	I - 2 bottom
	10
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
	3 0-9 //room id
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

int generate(int map[LEVEL_HEIGHT][LEVEL_WIDTH] ,char * seed, char * cratesSeed)
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
		char * crateSeed;
		if((i / 8)<10)
			crateSeed = strstr(cratesSeed, "Y%i",1);
		else
			crateSeed = strstr(cratesSeed, "%i", i / 8);
		Log_i(__func__, "crateSeed=%s, %i%i", crateSeed, ((i / 8) / 10), ((i / 8) % 10));
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
			if(wallEmpty != 'C' && wallEmpty != 'E' && wallEmpty != 'F' && wallEmpty != 'J' && wallEmpty != 'M' && map[y][x + q]==0)
				map[y][x + q] = 1;
			if (wallEmpty != 'D' && wallEmpty != 'G' && wallEmpty != 'H' && wallEmpty != 'J' && wallEmpty != 'N' && map[y + height][x + q] == 0)
				map[y+height][x + q] = 1;
		}
		
		for (int q = 0; q <= height; q++)
		{
			if (wallEmpty != 'A' && wallEmpty != 'E' && wallEmpty != 'G' && wallEmpty != 'I' && wallEmpty != 'K' && map[y + q][x] == 0)
				map[y+q][x] = 1;
			if (wallEmpty != 'B' && wallEmpty != 'F' && wallEmpty != 'H' && wallEmpty != 'I' && wallEmpty != 'L' && map[y + q][x + width] == 0)
				map[y + q][x + width] = 1;
		}
		for (int q = 1; q < height; q++)
		{
			for (int m = 1; m < width; m++)
				map[m][q] = 0;
		}
		for (int i = 0; i < LEVEL_WIDTH; i++)
		{
			map[i][0] = 1;
			map[i][LEVEL_HEIGHT - 1] = 1;
		}
		for (int q = 0; q < LEVEL_HEIGHT; q++)
		{
			map[0][q] = 1;
			map[LEVEL_WIDTH - 1][q] = 1;
		}
		
		if (crateSeed)
		{
			int crateX = x + width / 2, crateY = y + height / 2;
			map[crateY][crateX] = 2;
			map[crateY][crateX] = 3;
			for (int q = 2; q < SEED_LENTGH; q++)
			{
				switch (crateSeed[q])
				{
				case 'D':
					if (map[crateY][crateX + 1] == 0)
						crateX++;
					break;
				case 'E':
					if (map[crateY][crateX + 2] == 0)
						crateX += 2;
					break;
				case 'F':
					if (map[crateY][crateX - 1] == 0)
						crateX--;
					break;
				case 'G':
					if (map[crateY][crateX - 2] == 0)
						crateX -= 2;
					break;
				case 'B':
					if (map[crateY - 1][crateX] == 0)
						crateY -= 1;
					break;
				case 'C':
					if (map[crateY - 2][crateX] == 0)
						crateY -= 2;
					break;
				case 'H':
					if (map[crateY + 1][crateX] == 0)
						crateY += 1;
					break;
				case 'I':
					if (map[crateY + 2][crateX] == 0)
						crateY += 2;
					break;
				}
				if (crateSeed[q] != 'A')
					steps++;
				
			}
			
		}
	}
	
}