#pragma once
#include "stdio.h"
#include "memory.h"
typedef unsigned char byte;

struct SArrayElement
{
	int iNum;
	struct SArrayElement *linkToPrev, *linkToNext;
	byte * container;
};
typedef struct SArrayElement ArrayElement;
int arraySize(const ArrayElement *arrayC);
byte *get(const ArrayElement *arrayC, int i);
int add(ArrayElement **arrayC, const byte * cont, const size_t size);
int addInd(const ArrayElement *arrayC, int i, const byte * cont, const size_t size);
void removeEl(ArrayElement *arrayC, int i);
void removeLast(const ArrayElement *arrayC);
void removeElOb(ArrayElement **arrayC, ArrayElement *toRemove);
void clear(ArrayElement **arrayC);
byte *getLast(const ArrayElement *arrayC);
void set(const ArrayElement *arrayC, int i, const byte * cont, const size_t size);
ArrayElement *join(ArrayElement *firstArray, ArrayElement *secArray);
void sortArray(ArrayElement **arrayC, int(*compare)(byte *, byte *));
int findInd(const ArrayElement *arrayC, const byte * cont);
void removeCont(ArrayElement **arrayC, const byte * cont);