#ifndef Interaction_H
#define Interaction_H

#include "common/GestureManager.h"
#include "DotObject.h"

class Interaction{
public:
	float X, Y;

	Interaction(){
		X = 0.0;
		Y = 0.0;
	}

	Interaction(float X, float Y){
		this->X = X;
		this->Y = Y;
	}

	virtual ~Interaction(){
		//see no need for this to do anything
	}
	
	virtual void handleInteraction(){
		//how to accomodate this for each button?
		//create individual buttons for each need?
	}

	virtual void render(const unsigned int* objTexures){}
};

#endif

#ifndef Button_H
#define Button_H


class Button: public Interaction{
public:
	bool pressed;
	bool leftHand;
	Button() : Interaction() {
		pressed = false;
	}

	Button(float X, float Y) : Interaction(X, Y){
		pressed = false;
	}

	virtual ~Button(){

	}

	virtual void handleInteraction(){
		if(GestureManager::Inst()->buttonPressed(0, X, Y)){
			pressed =  true;
			leftHand = true;
		}
		if(GestureManager::Inst()->buttonPressed(1, X, Y)){
			pressed =  true;
			leftHand = false;
		}
	}
};

#endif

#ifndef ButtonWithTexture_H
#define ButtonWithTexture_H
class ButtonWithTexture: public Interaction{
public:
	bool pressed;
	bool beingPressed;
	bool leftHand;
	DotObject prettyPicture;

	ButtonWithTexture() : Interaction() {
		//dont use this
		pressed = false;
		leftHand = false;
		beingPressed = false;
	}

	ButtonWithTexture(float X, float Y, float size, int texIDIndex) : Interaction(X, Y){
		pressed = false;
		prettyPicture = DotObject(texIDIndex, size, X, Y);
		leftHand = false;
		beingPressed = false;
	}

	virtual ~ButtonWithTexture(){

	}

	void render(const unsigned int* objectTexIDs){
		prettyPicture.render(objectTexIDs);
	}

	virtual void handleInteraction(){
		if(GestureManager::Inst()->buttonPressed(0, X, Y)){
			printf("Left Hand button being pressed");
			pressed = true;
			leftHand = true;
			beingPressed = true;
		}
		else if(GestureManager::Inst()->buttonPressed(1, X, Y)){
			pressed = true;
			leftHand = false;
			beingPressed = true;
		}else{
			beingPressed = false;
		}
	}
};

#endif

#ifndef Slider_H
#define Slider_H
class Slider: public Interaction{
public:
	ButtonWithTexture slideHandle;
	bool horizontal;	//true if a horizontal slider, false if vertical slider
	bool slid;
	float startPosX, startPosY;
	float endPosX, endPosY;
	float percent;
	Slider() : Interaction() {	
	}

	Slider(bool ishorizontal, float X, float Y) : Interaction(X, Y){
		slideHandle = ButtonWithTexture(X, Y-.05, 0.1, 7);
		horizontal = ishorizontal;
		slid = false;
		percent = -1.0;
	}

	virtual ~Slider(){

	}

	virtual void render(const unsigned int* objectTexIDs){
		slideHandle.render(objectTexIDs);
	}

	virtual void handleInteraction(){
		slideHandle.handleInteraction();
		vertex3 leftHandData = GestureManager::Inst()->getCurrentHandData(0);
		vertex3 rightHandData = GestureManager::Inst()->getCurrentHandData(1);

		if(slideHandle.beingPressed){
			slid = true;
		}

		//LEFT HAND IS MOST RECENT PRESS!
		if(slideHandle.leftHand){
			if(slid && horizontal && (leftHandData.gety() < (slideHandle.Y + 0.1)) && (leftHandData.gety() > (slideHandle.Y-0.1))){
					printf("left hand change position");
					slideHandle.prettyPicture.position.setx(leftHandData.getx());
					slideHandle.X = leftHandData.getx();
			}else if(slid && !horizontal && (leftHandData.getx()<(slideHandle.X + 0.1)) && (leftHandData.getx() > (slideHandle.X-0.1))){
					slideHandle.prettyPicture.position.sety(leftHandData.gety());
					slideHandle.Y = leftHandData.gety();
			}else{
				slid = false;
			}
		}else{	//right hand most recent press
			if(slid && horizontal && (rightHandData.gety()< (slideHandle.Y + 0.1)) && (rightHandData.gety() > (slideHandle.Y-0.1))){
				slideHandle.prettyPicture.position.setx(rightHandData.getx());
				slideHandle.X = rightHandData.getx();
			}else if(slid && !horizontal && (rightHandData.getx()< (slideHandle.X + 0.1)) && (rightHandData.getx() > (slideHandle.X-0.1))){
					slideHandle.prettyPicture.position.sety(rightHandData.gety());
					slideHandle.Y = rightHandData.gety();
			}else {
				slid = false;
			}
		}
		if(slideHandle.pressed && horizontal)
			percent = (slideHandle.X - startPosX) / (endPosX -startPosX);
		else if(slideHandle.pressed && !horizontal)
			percent = (slideHandle.Y - startPosY) / (endPosY -startPosY);
	}
};

#endif