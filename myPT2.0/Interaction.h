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
};

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
			pressed = true;
			leftHand = true;
		}
		if(GestureManager::Inst()->buttonPressed(1, X, Y)){
			pressed = true;
			leftHand = false;
		}
	}
};

class ButtonWithTexture: public Interaction{
public:
	bool pressed;
	bool leftHand;
	DotObject prettyPicture;

	ButtonWithTexture() : Interaction() {
		//dont use this
		pressed = false;
		leftHand = false;
	}

	ButtonWithTexture(float X, float Y, int texIDIndex) : Interaction(X, Y){
		pressed = false;
		prettyPicture = DotObject(texIDIndex, 0.1, X, Y);
		leftHand = false;
	}

	virtual ~ButtonWithTexture(){

	}

	void render(const unsigned int* objectTexIDs){
		prettyPicture.render(objectTexIDs);
	}

	virtual void handleInteraction(){
		if(GestureManager::Inst()->buttonPressed(0, X, Y)){
			pressed = true;
			leftHand = true;
		}
		if(GestureManager::Inst()->buttonPressed(1, X, Y)){
			pressed = true;
			leftHand = false;
		}
	}
};

class Slider: public Interaction{
public:
	ButtonWithTexture slideHandle;
	float startPosX, startPosY;
	float endPosX, endPosY;
	Slider() : Interaction() {	
	}

	Slider(float X, float Y) : Interaction(X, Y){
		slideHandle = ButtonWithTexture(X, Y, 7);
	}

	virtual ~Slider(){

	}

	void render(const unsigned int* objectTexIDs){
		slideHandle.render(objectTexIDs);
	}

	virtual void handleInteraction(){
		slideHandle.handleInteraction();
		if(slideHandle.pressed && slideHandle.leftHand){
			slideHandle.X = GestureManager::Inst()->getCurrentHandData(0).getx();
			slideHandle.Y = GestureManager::Inst()->getCurrentHandData(0).gety();
		}
		else if(slideHandle.pressed){
			slideHandle.X = GestureManager::Inst()->getCurrentHandData(1).getx();
			slideHandle.Y = GestureManager::Inst()->getCurrentHandData(1).gety();
		}
	}
};
