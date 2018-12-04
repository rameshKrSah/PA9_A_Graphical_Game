#include "Terrain.h"
#include <iostream>

Terrain::Terrain(void)
{
	mHeight = 0;
	mWidth = 0;
	mOctaves = 0;
	mFrequency = 0.0f;
	mPersistance = 0.0f;
}

Terrain::Terrain(unsigned int width, unsigned int height, unsigned int octaves, float frequency, float persistance)
{
	mWindowSize = { width, height };
	mHeight = height;// +300;
	mWidth = width;// +200;
	mOctaves = octaves;
	mFrequency = frequency;
	mPersistance = persistance;
	mPitchAngle = 64.0f;
	mRollAngle = -4.0f;
	mYawAngle = 18.0f;

	// create the texture to store the noise value //
	mNoiseTexture.create(mWidth, mHeight);

	// create the pixels to store the colors
	mPixels = (new sf::Uint8[mWidth * mHeight * 4]);

	//std::cout << mHeight << " " << mWidth << " " << mFrequency << " " << mOctaves << " " << mPersistance << std::endl;
}

Terrain::~Terrain()
{
	// deallocate the pixels 
	delete mPixels;
}

void Terrain::generateNoise(void)
{
	SimplexNoise noiseGenerator;
	noiseGenerator.setOctaves(mOctaves);
	noiseGenerator.setFrequency(mFrequency);
	noiseGenerator.setPersistence(mPersistance);

	for (std::size_t y = 0; y < mHeight; ++y)
	{
		for (std::size_t x = 0; x < mWidth; ++x)
		{
			float xPos = float(x) / float(mWidth) - 0.5f;
			float yPos = float(y) / float(mHeight) - 0.5f;

			//noiseGenerator.randomizeSeed();
			
			float elevation = noiseGenerator.unsignedOctave(xPos, yPos);
			elevation = pow(elevation, 1.5f); //redistribution
			setPixel(x, y, elevation);
		}
	}

	// update the texture 
	mNoiseTexture.update(mPixels);

	// set the sprite 
	setSprite();
}

sf::Color Terrain::getColor(const float value)
{
	return getBiome(value);
}

void Terrain::setPixel(const unsigned int x, const unsigned int y, const float value)
{
	sf::Color color = getColor(value);
	mPixels[4 * (y * mWidth + x)] = color.r;
	mPixels[4 * (y * mWidth + x) + 1] = color.g;
	mPixels[4 * (y * mWidth + x) + 2] = color.b;
	mPixels[4 * (y * mWidth + x) + 3] = color.a;
}

sf::Color Terrain::getBiome(const float value)
{
	//if (value < 0.15f)      return sf::Color(0, 0, 102); // deep water

	if (value < 0.25f) return sf::Color(0, 51, 102); // water

	//else if (value < 0.25f) return sf::Color(0, 102, 102); // shallow water

	//else if (value < 0.27f) return sf::Color(255, 255, 204); // beach
	//else if (value < 0.35f) return sf::Color(102, 204, 0); // plains
	//else if (value < 0.4f)  return sf::Color(76, 153, 0); // jungle

	else if (value < 0.6f)  return sf::Color(51, 102, 0); // forest

	//else if (value < 0.6f)  return sf::Color(204, 204, 0); // savannah

	else if (value < 0.7f)  return sf::Color(128, 128, 128); // low hills

	else if (value < 0.8f)  return sf::Color(96, 96, 96); // hills

	else if (value < 0.9f)  return sf::Color(48, 48, 48); // high hills

	else                     return sf::Color::White;           // snow
}

void Terrain::setSprite()
{
	// set the texture to the sprite
	mSprite_3d.setTexture(mNoiseTexture);

	// set the origin and position of the sprite

	std::cout << mSprite_3d.getLocalBounds().width / 2.0f << " " << mSprite_3d.getLocalBounds().height / 2.0f << std::endl;
	std::cout << (mWindowSize / 2u).x << " " << (mWindowSize / 2u).y << std::endl;
	
	// set the origin and position of the sprite 
	mSprite_3d.setOrigin(sf::Vector2f(mSprite_3d.getLocalBounds().width, mSprite_3d.getLocalBounds().height) / 2.f);

	mSprite_3d.setPosition(sf::Vector2f(mWindowSize.x / 2.0f , mWindowSize.y / 2.0f + 100));
	
	// set the angle of rotation along the X-axis
	mSprite_3d.setPitch(60.0f);

	// set the angle of rotation along the Y axis
	//mSprite_3d.setYaw(mYawAngle);

	// set the angle of rotation along the Z axis
	//mSprite_3d.setRoll(mRollAngle);
}

void Terrain::incPitch()
{
	mSprite_3d.setPitch(mSprite_3d.getPitch() + 2.0f);
	//mSprite_3d.setPosition(mSprite_3d.getPosition().x + 2.0f, mSprite_3d.getPosition().y + 2.0f);
	std::cout << "Pitch angle " << mSprite_3d.getPitch() << std::endl;
	std::cout << "Position" << mSprite_3d.getPosition().x << " " << mSprite_3d.getPosition().y << std::endl;
}

void Terrain::decPitch()
{
	mSprite_3d.setPitch(mSprite_3d.getPitch() - 2.0f);
	//mSprite_3d.setPosition(mSprite_3d.getPosition().x - 2.0f, mSprite_3d.getPosition().y - 2.0f);
	std::cout << "Position" << mSprite_3d.getPosition().x << " " << mSprite_3d.getPosition().y << std::endl;
	std::cout << "Pitch angle " << mSprite_3d.getPitch() << std::endl;
}


void Terrain::incRoll()
{
	//mSprite_3d.setRoll(mSprite_3d.getRoll() + 2.0f);
	//std::cout << "Roll angle " << mSprite_3d.getRoll() << std::endl;
	mSprite_3d.setOrigin(mSprite_3d.getOrigin().x + 2.0f, mSprite_3d.getOrigin().y + 2.0f);
	std::cout << "Origin" << mSprite_3d.getOrigin().x << " " << mSprite_3d.getOrigin().y << std::endl;
}

void Terrain::decRoll()
{
//	mSprite_3d.setRoll(mSprite_3d.getRoll() - 2.0f);
//	std::cout << "Roll angle " << mSprite_3d.getRoll() << std::endl;
	mSprite_3d.setOrigin(mSprite_3d.getOrigin().x - 2.0f, mSprite_3d.getOrigin().y - 2.0f);
	std::cout << "Origin" << mSprite_3d.getOrigin().x << " " << mSprite_3d.getOrigin().y << std::endl;
}


void Terrain::incYaw()
{
	mSprite_3d.setYaw(mSprite_3d.getYaw() + 2.0f);
	std::cout << "Yaw angle " << mSprite_3d.getYaw() << std::endl;
}

void Terrain::decYaw()
{
	mSprite_3d.setYaw(mSprite_3d.getYaw() - 2.0f);
	std::cout << "Yaw angle " << mSprite_3d.getYaw() << std::endl;
}

void Terrain::drawTerrain(sf::RenderWindow & window)
{
	setSprite();

	// draw the vertex array
	window.draw(mSprite_3d);
}
