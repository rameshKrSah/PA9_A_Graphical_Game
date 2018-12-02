#pragma once
#include <cstdlib>
#include <memory>
#include <SFML/Graphics.hpp>

#include "SimplexNoise.hpp"
#include "Sprite3d.hpp"


/*
	## UNDERSTANDING THE OCTAVES, FREQUENCY, AND PERSISTANCE

	- Octaves :: The higher the octave number, the busier the terrain. This is because higher octaves have higher
	frequencies than lower octaves. The amount of details increases when the number of octaves increases.
	
	- Frequency :: The frequency determines how many changes occur along a unit length. Increasing the frequency
	will increase the terrain featires (and also decrease the size of these features) in a terrain height map.

	- Persistance :: The persistance value determines how quickly tha amplitudes fall for each successive octaves.
	Increasing the persistance value will create a rougher terrian height map, while decreasing the persistance value 
	will create a smoother terrain map.


*/


class Terrain : public sf::Drawable, public sf::Transformable
{

private:
	unsigned int mHeight, mWidth;
	sf::Vector2u mWindowSize;
	sf::Sprite3d mSprite_3d;
	sf::Uint8 * mPixels;
	sf::Texture mNoiseTexture;
	unsigned int mOctaves;
	float mFrequency, mPersistance;
	float mPitchAngle;

public:
	
	Terrain();
	Terrain(unsigned int width, unsigned int height, unsigned int octaves = 8, float frequency = 2.0f, 
		float persistance = 0.45f);
	~Terrain();
	void generateNoise(void);
	void drawTerrain(sf::RenderWindow & window);

private:
	sf::Color getColor(const float value);
	void setPixel(const unsigned int x, const unsigned int y, const float value);
	sf::Color getBiome(const float value);
	void setSprite();
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw the vertex array
		target.draw(mSprite_3d);
	}
};

