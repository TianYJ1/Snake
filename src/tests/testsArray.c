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
