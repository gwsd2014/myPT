#ifndef Frame_H
#define Frame_H

#include <iostream>
#include <sstream>
#include "Interaction.h"

//Interface that main deals with and all current frames must deal with
class Frame{
public:
	//holds an index of the array that holds background textures in main
	unsigned int backgroundIDIndex;
	std::stringstream string;
	vector<Interaction*> interactions;
	bool viewUpdated;
	Frame* nextFrame;
	Frame(){
		string << " ";
		viewUpdated = false;
	}
	~Frame(){}
	virtual void render(const unsigned int* objectTexIDs){
		for(int i=0; i<interactions.size(); i++){
			interactions.at(i)->render(objectTexIDs);
		}
	}

	virtual void update(){
		//might cause problems
		for(int i=0; i<interactions.size(); i++){
			interactions.at(i)->handleInteraction();
		}
	}

	void changeView(Frame* nextFrame){
		this->nextFrame = nextFrame;
		viewUpdated = true;
	}

	virtual void timer(int value){
		//printf("I do something!");
	}
};

#endif