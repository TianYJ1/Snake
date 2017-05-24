#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
char * pathCur;
char names [DEFAULT_LENGTH][DEFAULT_LENGTH] = {0};
char levelsPaths[DEFAULT_LENGTH][DEFAULT_LENGTH] = { 0 };
char levelsNames[DEFAULT_LENGTH][BUTTONS_NAME_SIZE];
extern float SCREEN_WIDTH_UNIT, SCREEN_HEIGHT_UNIT;
int levelSelectPage = 0, yOffset = 0;

static void RunAllTests(void)
{
	RUN_TEST_GROUP(TestCore);
	RUN_TEST_GROUP(TestArray);
	RUN_TEST_GROUP(TestEventManager);
	RUN_TEST_GROUP(TestLabel);

}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
