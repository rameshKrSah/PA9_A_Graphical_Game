/*
	@brief:		A graphical Game 
	@date:		Nov, 2018

	1. Terrain in SFML using Simplex Noise function from here, https://github.com/PawelWorwa/SimplexNoise 
	Planning to use the 2D terrain generated using the  simplex noise as the terrian for the game. The other option is to use Perlin Noise as the Noise function.
	
	TODO:
		- Make the terrain graphically nice
		- Change the Camera angle
		- Try to do the same with Perlin Noise function.

	References
		- http://libnoise.sourceforge.net/tutorials/tutorial4.html#beforebegin
		- https://flafla2.github.io/2014/08/09/perlinnoise.html
		- https://gist.github.com/Flafla2/f0260a861be0ebdeef76
		- https://github.com/Owen-Jackson/Sim-Worlds-Terrain A good report available here.
		- https://github.com/Auburns/FastNoise A library constaining all the noise functions
		- http://libnoise.sourceforge.net/tutorials/tutorial6.html
		- https://github.com/PawelWorwa/SimplexNoise
		- https://github.com/SamReha/SFML_Perlin_Terrain Perlin Noise implementation using Tiles


*/


#include <SFML/Graphics.hpp>
#include "SimplexNoise.hpp"

#include <cstdlib>
#include <ctime>
#include <memory>

/* ***** Example Class (for debug and noise visualisation) *****/
class ExampleNoise {
public:
	explicit ExampleNoise(int width, int height) :
		isGreyscale(false),
		height(height),
		width(width) {
		noiseTexture.create(width, height);
		pixels = std::unique_ptr<sf::Uint8[]>(new sf::Uint8[width * height * 4]);
	};
	virtual ~ExampleNoise() {};

	void drawNoise(sf::RenderWindow &window) {
		sf::Sprite noiseSprite;
		noiseSprite.setTexture(noiseTexture);
		window.draw(noiseSprite);
	};

	void generateNoise(void) {
		SimplexNoise noiseGenerator;
		noiseGenerator.setOctaves(7);
		noiseGenerator.setFrequency(2.0f);
		noiseGenerator.setPersistence(0.35f);

		for (std::size_t y = 0; y<height; ++y) {
			for (std::size_t x = 0; x<width; ++x) {
				float xPos = float(x) / float(width) - 0.5f;
				float yPos = float(y) / float(height) - 0.5f;

				float elevation = noiseGenerator.unsignedOctave(xPos, yPos);
				elevation = pow(elevation, 1.5f); //redistribution
				setPixel(x, y, elevation);
			}
		}

		noiseTexture.update(pixels.get());
	};

	void setGreyscale(bool isGreyscale) {
		this->isGreyscale = isGreyscale;
	};

private:
	bool         isGreyscale;
	unsigned int height;
	unsigned int width;
	sf::Texture  noiseTexture;
	std::unique_ptr<sf::Uint8[]> pixels;

	void setPixel(unsigned int x, unsigned int y, float value) {
		sf::Color color = getColor(value);
		pixels[4 * (y * width + x)] = color.r;
		pixels[4 * (y * width + x) + 1] = color.g;
		pixels[4 * (y * width + x) + 2] = color.b;
		pixels[4 * (y * width + x) + 3] = color.a;
	};

	sf::Color getColor(float value) {
		sf::Color color(0, 0, 0);

		if (isGreyscale) {
			color = sf::Color(value * 255, value * 255, value * 255, value * 255);

		}
		else {
			color = getBiome(value);
		}

		return color;
	};

	sf::Color getBiome(float value) {
		if (value < 0.15f)      return sf::Color(0, 0, 102); // deep water
		else if (value < 0.20f) return sf::Color(0, 51, 102); // water
		else if (value < 0.25f) return sf::Color(0, 102, 102); // shallow water

		//else if (value < 0.27f) return sf::Color(255, 255, 204); // beach
		// else if (value < 0.4f)  return sf::Color(76, 153, 0); // jungle
		//else if (value < 0.35f) return sf::Color(102, 204, 0); // plains
		
		else if (value < 0.6f)  return sf::Color(51, 102, 0); // forest
		
		//else if (value < 0.6f)  return sf::Color(204, 204, 0); // savannah
		
		else if (value < 0.7f)  return sf::Color(128, 128, 128); // low hills
		else if (value < 0.8f)  return sf::Color(96, 96, 96); // hills
		else if (value < 0.9f)  return sf::Color(48, 48, 48); // high hills
		else                     return sf::Color::White;           // snow
	};
};

/* ***** Main *****/
int main() {
	unsigned static int const width = 800;
	unsigned static int const height = 600;

	srand(time(0));

	ExampleNoise example(width, height);
	example.generateNoise();

	sf::RenderWindow window(sf::VideoMode(width, height), "Simplex Noise 2D visualisation");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		example.drawNoise(window);
		window.display();
	}

	return EXIT_SUCCESS;
}