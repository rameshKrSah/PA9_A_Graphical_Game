#include "Test.h"

Test::Test()
{
}

Test::~Test()
{
}

void Test::backgroundImageLoadTest()
{
	Background test;

	if (test.loadBackground("blue_sky.jpg"))
	{
		std::cout << "PASSED : background image load test" << std::endl;
	}
	else
	{
		std::cout << "FAILED : background image load test" << std::endl;
	}
}

void Test::terrainGenrationTest()
{

}
