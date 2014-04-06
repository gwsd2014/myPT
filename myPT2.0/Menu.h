#ifndef MainMenu_H
#define MainMenu_H

#pragma once
#include "Frame.h"
#include "Interaction.h"
#include "DotSpot.h"

class MainMenu: public Frame{

public:
	MainMenu(): Frame(){
		welcome = Button(0.5f, 0.666f, 0.1);
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

//-------------------Screen 7---------------------------//
#ifndef TimeSinceMenu_H
#define TimeSinceMenu_H
class TimeSinceMenu: public Frame{
public:
	TimeSinceMenu(): Frame(){
		backgroundIDIndex = 7;
		continueButton = Button(0.5, 0.5, 0.1);
		timeSlider = Slider(true, 0.5, 0.7, 0.15, .85, .65);
		interactions.push_back(&continueButton);
		interactions.push_back(&timeSlider);

	}

	virtual void update(){
		__super::update();

		if(continueButton.pressed && timeSlider.slid){		
			//SAVE PERCENTAGE!
			//RUN ALGORITHM TO DETERMINE SYSTEM!
			changeView(new DotSpot());
		}
	}

protected:
	Button continueButton;
	Slider timeSlider;
};

#endif

//-------------------Screen 6---------------------------//
#ifndef MeniscusMenu_H
#define MeniscusMenu_H
class MeniscusMenu: public Frame{
public:
	MeniscusMenu(): Frame(){
		backgroundIDIndex = 6;
		yesButton = Button(0.7, 0.5, 0.1);
		noButton = Button(0.3, 0.5, 0.1);
		interactions.push_back(&yesButton);
		interactions.push_back(&noButton);

	}

	virtual void update(){
		__super::update();

		if(yesButton.pressed){		
			//SAVE ANSWER!
			changeView(new TimeSinceMenu());
		}else if(noButton.pressed){
			changeView(new TimeSinceMenu());
		}
	}

protected:
	Button yesButton;
	Button noButton;
};
#endif

//-------------------Screen 5---------------------------//
#ifndef BehindKneeMenu_H
#define BehindKneeMenu_H
class BehindKneeMenu: public Frame{
public:
	BehindKneeMenu(): Frame(){
		backgroundIDIndex = 5;
		yesButton = Button(0.7f, 0.5f, 0.1f);
		noButton = Button(0.3f, 0.5f, 0.1f);
		interactions.push_back(&yesButton);
		interactions.push_back(&noButton);

	}

	virtual void update(){
		__super::update();

		if(yesButton.pressed){		
			//SAVE ANSWER!
			changeView(new MeniscusMenu());
		}else if(noButton.pressed){
			changeView(new MeniscusMenu());
		}
	}

protected:
	Button yesButton;
	Button noButton;
};

#endif

//-------------------Screen 4---------------------------//
#ifndef ScarMenu_H
#define ScarMenu_H
class ScarMenu: public Frame{
public:
	ScarMenu(): Frame(){
		backgroundIDIndex = 4;
		yesButton = Button(0.7f, 0.5f, 0.1f);
		noButton = Button(0.3f, 0.5f, 0.1f);
		interactions.push_back(&yesButton);
		interactions.push_back(&noButton);

	}

	virtual void update(){
		__super::update();

		if(yesButton.pressed){		
			//SAVE ANSWER!
			changeView(new BehindKneeMenu());
		}else if(noButton.pressed){
			changeView(new BehindKneeMenu());
		}
	}

protected:
	Button yesButton;
	Button noButton;
};

#endif


//-------------------Screen 3---------------------------//
#ifndef FeelingMenu_H
#define FeelingMenu_H
class FeelingMenu: public Frame{
public:
	FeelingMenu(): Frame(){
		backgroundIDIndex = 3;
		continueButton = Button(0.5f, 0.5f, 0.1f);
		feelingSlider = Slider(true, 0.5f, 0.7f, 0.15f, .85f, .65f);
		interactions.push_back(&continueButton);
		interactions.push_back(&feelingSlider);

	}

	virtual void update(){
		__super::update();

		if(continueButton.pressed && feelingSlider.slid){		
			//SAVE PERCENTAGE!
			changeView(new ScarMenu());
		}
	}

protected:
	Button continueButton;
	Slider feelingSlider;
};

#endif

//-------------------Screen 2---------------------------//
#ifndef ContinueMenu_H
#define ContinueMenu_H
class ContinueMenu: public Frame{
public:
	ContinueMenu(): Frame(){
		backgroundIDIndex = 2;
		continueButton = Button(0.5f, 0.8f, 0.2f);
		interactions.push_back(&continueButton);
	}

	virtual void update(){
		__super::update();

		if(continueButton.pressed){		
			changeView(new FeelingMenu());
		}
	}

protected:
	Button continueButton;
};

#endif

//----------When you boot up the game!-----------------//
//-------------------Screen 1---------------------------//
#ifndef LogoMenu_H
#define LogoMenu_H

class LogoMenu: public Frame{
public:
	LogoMenu(): Frame(){
		backgroundIDIndex = 1;
		clickAnywhere = Button(0.5f, 0.5f, 1.0f);
		interactions.push_back(&clickAnywhere);
	}

	virtual void update(){
		__super::update();

		if(clickAnywhere.pressed){		
			ContinueMenu* contMenu = new ContinueMenu();
			changeView(contMenu);
		}
	}

protected:
	Button clickAnywhere;
};

#endif
//-------------------------------------------------------//