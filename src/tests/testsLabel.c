#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
#include <time.h>

TEST_GROUP(TestLabel);

TEST_GROUP_RUNNER(TestLabel)
{
    RUN_TEST_CASE(TestLabel, changeText);
}

TEST_SETUP(TestLabel)
{
}

TEST_TEAR_DOWN(TestLabel)
{
}
TEST(TestLabel, changeText)
{
	TEST_ASSERT_EQUAL_INT(0, addLabel(0,0, 255,0,0, 0,1,"Default text") );
	char checkStr [256];
	sprintf(checkStr, "Crates left:%i", 50);
	changeText(0, "Crates left:%i", 50);
	Label *curLabel = getStructLabel(0);
	TEST_ASSERT(curLabel != NULL);
	TEST_ASSERT(strcmp(checkStr,curLabel->text) == 0);
}
