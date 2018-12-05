#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <SFML\Graphics.hpp>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <SFML/System.hpp>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class TreeStats
{
public:
	TreeStats();
	
	int getmNumWater();
	int getmNumFert();
	//int getmHealth();

//	void setmHealth(int health);
	void setmNumWater(int newWater);
	void setmNumFert(int newFert);

	int calcHealth();
	void incWater();
	void incFert();
	void resetW();
	void resetF();

private:
	int mNumWater;
	int mNumFert;
	//int mHealth;
};