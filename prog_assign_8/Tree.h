#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>
#include <ctime>
#include <thread>
#include <chrono>
#include <cmath>
#include "math.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::fstream;

class Tree : public sf::RectangleShape
{
public:

	typedef enum TREE_HEALTH
	{
		HEALTHY = 1,
		UNHEALTHY,
		NEUTRAL
	}_TREE_HEALTH_;


	Tree();
	Tree(const float x_value, const float y_value);
	~Tree();
	void setStartLocation(sf::Vector2f & newLocation);
	void setStartLocation(double x, double y);
	void setHeight(double newHeight);
	void setWidth(double newWidth);
	void setScalingVariable(double newScalar);
	void setRAngle(double newRight);
	void setLAngle(double newLeft);
	void setColorFLower(sf::Color Flower);
	void setColorStem(sf::Color Stem);
	void setLoop(int AOccured);
	void setHealth(int Healthlvl, int index);
	int getHealth(int index);
	int getLoop();
	double getHeight();
	double getWidth();
	sf::Color GetFlowerColor();
	sf::Color GetStemColor();
	double GetScalingVariable();
	double GetRAngle();
	double GetLAngle();
	sf::Vector2f GetStartPoint();
	void setHealth(_TREE_HEALTH_ h);

	void RunTreeBuild();
	int TestHEandUN();
	void TestStep();
	void Render(sf::RenderWindow& window);

protected:
	void runIt();
	void drawTree(int iteration, const sf::Vector2f& rootPosition, double rootRotation, sf::RenderWindow& window, bool BROL);
	void GrowFlowers(const sf::Vector2f& rootPosition, sf::RenderWindow& window);

private:
	sf::Color STColor;
	sf::Color FlowerColor;
	double ScalingV;
	double RAngle;
	double LAngle;
	double Width;
	double Length;
	sf::Vector2f StartPoint;
	int NumberLoop;
	_TREE_HEALTH_ treeHealth;

	int HealthTrack[9];

};