#pragma once

#include <iostream>
#include "Background.h"

using std::cout;
using std::endl;
using std::cin;

class Test
{
public:
	Test();
	~Test();

	void backgroundImageLoadTest();

	// Ben's Test case
	int TestHEandUN();
	int TestStep();
	int TestX();
	int TestY();
	int TestHeight();
	int TestWidth();
};
