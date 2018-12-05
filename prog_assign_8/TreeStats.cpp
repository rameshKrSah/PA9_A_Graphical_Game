#include "TreeStats.h"
#include "Tree.h"

TreeStats::TreeStats()
{
	this->mNumWater = 0;
	this->mNumFert = 0;
}

//getters
int TreeStats::getmNumWater()
{
	return this->mNumWater;
}

int TreeStats::getmNumFert()
{
	return this->mNumFert;
}

//setters
void TreeStats::setmNumWater(int newWater)
{
	this->mNumWater = newWater;
}

void TreeStats::setmNumFert(int newFert)
{
	this->mNumFert = newFert;
}


// member functions
int TreeStats::calcHealth()
{
	int health = 0;
	int condition = 0;

	//determining health of watering
	if (mNumWater <= 1 || mNumWater >= 8)	//unhealthy 
	{
		health--;
	}
	else if (mNumWater >= 2 && mNumWater <= 5)	//healthy
	{
		health++;
	}
	else	//nuetral
	{
		health = health;
	}

	//determining health of fertilization
	if (mNumFert == 0 || mNumFert == 4)		// nuetral
	{
		health = health;
	}
	else if (mNumFert >= 1 && mNumFert <= 3)	//healthy
	{
		health++;
	}
	else	//unhealthy
	{
		health--;
	}

	//determining condition
	if (health >= 1)	//healthy
	{
		condition = HEALTHY;
	}
	else if (health == 0)	//nuetral
	{
		condition = NEUTRAL;
	}
	else if (health < 0)	//unhealthy
	{
		condition = UNHEALTHY;
	}

	this->resetW();
	this->resetF();

	return condition;
}

void TreeStats::incWater()
{
	mNumWater++;
}

void TreeStats::incFert()
{
	mNumFert++;
}

void TreeStats::resetW()
{
	this->mNumWater = 0;
}

void TreeStats::resetF()
{
	this->mNumFert = 0;
}