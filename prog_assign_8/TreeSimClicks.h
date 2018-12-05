#include "TreeStats.h"

class TreeSimClicks
{
public:
	TreeSimClicks();

	void runSim();
		
	void setmIsOver(bool status);
	bool getmIsOver();

	
private:
	bool mIsOver;
	TreeStats mtStats;
};



