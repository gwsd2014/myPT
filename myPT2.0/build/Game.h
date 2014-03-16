#ifndef _GAME_H_
#define _GAME_H_

#pragma once
#include "Button.h"
#include <vector>

class Game{

public:
	int score;
	int lives;
	unsigned int gameOverTexID;
	unsigned int backgroundTexID;
	int difficulty;
	vector<Button> buttons;

	Game(){
		score = 0;
		lives = 100;
		gameOverTexID = 6;
		backgroundTexID = 1;
		//CREATE EXIT AND RESTART BUTTONS!
		buttons.push_back(Button(0.9f, 0.9f));
	}

	virtual void update(){
		printf("Executing general version of Game update");
	}

	virtual void timer(int frame){
		//do something?
	}

	void gameOver(){

	}

	virtual void render(){
		//render stuff!
		printf("Executing general version of Game render");
	}
};

#endif