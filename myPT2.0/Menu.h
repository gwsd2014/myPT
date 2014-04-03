#ifndef MainMenu_H
#define MainMenu_H

#pragma once
#include "Frame.h"
#include "Interaction.h"
#include "DotSpot.h"

class MainMenu: public Frame{

public:
	MainMenu(): Frame(){
		welcome = Button(0.5f, 0.666f);
		slider = Slider(true, 0.5f, 0.333f);
		interactions.push_back(&welcome);
		interactions.push_back(&slider);
		backgroundIDIndex = 1;
	}

	virtual void update(){
		__super::update();

		if(welcome.pressed){		
			changeView(new DotSpot());
		}
		if(slider.slid){
			
		}
	}
protected:
	Button welcome;
	Slider slider;
};

#endif

#ifndef PainMenu_H
#define PainMenu_H
class PainMenu: public Frame{
public:
	PainMenu(): Frame(){
		scar = Slider(true, 0.5f, 0.3f);
		swelling = Slider(true, 0.5, 0.6);
		soreness = Slider(true, 0.9, 0.9);
		interactions.push_back(&scar);
		interactions.push_back(&swelling);
		interactions.push_back(&soreness);
	}

	virtual void update(){
		__super::update();
	}
protected:
	Slider scar;
	Slider swelling;
	Slider soreness;	//?
};

#endif