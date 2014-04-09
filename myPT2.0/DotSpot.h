#ifndef DotSpot_H
#define DotSpot_H


#include "DotObject.h"
#include <vector>
#include "common/GestureManager.h"
#include "Frame.h"

class DotSpot: public Game{
public:
	DotSpot();
	DotSpot(int difficulty, Frame* goBack);

	virtual void timer(int value);

	virtual void render(const unsigned int* textureArray);

	virtual void update();
	
private:
	void shuffleDots();
	bool correctForm();

	//MEMBER DATA
	//game globals
	bool hotDonutTouched;
	bool shuffled;
	bool leftHand; //true for left, false if right;
	int score, life;
	int phase, difficulty;
	int framesBetweenSquats;
	bool singleLeg, leftLeg;
	Button restart;
	Button exit;

	std::vector<DotObject> donuts;
	
	DotObject guide;	//originally set to blue
	DotObject checkMark;

	int hotDonut;		//Location of the green donut

};

#endif