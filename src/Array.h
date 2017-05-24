#pragma once
#include "stdio.h"
#include "memory.h"
typedef unsigned char byte;//!< Dinamic type of data to store different standart types without loosing data
/*!
@file Array.h
\defgroup Array Array
@{

@author arseniy899
\brief Array\n
This is 'class' for working with dynamic arrays (lists)
*/
/**
	List element
*/
struct SArrayElement
{
	int iNum;//!< Elemt's number in list (for debug proposes)
	struct SArrayElement *linkToPrev/*!< Link to previous element in list*/, *linkToNext;//!< Link to next element in list
	byte * container;//!< Container for storing data
};
typedef struct SArrayElement ArrayElement;
/**
	Get size of array by it's link
	@param arrayC link to array (first element)
	@return array's size
*/
int arraySize(ArrayElement *arrayC);
/**
	Get object at i position
	@param arrayC link to array (first element)
	@param i index
	@return pointer to requested object or null if not found
*/
byte *get(ArrayElement *arrayC, int i);
/**
	Add new object to array to the end
	@param arrayC link to array (first element)
	@param cont your object to put
	@param size size of your object in bytes (e.g sizeof() )
	@return index where object was putted
*/
int add(ArrayElement **arrayC, byte * cont, size_t size);
/**
	Add new object to array at specific position
	@param arrayC link to array (first element)
	@param i index to put on object
	@param cont your object to put
	@param size size of your object in bytes (e.g sizeof() )
	@return index where object was putted
*/
int addInd(ArrayElement *arrayC, int i, byte * cont, size_t size);
/**
	Remove object at postion
	@param arrayC link to array (first element)
	@param i index to put on object
*/
void removeEl(ArrayElement *arrayC, int i);
/**
	Remove last object in list
	@param arrayC link to array (first element)
*/
void removeLast(ArrayElement *arrayC);
/**
	Remove object by link to this object. To use it publicly, call removeCont
	@see removeCont()
	@param arrayC link to array (first element)
	@param toRemove link to object as ArrayElement
*/
void removeElOb(ArrayElement **arrayC, ArrayElement *toRemove);
/**
	Remove object by link to this object
	@param arrayC link to array (first element)
	@param cont object to remove from array
*/
void removeCont(ArrayElement **arrayC, byte * cont);
/**
	Clear specified array
	@param arrayC link to array (first element)
*/
void clear(ArrayElement **arrayC);
/**
	Assign new object into array at specific position
	@param arrayC link to array (first element)
	@param i index of the object
	@param cont your object to put
	@param size size of your object in bytes (e.g sizeof() )
*/
void set(ArrayElement *arrayC, int i, byte * cont, size_t size);
/**
	Joining two arrays into one.
	@param *firstArray link first to array (first element)
	@param *secArray link second to array (first element)
	@return new array from both above
*/
ArrayElement *join(ArrayElement *firstArray, ArrayElement *secArray);
/**
	Sorting array by your specified rule
	@param arrayC link to array (first element)
	@param compare link to function with your rule of sorting
	Example Usage:
	@code
		...
		int sortRule(byte * a1, byte *a2)
		{
			return -(((int)*a1) - ((int)*a2));
		}
		...
		sortArray(&arrayToSort, &sortRule);
	@endcode
		
*/
void sortArray(ArrayElement **arrayC, int(*compare)(byte *, byte *));
/**
	Get index of object by link to it
	@param arrayC link first to array (first element)
	@param cont your object for
	@return index of object
*/
int findInd(ArrayElement *arrayC, byte * cont);
/**
	Get last object in the array
	@param arrayC link first to array (first element)
	@return object requested or NULL if array is empty
*/
byte *getLast(ArrayElement *arrayC);
/**
@}
*/
