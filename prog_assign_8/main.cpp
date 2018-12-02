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
		- http://libnoise.sourceforge.net/tutorials/tutorial6.html
		- https://flafla2.github.io/2014/08/09/perlinnoise.html
		- https://gist.github.com/Flafla2/f0260a861be0ebdeef76
		- https://github.com/Owen-Jackson/Sim-Worlds-Terrain A good report available here.
		- https://github.com/Auburns/FastNoise A library constaining all the noise functions
		- https://github.com/PawelWorwa/SimplexNoise
		- https://github.com/SamReha/SFML_Perlin_Terrain Perlin Noise implementation using Tiles
		- https://www.youtube.com/watch?v=UQNZ1207MaI

*/


#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <ctime>

#include "Points.h"
#include "Terrain.h"

unsigned static int const width = 1000;
unsigned static int const height = 600;

int main() 
{
	Terrain terrain(width, height, 6, 2.0, 0.4);
	// generate the noise for the terrain 
	terrain.generateNoise();
	
	// create the window 
	sf::RenderWindow window(sf::VideoMode(width, height), "Simplex Noise 2D visualisation", sf::Style::Close);
	sf::View view;
	
	// load the blue sky texture 
	sf::Texture texture;
	if (!texture.loadFromFile("blue_sky.jpg"))
		return -68;

	// create the sprite fromt the blue sky texture 
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setOrigin(0.0f, 0.0f);

	// game loop //
	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
		}
		
		// clear the window 
		window.clear();
		
		// draw the sky background
		window.draw(sprite);

		// draw the noise on the window
		window.draw(terrain);

		// show everything on the window
		window.display();
	}

	return EXIT_SUCCESS;
}
