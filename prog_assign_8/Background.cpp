#include "Background.h"


Background::Background()
{}


bool Background::loadBackground(const std::string & fileName)
{
	bool success = false;

	// load the blue sky texture 
	if (mTexture.loadFromFile("blue_sky.jpg"))
	{
		// create the sprite fromt the blue sky texture 
		mSprite.setTexture(mTexture);
		mSprite.setOrigin(0.0f, 0.0f);
		
		success = true;
	}

	return success;
}

Background::~Background()
{
}
