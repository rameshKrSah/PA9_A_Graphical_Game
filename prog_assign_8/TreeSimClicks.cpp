#include "TreeSimClicks.h"

TreeSimClicks::TreeSimClicks()
{
	this->mIsOver = false;
}

void TreeSimClicks::setmIsOver(bool status)
{
	this->mIsOver = status;
}

bool TreeSimClicks::getmIsOver()
{
	return this->mIsOver;
}

void TreeSimClicks::runSim()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	TreeSimClicks userTree;
	sf::Event event;
	sf::Clock clock;
	sf::Time t1 = clock.restart();

	while (window.isOpen())
	{
		sf::Time t1 = clock.getElapsedTime();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			if (userTree.getmIsOver())
			{
				//Bens Flower scene
				//window.close();
			}

			if (event.type == sf::Event::KeyPressed)		//sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Keyboard::W)		//sf::Mouse::Button::Left)
				{
					userTree.mtStats.incWater();
					cout << "You Watered the Tree!" << endl;
				}

				if (event.key.code == sf::Keyboard::F)		//sf::Mouse::Button::Right)
				{
					userTree.mtStats.incFert();
					cout << "You Fertilized the Tree" << endl;
				}
			}

			//if (Tree size == 10)
			//{
			//	userTree.setmIsOver(true);
			//}
			
			cout << t1.asMilliseconds() << endl;
			if (t1.asMilliseconds() >= 5000)
			{
				cout << "Time Works" << endl;
				//Bens tree function
				t1 = clock.restart();

			}
		}

	}


}











