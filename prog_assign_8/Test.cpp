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

int Test::TestHEandUN()
{
	int  x = 0;
	cout << "Health Value" << endl;
	while (x < 1 || x > 3)
	{
		cin >> x;
		//Thanks StackOverFlow
		if (!cin) // or if(cin.fail())
		{
			// user didn't input a number
			// reset failbit
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//skip bad input
		}
	}
	return x;
}
int Test::TestStep()
{
	cout << "Loop Value" << endl;
	int  x = 0;
	while (x < 1 || x > 10)
	{
		cin >> x;
		//Thanks StackOverFlow
		if (!cin) // or if(cin.fail())
		{
			// user didn't input a number
			// reset failbit
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//skip bad input
		}
	}
	return x;
}
int Test::TestX()
{
	cout << "X Value" << endl;
	int  x = 0;
	while (x < 1 || x > 1000)
	{
		cin >> x;
		//Thanks StackOverFlow
		if (!cin) // or if(cin.fail())
		{
			// user didn't input a number
			// reset failbit
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//skip bad input
		}
	}
	return x;
}
int Test::TestY()
{
	cout << "Y Value" << endl;
	int  x = 0;
	while (x < 1 || x > 1000)
	{
		cin >> x;
		//Thanks StackOverFlow
		if (!cin) // or if(cin.fail())
		{
			// user didn't input a number
			// reset failbit
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//skip bad input
		}
	}
	return x;
}
int Test::TestHeight()
{
	cout << "Height Value" << endl;
	int  x = 0;
	while (x < 1 || x > 200)
	{
		cin >> x;
		//Thanks StackOverFlow
		if (!cin) // or if(cin.fail())
		{
			// user didn't input a number
			// reset failbit
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//skip bad input
		}
	}
	return x;
}
int Test::TestWidth()
{
	cout << "Width Value" << endl;
	int  x = 0;
	while (x < 1 || x > 150)
	{
		cin >> x;
		//Thanks StackOverFlow
		if (!cin) // or if(cin.fail())
		{
			// user didn't input a number
			// reset failbit
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//skip bad input
		}
	}
	return x;
}
