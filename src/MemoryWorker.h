#pragma once
struct MemEntryS
{
	char * data;
	char * key;
};
typedef struct MemEntryS MemEntry;
char *getUnformatted(char *key, ...);
char* getMem(char *key);
void putMem(char *key, char *data);
void loadMem();
void saveMem();