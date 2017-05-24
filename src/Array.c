#include <stdlib.h>
#include "Array.h"
ArrayElement *getLastEl(ArrayElement *arrayC);
int arraySize(ArrayElement *arrayC)
{
	if (!arrayC)
		return 0;
	else { /* Just nothing, just to meet the criteria*/ }
	int ret = 0;
	for (const ArrayElement *cur = arrayC; cur; cur = cur->linkToNext, ++ret);
	return ret;
}
byte *get(ArrayElement *arrayC, int i)
{
	if (i > arraySize(arrayC))
		return NULL;
	else { /* Just nothing, just to meet the criteria*/ }
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
	else { /* Just nothing, just to meet the criteria*/ }
	ArrayElement *cur = arrayC;
	while (cur->linkToNext && (i--) > 0)
		cur = cur->linkToNext;
	return cur;
}

int add(ArrayElement **arrayC, byte * cont, size_t size)
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
int addInd(ArrayElement *arrayC, int i, byte * cont, size_t size)
{
	if (i < 0 || i > arraySize(arrayC))
		return 0;
	else { /* Just nothing, just to meet the criteria*/ }
	if (i == 0)
		add(&arrayC, cont, size);
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
void set(ArrayElement *arrayC, int i, byte * cont, size_t size)
{
	if (i < 0 || i > arraySize(arrayC))
		return;
	ArrayElement *toSet = getEl(arrayC, i);
	toSet->container = cont;
}
void removeEl(ArrayElement *arrayC, int i)
{
	if (i < 0 || i >= arraySize(arrayC)) return;
	else { /* Just nothing, just to meet the criteria*/ }
	ArrayElement *toRemove = getEl(arrayC, i);
	removeElOb(&arrayC, toRemove);
	
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
int findInd(ArrayElement *arrayC, byte * cont)
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
void removeCont(ArrayElement **arrayC, byte * cont)
{
	int ind = findInd(*arrayC, cont);
	if (ind >= 0)
		removeEl(*arrayC, ind);
}
void removeLast(ArrayElement *arrayC)
{
	ArrayElement *toRemove = getLastEl(arrayC), *prev = toRemove->linkToPrev;
	if (toRemove != NULL)
	{
		prev->linkToNext = NULL;
		free(toRemove->container);
		free(toRemove);
	}
	else { /* Just nothing, just to meet the criteria*/ }
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
		else { /* Just nothing, just to meet the criteria*/ }
		cur = NULL;
	}
	free(*arrayC);
	*arrayC = NULL;
}
ArrayElement *getLastEl(ArrayElement *arrayC)
{
	if (arrayC == NULL)
		return NULL;
	else { /* Just nothing, just to meet the criteria*/ }
	ArrayElement *cur = arrayC;
	while (cur->linkToNext)
		cur = cur->linkToNext;
	return cur;
}
byte *getLast(ArrayElement *arrayC)
{
	if (arrayC == NULL)
		return NULL;
	else { /* Just nothing, just to meet the criteria*/ }
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
			else { /* Just nothing, just to meet the criteria*/ }
		}
	}
}
