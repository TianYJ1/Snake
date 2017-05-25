#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
#include <time.h>

TEST_GROUP(TestLabel);
char checkStr [256];
TEST_GROUP_RUNNER(TestLabel)
{
    RUN_TEST_CASE(TestLabel, addText);
    RUN_TEST_CASE(TestLabel, changeText);
    RUN_TEST_CASE(TestLabel, checkAfterText);
}

TEST_SETUP(TestLabel)
{
}

TEST_TEAR_DOWN(TestLabel)
{
}
TEST(TestLabel, addText)
{
	clear(&labelsArr);
	TEST_ASSERT_EQUAL_INT(0, addLabel(0,0, 255,0,0, 0,1,"Default text") );
	
}
TEST(TestLabel, changeText)
{
	sprintf(checkStr, "Crates left:%i", 50);
	TEST_ASSERT(changeText(0, "Crates left:%i", 50) >= 0);
}
TEST(TestLabel, checkAfterText)
{
	Label *curLabel = getStructLabel(0);
	TEST_ASSERT(curLabel != NULL);
	TEST_ASSERT(strcmp(checkStr,curLabel->text) == 0);
}
