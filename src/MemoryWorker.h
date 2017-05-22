#pragma once
/*!
@file MemoryWorker.h
\defgroup MemoryWorker MemoryWorker
@{

@author arseniy899
\brief MemoryWorker\n
This is for managing constant memory between running game (storing highscores and etc.)
*/
/*!<
	Structure for storing data in assotiative array
*/
struct MemEntryS
{
	char * data;//!< Data to store
	char * key;//!< Key to find data by
};
typedef struct MemEntryS MemEntry;
/**
	Return string from formatted input
	@param key input
	@return string unformatted
*/
char *getUnformatted(char *key, ...);
/**
	Return string from memory by it's key
	@param key key
	@return string
*/
char* getMem(char *key);
/**
	Put string to memory by it's key
	@param key key to store with
	@param data data to store
*/
void putMem(char *key, char *data);
/**
	Load data from file
*/
void loadMem();
/**
	Write to file all data
*/
void saveMem();
/**
@}
*/