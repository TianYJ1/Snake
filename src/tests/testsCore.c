#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
#include <time.h>

TEST_GROUP(TestCore);

TEST_GROUP_RUNNER(TestCore)
{
	RUN_TEST_CASE(TestCore, initAddonsAllegro);
	RUN_TEST_CASE(TestCore, initvars);	
	RUN_TEST_CASE(TestCore, loadResourcesPath);
	RUN_TEST_CASE(TestCore, showDirectoryListing);
	RUN_TEST_CASE(TestCore, openLevel);
}

TEST_SETUP(TestCore)
{

}

TEST_TEAR_DOWN(TestCore)
{
}

TEST(TestCore, initAddonsAllegro)
{
	TEST_ASSERT_MESSAGE(initAddons()>=0, "Error initing addons");
}
TEST(TestCore, showDirectoryListing)
{
	TEST_ASSERT_MESSAGE(showDirectoryListing(0)>=0, "Error showing directory");
}
TEST(TestCore, openLevel)
{
	TEST_ASSERT_MESSAGE(openLevel(0)>=0, "Error opening level");
}
TEST(TestCore, initvars)
{
	TEST_ASSERT_MESSAGE(initVars()>=0, "Error initing vars");
}
TEST(TestCore, loadResourcesPath)
{
	path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	TEST_ASSERT_MESSAGE(path, "No resources path got");
	al_append_path_component(path, "res");
	if ((!al_change_directory (al_path_cstr(path, '/') )))
	{
		path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
		al_append_path_component(path, "../res");
		if ((!al_change_directory(al_path_cstr(path, '/')) ))
		{
			//const char * p = al_path_cstr(path, '/');
			//Log_e(__func__, "Res path not found: %s", p);
			path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
			al_append_path_component(path, "../../res");
		    	if ((!al_change_directory(al_path_cstr(path, '/') )))
			{
				TEST_ASSERT_MESSAGE(false, "No resources detected");	
			}
			else { /* Just nothing, just to meet the criteria*/ }	
		}
	}
}


