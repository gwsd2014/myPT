#ifndef _GAMEDOTSPOT_H_
#define _GAMEDOTSPOT_H_

#pragma once
#include "DotObject.h"
#include "Game.h"
#include "Player.h"
#include <vector>

class GameDotSpot : public Game{

public:
	int hotDonut;	//location of green donut
	std::vector<DotObject> donuts;
	Player* player;


	void init();

	GameDotSpot();	//extends Game();

	GameDotSpot(Player* playerPtr);

	virtual void update();

	void timer(int frame);

	void shuffleDots();

	virtual void render();

};

#endif //GameDotSpot