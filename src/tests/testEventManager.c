#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
#include <time.h>

TEST_GROUP(TestEventManager);

TEST_GROUP_RUNNER(TestEventManager)
{
    RUN_TEST_CASE(TestEventManager, onMouseRightClickTest);
    RUN_TEST_CASE(TestEventManager, onKeyDownTest);

}

TEST_SETUP(TestEventManager)
{
}

TEST_TEAR_DOWN(TestEventManager)
{
}

TEST(TestEventManager, onMouseRightClickTest)
{
	TEST_ASSERT_EQUAL_INT(0, onKeyUp(0));
}
TEST(TestEventManager, onKeyDownTest)
{
	TEST_ASSERT_EQUAL_INT(0, onKeyDown(0));
}

