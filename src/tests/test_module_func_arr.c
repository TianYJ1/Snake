#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
#include <time.h>

TEST_GROUP(TestArray);

TEST_GROUP_RUNNER(TestArray)
{
    RUN_TEST_CASE(TestArray, addToArray);
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

