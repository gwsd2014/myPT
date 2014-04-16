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
	bool feetOnTheGround(bool singleLeg, bool leftFoot);
	bool correctForm();

	//MEMBER DATA
	//game globals
	bool hotDonutTouched;
	bool shuffled;
	bool leftHand; //true for left, false if right;
	int score, life;
	int phase, difficulty;
	int framesBetweenSquats;
	bool leftLeg;
	Button restart;
	Button exit;

	std::vector<DotObject> donuts;
	
	DotObject guide;	//originally set to blue
	DotObject checkMark;
	DotObject footMistake;
	DotObject squatMistake;
	DotObject legHint;
	DotObject leftFootPlacement;
	DotObject rightFootPlacement;

	int hotDonut;		//Location of the green donut
	int mistake;

};

#endif