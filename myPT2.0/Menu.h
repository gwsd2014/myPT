#ifndef MainMenu_H
#define MainMenu_H

#pragma once
#include "Frame.h"
#include "Interaction.h"
#include "DotSpot.h"
#include "MazeRaceGame.h"

class MainMenu: public Frame{
	public:
		MainMenu();
		virtual void update();
	protected:
		ButtonWithTexture dotSpotButton;
		ButtonWithTexture mazeRaceButton;
		Slider slider;
		DotObject phase;
		DotObject difficulty;
};

#endif

//-------------------Screen 7---------------------------//
#ifndef TimeSinceMenu_H
#define TimeSinceMenu_H
class TimeSinceMenu: public Frame{
public:
	TimeSinceMenu();

	virtual void update();

protected:
	ButtonWithTexture continueButton;
	Slider timeSlider;
	bool continueAdded;
};

#endif

//-------------------Screen 6---------------------------//
#ifndef MeniscusMenu_H
#define MeniscusMenu_H
class MeniscusMenu: public Frame{
public:
	MeniscusMenu();

	virtual void update();

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
	BehindKneeMenu();

	virtual void update();
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
	ScarMenu();

	virtual void update();

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
	FeelingMenu();

	virtual void update();

protected:
	ButtonWithTexture continueButton;
	Slider feelingSlider;
	bool continueAdded;
};

#endif

//-------------------Screen 2---------------------------//
#ifndef ContinueMenu_H
#define ContinueMenu_H
class ContinueMenu: public Frame{
public:
	ContinueMenu();

	virtual void update();

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
	LogoMenu();

	virtual void update();

protected:
	Button clickAnywhere;
};

#endif
//-------------------------------------------------------//