#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <GL/freeglut.h>
#include "common/TextureManager.h"
#include "common/GLUtilities.h"

class Button{
public:
	GLfloat texOffset[4];
	GLfloat size;
	unsigned int objectTextureID;


	float percentX;
	float percentY;
	bool pressed;

	Button(){
		percentX = 0.0f;
		percentY = 0.0f;
		pressed = false;
	}

	Button(float x, float y){
		percentX = x;
		percentY = y;
	}

};

#endif