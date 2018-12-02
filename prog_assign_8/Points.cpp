#include "Points.h"

Points::Points(unsigned int width, unsigned int height) : mWidth(width), mHeight(height)
{
	// the size of Square is 10 units
	unsigned int const lengthSquare = 10;
	unsigned int m = mHeight / lengthSquare;
	unsigned int n = mWidth / lengthSquare;
	unsigned int total = m * n;

	printf("m * n %d\n", total);

	// resize the vertex array to fit the level size
	mPoints.setPrimitiveType(sf::Points);
	mPoints.resize(total + 1);
	
	// create the points position on the window 
	for (unsigned int x = 0; x < n; x++)
	{
		for (unsigned int y = 0; y < m; y++)
		{
			printf("m * x + y %d ------ %d\n", x, m * x + y);

			mPoints[m * x + y].position = sf::Vector2f(float(x * lengthSquare), float(y * lengthSquare));
		}
	}
}


