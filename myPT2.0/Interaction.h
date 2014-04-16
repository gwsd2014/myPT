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

	virtual void render(const unsigned int* objTexures){

	}
};

#endif

#ifndef Button_H
#define Button_H


class Button: public Interaction{
public:
	bool pressed;
	bool leftHand;
	float range;
	bool hover;
	int numFramesToHold;
	DotObject guide;
	Button() : Interaction() {
		pressed = false;
		this->range = 0.1f;
		int numFramesToHold = 20;
	}

	Button(float X, float Y) : Interaction(X, Y){
		pressed = false;
		hover = false;
		this->range = 0.1f;
		guide = DotObject(6, 0.05, 0.0, 0.0);
		this->numFramesToHold = 20;
	}

	Button(float X, float Y, float range) : Interaction(X, Y){
		pressed = false;
		hover = false;
		this->range = range;
		guide = DotObject(6, 0.05, 0.0, 0.0);
		this->numFramesToHold = 20;
	}

	Button(float X, float Y, float range, int numFrameToHold) : Interaction(X, Y){
		pressed = false;
		hover = false;
		this->range = range;
		guide = DotObject(6, 0.05, 0.0, 0.0);
		this->numFramesToHold = numFramesToHold;
	}


	virtual ~Button(){

	}

	virtual void render(const unsigned int* objectTexIDs){
		//printf("Rendering Button Interaction\n");
		//DotObject test(5, 0.02, X, Y);
		//test.render(objectTexIDs);
		if(hover && leftHand){
			vertex3 handData = GestureManager::Inst()->getCurrentData(0);
			guide.position.setx(handData.getx());
			guide.position.sety(handData.gety());
			guide.render(objectTexIDs);
		} else if(hover && !leftHand){
			vertex3 handData = GestureManager::Inst()->getCurrentData(1);
			guide.position.setx(handData.getx());
			guide.position.sety(handData.gety());
			guide.render(objectTexIDs);
		}
	}

	void resetButton(){
		pressed = false;
	}

	virtual void handleInteraction(){
		int resultLeft = GestureManager::Inst()->buttonPressed(0, X, Y, numFramesToHold, range/2);
		int resultRight = GestureManager::Inst()->buttonPressed(1, X, Y, numFramesToHold, range/2);
		//printf("Handling Button Interaction\n");
		if(resultRight == 2){
			pressed = true;
			leftHand = false;
			hover = true;
				printf("Pressed with right hand!\n");
		}
		else if(resultRight == 1){
			leftHand = false;
			hover = true;
		}
		else if(resultRight == 0){
			leftHand = false;
			hover = false;
		}else if(resultLeft == 2){
			pressed = true;
			leftHand = true;
			hover = true;
			printf("Pressed with left hand!\n");
		}
		else if(resultLeft == 1){
			leftHand = true;
			hover = true;
		}
		else if(resultLeft == 0){
			leftHand = false;
			hover = false;
		}
	}
};

#endif

#ifndef ButtonWithTexture_H
#define ButtonWithTexture_H
class ButtonWithTexture: public Interaction{
public:
	bool pressed;
	bool hover;
	bool leftHand;
	float range;
	DotObject prettyPicture;
	DotObject guide;
	vertex3 leftHandData;
	vertex3 rightHandData;

	ButtonWithTexture() : Interaction() {
		//dont use this
		pressed = false;
		leftHand = false;
		hover = false;
	}

	ButtonWithTexture(float X, float Y, float size, int texIDIndex) : Interaction(X, Y){
		pressed = false;
		prettyPicture = DotObject(texIDIndex, size, X - (size/2), Y- (size/2), 20);
		leftHand = false;
		hover = false;
		guide = DotObject(6, 0.05, 0.0, 0.0);
		range = size/2.0f;
	}

	ButtonWithTexture(float X, float Y, float size, int texIDIndex, float range, int numFramestoHold) : Interaction(X, Y){
		pressed = false;
		prettyPicture = DotObject(texIDIndex, size, X - (size/2), Y- (size/2), numFramestoHold);
		leftHand = false;
		this->range = range;
		hover = false;
		guide = DotObject(6, 0.05, 0.0, 0.0);
	}

