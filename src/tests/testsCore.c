#include "unity.h"
#include "unity_fixture.h"
#include "LibraryMerger.h"
#include <time.h>

TEST_GROUP(TestCore);

TEST_GROUP_RUNNER(TestCore)
{
	initAddons();
	initVars();
	RUN_TEST_CASE(TestCore, loadResourcesPath);
}

TEST_SETUP(TestCore)
{

}

TEST_TEAR_DOWN(TestCore)
{
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


