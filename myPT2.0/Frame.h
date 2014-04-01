#ifndef Frame_H
#define Frame_H

#include <iostream>
#include <sstream>
//Interface that main deals with and all current frames must deal with
class Frame{
public:
	
	//holds an index of the array that holds background textures in main
	unsigned int backgroundIDIndex;
	std::stringstream string;
	Frame(){
		string << " ";
	}
	~Frame(){}
	virtual void render(const unsigned int* objectTexIDs){}
	virtual void update(){}
	virtual void timer(int value){}
};

#endif