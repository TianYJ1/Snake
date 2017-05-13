#include <stdlib.h>
#include "Array.h"
ArrayElement *getLastEl(const ArrayElement *arrayC);
int arraySize(const ArrayElement *arrayC)
{
	 if (!arrayC)
		 return 0;
	int ret = 0;
	for (const ArrayElement *cur = arrayC; cur; cur = cur->linkToNext, ++ret);
	return ret;
}
byte *get(ArrayElement *arrayC, int i)
{
	if (i > arraySize(arrayC))
		return NULL;
	ArrayElement *cur = arrayC;
	while (cur && cur->linkToNext && (i--) > 0)
		cur = cur->linkToNext;
	if(cur)
		return cur->container;
	else
		return NULL;
}
ArrayElement *getEl(ArrayElement *arrayC, int i)
{
	if (i > arraySize(arrayC))
		return NULL;
	ArrayElement *cur = arrayC;
	while (cur->linkToNext && (i--) > 0)
		cur = cur->linkToNext;
	return cur;
}

int add(ArrayElement **arrayC, const byte * cont, const size_t size)
{
	ArrayElement *newEl = malloc(sizeof(ArrayElement));
	newEl->container = (byte*)malloc(size);
	memcpy(newEl->container, cont, size);
	newEl->iNum = arraySize(*arrayC);
	if (*arrayC == NULL)
	{
		*arrayC = newEl;
		(*arrayC)->linkToNext = NULL;
		(*arrayC)->linkToPrev = NULL;
	}
	else
	{
		newEl->linkToPrev = getLastEl(*arrayC);
		newEl->linkToNext = NULL;
		newEl->linkToPrev->linkToNext = newEl;
	}
	return arraySize(*arrayC) - 1;
}
int addInd(const ArrayElement *arrayC, int i,const byte * cont, const size_t size)
{
	if (i < 0 || i > arraySize(arrayC))
		return 0;
	if (i == 0)
		add(arrayC, cont, size);
	else
	{
		ArrayElement *prev = getEl(arrayC, i), *next = prev->linkToNext;
		ArrayElement *newEl = malloc(sizeof(ArrayElement));
		newEl->container = malloc(size);
		memcpy(newEl->container, cont, size);
		newEl->linkToPrev = prev;
		newEl->linkToNext = next;
		prev->linkToNext = newEl;
		next->linkToPrev = newEl;
	}
	return i;
}
void set(const ArrayElement *arrayC, int i, const byte * cont, const size_t size)
{
	if (i < 0 || i > arraySize(arrayC))
		return;
	ArrayElement *toSet = getEl(arrayC, i);
	toSet->container = cont;
}
void removeEl(ArrayElement *arrayC, int i)
{
	if (i < 0 || i >= arraySize(arrayC)) return;
	ArrayElement *toRemove = getEl(arrayC, i);
	removeElOb(arrayC, &toRemove);
	
}
void removeElOb(ArrayElement **arrayC, ArrayElement *toRemove)
{
	ArrayElement *prev = toRemove->linkToPrev;
	ArrayElement *next = toRemove->linkToNext;
	if (!prev)
	{
		if (next)
		{
			free((*arrayC)->container);
			free(*arrayC);
			next->linkToPrev = NULL;
			(*arrayC) = next;
			
		}
		else
		{
			free((*arrayC)->container);
			free((*arrayC));
			*arrayC = NULL;
		}

	}
	else if (!next)
	{
		prev->linkToNext = NULL;
		free(toRemove->container);
		free(toRemove);
	}
	else
	{
		if (prev != NULL)
			prev->linkToNext = next;
		next->linkToPrev = prev;
		free(toRemove->container);
		free(toRemove);
	}

}
int findInd(const ArrayElement *arrayC, const byte * cont)
{
	if (arrayC == NULL)
		return -1;
	ArrayElement *cur = arrayC;
	int ind = -1;
	while (cur->linkToNext)
	{
		cur = cur->linkToNext;
		ind++;
		if (cur->container == cont)
			break;
	}
	return ind;
}
void removeCont(ArrayElement **arrayC, const byte * cont)
{
	int ind = findInd(*arrayC, cont);
	if (ind >= 0)
		removeEl(*arrayC, ind);
}
void removeLast(const ArrayElement *arrayC)
{
	ArrayElement *toRemove = getLastEl(arrayC), *prev = toRemove->linkToPrev;
	if (toRemove != NULL)
	{
		prev->linkToNext = NULL;
		free(toRemove->container);
		free(toRemove);
	}
	
}
void clear(ArrayElement **arrayC)
{
	ArrayElement *cur = getLastEl(*arrayC);
	while (cur)
	{
		cur = getLastEl(*arrayC);
		if (cur)
		{
			free(cur->container);
			free(cur);
		}
		cur = NULL;
	}
	free(*arrayC);
	*arrayC = NULL;
}
ArrayElement *getLastEl(const ArrayElement *arrayC)
{
	if (arrayC == NULL)
		return NULL;
	ArrayElement *cur = arrayC;
	while (cur->linkToNext)
		cur = cur->linkToNext;
	return cur;
}
byte *getLast(const ArrayElement *arrayC)
{
	if (arrayC == NULL)
		return NULL;
	ArrayElement *cur = arrayC;
	while (cur->linkToNext)
		cur = cur->linkToNext;
	return cur->container;
}
ArrayElement *join(ArrayElement *firstArray, ArrayElement *secArray)
{
	ArrayElement *firstArrayLast = getLastEl(firstArray);
	firstArrayLast->linkToNext = secArray;
	secArray->linkToPrev = firstArrayLast;
	return firstArray;
}
void sortArray(ArrayElement **arrayC, int(*compare)(byte *, byte *))
{
	for (int i = 0; i < arraySize(*arrayC); i++)
	{
		for (int q = 0; q < arraySize(*arrayC) - 1; q++)
		{
			ArrayElement *a1 = getEl(*arrayC, i), *a2 = getEl(*arrayC, q);
			if (compare(a1->container, a2->container) < 0)
			{
				byte *newT = a1->container;
				a1->container = a2->container;
				a2->container = newT;
			}
		}
	}
}
