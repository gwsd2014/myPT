#ifndef MazeRaceGame_H
#define MazeRaceGame_H

#pragma once
#include "Frame.h"

class MazeRaceGame :public Game{
public:
	//BE SURE TO SET TO 3D
	MazeRaceGame();
	~MazeRaceGame();
	virtual void update();
	virtual void render(unsigned int* objectTexIds);
	virtual void timer(int value);

protected:
	void drawRoom();

	float positionZ;
};

#endif