	virtual ~ButtonWithTexture(){

	}

	void resetButton(){
		pressed = false;
	}

	void render(const unsigned int* objectTexIDs){
		prettyPicture.render(objectTexIDs);
		DotObject test(5, 0.02, X, Y);
		//test.render(objectTexIDs);
		if(hover && leftHand){
			vertex3 handData = GestureManager::Inst()->getCurrentData(0);
			guide.position.setx(handData.getx());
			guide.position.sety(handData.gety());
			guide.render(objectTexIDs);
		} else if(hover && !leftHand){
			vertex3 handData = GestureManager::Inst()->getCurrentData(1);
			guide.position.setx(handData.getx());
			guide.position.sety(handData.gety());
			guide.render(objectTexIDs);
		}
	}

	virtual void handleInteraction(){
		int resultLeft = GestureManager::Inst()->buttonPressed(0, X, Y, 20, range/2);
		int resultRight = GestureManager::Inst()->buttonPressed(1, X, Y, 20, range/2);
		//printf("Handling Button Interaction\n");
		if(resultRight == 2){
			pressed = true;
			leftHand = false;
			hover = true;
				printf("Pressed with right hand!\n");
		}
		else if(resultRight == 1){
			leftHand = false;
			hover = true;
		}
		else if(resultRight == 0){
			leftHand = false;
			hover = false;
		}else if(resultLeft == 2){
			pressed = true;
			leftHand = true;
			hover = true;
			printf("Pressed with left hand!\n");
		}
		else if(resultLeft == 1){
			leftHand = true;
			hover = true;
		}
		else if(resultLeft == 0){
			leftHand = false;
			hover = false;
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

	Slider(bool ishorizontal, float start, float end, float position) : Interaction(X, Y){
		//slideHandle = ButtonWithTexture(X, Y-.1, 0.07, 7, 0.1, 10);
		horizontal = ishorizontal;
		slid = false;
		percent = -1.0;
		if(horizontal){
			slideHandle = ButtonWithTexture((end-start)/2.0f, position, 0.07, 7, 0.07, 20);
			startPosX = start;
			endPosX = end;
			startPosY = endPosY = position;
		}else{
			slideHandle = ButtonWithTexture(position,(end-start)/2.0f, 0.07, 7, 0.07, 20);
			startPosY = start;
			endPosY = end;
			startPosX = endPosX = position;
		}
	}

	virtual ~Slider(){

	}

	virtual void render(const unsigned int* objectTexIDs){
		slideHandle.render(objectTexIDs);
	}

	virtual void handleInteraction(){
		slideHandle.handleInteraction();
		vertex3 leftHandData = GestureManager::Inst()->getCurrentData(0);
		vertex3 rightHandData = GestureManager::Inst()->getCurrentData(1);

		if(slideHandle.pressed && slideHandle.hover){
			slid = true;
		}

		//LEFT HAND IS MOST RECENT PRESS!
		if(slideHandle.leftHand){
			if(slid && horizontal && (leftHandData.gety() < (slideHandle.Y + slideHandle.range/2)) && (leftHandData.gety() > (slideHandle.Y-slideHandle.range/2))){
					printf("left hand change position");
					slideHandle.prettyPicture.position.setx(leftHandData.getx());
					slideHandle.X = leftHandData.getx();
			}else if(slid && !horizontal && (leftHandData.getx()<(slideHandle.X + slideHandle.range/2)) && (leftHandData.getx() > (slideHandle.X-slideHandle.range/2))){
					slideHandle.prettyPicture.position.sety(leftHandData.gety());
					slideHandle.Y = leftHandData.gety();
			}else{
				slid = false;
			}
		}else{	//right hand most recent press
			if(slid && horizontal && (rightHandData.gety()< (slideHandle.Y + slideHandle.range/2)) && (rightHandData.gety() > (slideHandle.Y-slideHandle.range/2))){
				slideHandle.prettyPicture.position.setx(rightHandData.getx());
				slideHandle.X = rightHandData.getx();
			}else if(slid && !horizontal && (rightHandData.getx()< (slideHandle.X + slideHandle.range/2)) && (rightHandData.getx() > (slideHandle.X-slideHandle.range/2))){
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