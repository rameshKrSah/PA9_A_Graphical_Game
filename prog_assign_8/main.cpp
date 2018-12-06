/*
	----------------- TEAM MEMBERS ---------------------
	Mitch Boesel
	Benjamin 
	Michaela Bayerlova
	Ramesh Kumar Sah
	
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

#include "Terrain.h"
#include "Background.h"
#include "Tree.h"
#include "TreeStats.h"

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
	// create the window 
	sf::RenderWindow window(sf::VideoMode(width, height), "Tree Simulator", sf::Style::Close);
	sf::View view;

	int start = 1;
	int play = 0;

	// clock 
	sf::Clock clock;
	sf::Time t1 = clock.restart();

	// Tree stats object
	TreeStats treeStats;

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


	// menu part 
	sf::Font font;
	if (!font.loadFromFile("SimplySquare.ttf"))
	{
		std::cout << "Error loading file" << std::endl;
		return LOAD_FAILURE;
	}

	//Main Menu
	sf::Text text1, text3, text4;
	
	text1.setFont(font);
	text1.setString("Welcome to TREE SIMULATOR Cs 122");
	text1.setCharacterSize(32);
	text1.setFillColor(sf::Color::Red);
	text1.setStyle(sf::Text::Underlined);
	text1.setPosition(window.getSize().x / 4, 0);

	text4.setFont(font);
	text4.setString("\n \n \n \nPlant a tree with left mouse click and nurture it.\n\nIt will grow to a little plant and eventually to a tree.\n\n\nKeys to use:\n\nW :: To  water\n\nF :: To  Fertilize");
	text4.setCharacterSize(24);
	text4.setFillColor(sf::Color::White);

	text3.setFont(font);
	text3.setLineSpacing(1);
	text3.setString(" \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \nTo Play : press Space\n\nTo Reset : press BackSpase\n\nTo Exit : press Enter");
	text3.setCharacterSize(24);
	text3.setFillColor(sf::Color::White);

	
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


			if (event.type == sf::Event::KeyPressed)		//sf::Event::MouseButtonPressed)
			{
				// menu 
				if (event.key.code == sf::Keyboard::Space)
				{
					start = 0;
					play = 1;
				}

				// menu 
				if (event.key.code == sf::Keyboard::Enter)
				{
					window.close();
					backgroundMusicStop(music);
				}

				if (event.key.code == sf::Keyboard::BackSpace)
				{
					trees.clear();
				}

				if (event.key.code == sf::Keyboard::W)		//sf::Mouse::Button::Left)
				{
					treeStats.incWater();
					cout << "You Watered the Tree!" << endl;
				}

				if (event.key.code == sf::Keyboard::F)		//sf::Mouse::Button::Right)
				{
					treeStats.incFert();
					cout << "You Fertilized the Tree" << endl;
				}
			}

			// get the elapsed time to grow the trees
			t1 = clock.getElapsedTime();
			if (t1.asMilliseconds() >= 2000)
			{
				_TREE_HEALTH_ health = (_TREE_HEALTH_)treeStats.calcHealth();
				
				cout << "Health " << health << endl;
				for (int i = 0; i < trees.size(); i++)
				{
					trees[i].setHealth(health);

					if (health == HEALTHY)
					{
						//trees[i].setLoop(trees[i].getNewlevel());
						trees[i].incremenetLevel();
					}

				}
				
				//Bens tree function
				t1 = clock.restart();
			}

			/*
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
			*/
		}
		
		// clear the window 
		window.clear();
		
		//show menu
		if (start == 1)
		{
			window.draw(text1);
			window.draw(text4);
			window.draw(text3);
		}

		// play the background score
		backgroundMusicPlay(music);

		if (play == 1)
		{
			// draw the sky background
			window.draw(background);

			// draw the noise on the window
			window.draw(terrain);

			// draw the tree
			for (int i = 0; i < trees.size(); i++)
			{
				trees[i].Render(window);
			}
		}

		// show everything on the window
		window.display();
	}

	return EXIT_SUCCESS;
}
