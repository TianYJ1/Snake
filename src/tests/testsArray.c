#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
#include <time.h>

TEST_GROUP(TestArray);

TEST_GROUP_RUNNER(TestArray)
{
    RUN_TEST_CASE(TestArray, addToArray);
    RUN_TEST_CASE(TestArray, clearArray);
    RUN_TEST_CASE(TestArray, removeLastAddAtArray);
    RUN_TEST_CASE(TestArray, moveSprite);
    RUN_TEST_CASE(TestArray, clearSpritesLayer);

}

TEST_SETUP(TestArray)
{
}

TEST_TEAR_DOWN(TestArray)
{
}


TEST(TestArray, addToArray)
{
	ArrayElement * array = NULL;
    	srand(time(NULL));
	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		num = rand() % 50;
		add(&array, (byte *)&num, sizeof(num));
	}
	TEST_ASSERT_EQUAL_INT(10, arraySize(array));
}

TEST(TestArray, clearArray)
{
	ArrayElement * array = NULL;
    	srand(time(NULL));
	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		num = rand() % 50;
		add(&array, (byte *)&num, sizeof(num));
	}
	clear(&array);
	TEST_ASSERT_EQUAL_INT(NULL, array);
}

TEST(TestArray, removeLastAddAtArray)
{
	ArrayElement * array = NULL;
    	srand(time(NULL));
	int num = 0;
	for (int i = 0; i < 10; i++)
	{
		num = rand() % 50;
		add(&array, (byte *)&num, sizeof(num));
	}
	addInd(array, 1, (byte *)&num, sizeof(char));
	TEST_ASSERT_EQUAL_INT(num, (int)*get(array,2));
	removeLast(array);
	TEST_ASSERT_EQUAL_INT(10, arraySize(array));
}

TEST(TestArray, moveSprite)
{
	clear(&spritesArr);
	nextSpriteId = 0;
	TEST_ASSERT_EQUAL_INT(0, addSprite("back.jpg",0, 0, 0, 0, 0, rand() % SPRITES_LAYERS_AMOUNT) );
	//getting sprite at 0. Check if it equals to our created
	Sprite *curSprite = getStruct(0);
	TEST_ASSERT(curSprite);
	TEST_ASSERT(0 == curSprite->id);
	moveSpriteTo(0, 20,30);	
	curSprite = getStruct(0);
	TEST_ASSERT(0 == curSprite->id);
	//checking it's coordinates
	TEST_ASSERT_EQUAL_INT(curSprite->posX,20);
	TEST_ASSERT_EQUAL_INT(curSprite->posY,30);
	
}
TEST(TestArray, clearSpritesLayer)
{
	int layerToClear = rand() % SPRITES_LAYERS_AMOUNT, spritesToClearCount = 0; 
	for(int i = 0;i<50;i++)
	{
		int r = rand() % SPRITES_LAYERS_AMOUNT;
		if(r == layerToClear)
			spritesToClearCount++;
		TEST_ASSERT_EQUAL_INT(i+1, addSprite("back.jpg",0, 0, 0, 0, 0, r));
	}
	clearSpritesLayer(layerToClear);
	for (int i = 0; i < arraySize(spritesArr); i++)
	{
		Sprite *curSprite = getStruct(i);
		TEST_ASSERT(layerToClear != curSprite->layer);
	}
	TEST_ASSERT(arraySize(spritesArr) <= (50-spritesToClearCount+1));
}

