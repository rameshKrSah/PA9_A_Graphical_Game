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
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>

#include "Points.h"
#include "Terrain.h"
#include "Background.h"
#include "Tree.h"

unsigned static int const width = 1000;
unsigned static int const height = 600;
#define LOAD_FAILURE		-999

void backgroundMusicPlay(sf::Music & sound)
{
	static bool loaded = false;

	if (!loaded)
	{
		sound.setLoop(true);
		sound.play();
		loaded = true;
	}
}

void backgroundMusicStop(sf::Music & sound)
{
	sound.stop();
}

int main() 
{
	// object of the Terrain class
	Terrain terrain(width, height, 6, 2.0, 0.4);

	// generate the noise for the terrain 
	terrain.generateNoise();
	
	// object of the background class
	Background background;

	// Tree objects
	std::vector <Tree> trees;

	// load the blue sky texture 
	if (!background.loadBackground("blue_sky.jpg"))
	{
		std::cout << "ERROR: background load failed " << std::endl;
		return LOAD_FAILURE;
	}

	// background music
	sf::Music music;
	if (!music.openFromFile("background_2.wav"))
	{
		return LOAD_FAILURE;
	}

	// create the window 
	sf::RenderWindow window(sf::VideoMode(width, height), "Simplex Noise 2D visualisation", sf::Style::Close);
	sf::View view;
	
	// game loop //
	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
				backgroundMusicStop(music);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// get the cursor position relative to the window 
				sf::Vector2i start_coordinates = sf::Mouse::getPosition(window);

				// create a new tree and set its parameters
				Tree newTree(float(start_coordinates.x), float(start_coordinates.y));
				
				// insert the tree into the vector
				trees.push_back(newTree);

			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					terrain.incPitch();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					terrain.decPitch();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					terrain.incYaw();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					terrain.decYaw();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					terrain.incRoll();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					terrain.decRoll();
				}
			}
		}
		
		// clear the window 
		window.clear();
		
		// play the background score
		backgroundMusicPlay(music);

		// draw the sky background
		window.draw(background);

		// draw the noise on the window
		window.draw(terrain);

		// draw the tree
		for (int i = 0; i < trees.size(); i++)
		{
			trees[i].Render(window);
		}


		// show everything on the window
		window.display();
	}

	return EXIT_SUCCESS;
}


/*
void r()
{
	std::vector<sf::Vertex> vertices;
	int wi = 5;
	int he = 10;

	vertices.push_back(sf::Vertex(sf::Vector2f(10, 20), sf::Color::Green));
	vertices.push_back(sf::Vertex(sf::Vector2f(10 + wi, 20), sf::Color::Green));
	vertices.push_back(sf::Vertex(sf::Vector2f(10, 20 + he), sf::Color::Green));
	vertices.push_back(sf::Vertex(sf::Vector2f(10 + wi, 20 + he), sf::Color::Green));

	
	int size = vertices.size();
	static int i = 0;
	while (size)
	{
		window.draw(&vertices[i], 4, sf::Quads);
		size -= 4;
		i += 4;
	}

}
*/

