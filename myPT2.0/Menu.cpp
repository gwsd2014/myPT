#include "Menu.h"

MainMenu::MainMenu(): Frame(){
		button1PressedOnce = false;
		button2PressedOnce = false;
		dotSpotButton = ButtonWithTexture(0.4f, 0.4f, 0.35, 10);
		mazeRaceButton = ButtonWithTexture(0.4, 0.2f, 0.35, 9);
		interactions.push_back(&dotSpotButton);
		interactions.push_back(&mazeRaceButton);
		backgroundIDIndex = 8;
		phase = DotObject( 17, .28, 0.48, 0.7);
		difficulty = DotObject(12, .14, 0.6, 0.34);
		difficulty2 = DotObject(11, .14, 0.6, 0.14);
	}

	void MainMenu::update(){

		__super::update();

		if(dotSpotButton.pressed && !button1PressedOnce){
			dotSpotButton.prettyPicture.objectIDIndex = 24;
			button1PressedOnce = true;
			changeView(new DotSpot(3, (Frame*)this));
		}
		if(mazeRaceButton.pressed && !button2PressedOnce){
			button2PressedOnce = true;
			mazeRaceButton.prettyPicture.objectIDIndex = 23;
			changeView(new MazeRaceGame());
		}

		if(dotSpotButton.pressed && button1PressedOnce && button2PressedOnce && mazeRaceButton.pressed){
			changeView(new LogoMenu());
		}
	}

	void MainMenu::render(const unsigned int* objectTexIDs){
		__super::render(objectTexIDs);
		phase.render(objectTexIDs);
		difficulty.render(objectTexIDs);
		difficulty2.render(objectTexIDs);
	}


	TimeSinceMenu::TimeSinceMenu(): Frame(){
		backgroundIDIndex = 7;
		continueButton = ButtonWithTexture(0.5, 0.3, 0.2, 8);
		timeSlider = Slider(true, 0.15, .85, .57);
		interactions.push_back(&timeSlider);
		continueAdded = false;
	}

	void TimeSinceMenu::update(){
		__super::update();

		if(timeSlider.slid && !continueAdded){		
			//SAVE PERCENTAGE!
			//RUN ALGORITHM TO DETERMINE SYSTEM!
			continueAdded = true;
			interactions.push_back(&continueButton);
		}
		if(continueAdded && continueButton.pressed){
			changeView(new MainMenu());
		}
	}

	MeniscusMenu::MeniscusMenu(): Frame(){
		backgroundIDIndex = 6;
		yesButton = Button(0.7, 0.5, 0.1);
		noButton = Button(0.3, 0.5, 0.1);
		interactions.push_back(&yesButton);
		interactions.push_back(&noButton);
	}

	void MeniscusMenu::update(){
		__super::update();

		if(yesButton.pressed){		
			//SAVE ANSWER!
			changeView(new TimeSinceMenu());
		}else if(noButton.pressed){
			changeView(new TimeSinceMenu());
		}
	}


	BehindKneeMenu::BehindKneeMenu(): Frame(){
		backgroundIDIndex = 5;
		yesButton = Button(0.7f, 0.5f, 0.2f);
		noButton = Button(0.3f, 0.5f, 0.2f);
		interactions.push_back(&yesButton);
		interactions.push_back(&noButton);

	}

	void BehindKneeMenu::update(){
		__super::update();

		if(yesButton.pressed){		
			//SAVE ANSWER!
			changeView(new MeniscusMenu());
		}else if(noButton.pressed){
			changeView(new MeniscusMenu());
		}
	}

	ScarMenu::ScarMenu(): Frame(){
		backgroundIDIndex = 4;
		yesButton = Button(0.7f, 0.5f, 0.2f);
		noButton = Button(0.3f, 0.5f, 0.2f);
		interactions.push_back(&yesButton);
		interactions.push_back(&noButton);

	}

	void ScarMenu::update(){
		__super::update();

		if(yesButton.pressed){		
			//SAVE ANSWER!
			changeView(new BehindKneeMenu());
		}else if(noButton.pressed){
			changeView(new BehindKneeMenu());
		}
	}

	FeelingMenu::FeelingMenu(): Frame(){
		backgroundIDIndex = 3;
		continueButton = ButtonWithTexture(0.5f, 0.5f, 0.2, 8);
		feelingSlider = Slider(true, 0.15f, .85f, .65f);
		interactions.push_back(&feelingSlider);
		continueAdded = false;

	}

	void FeelingMenu::update(){
		__super::update();

		if(feelingSlider.slideHandle.pressed && !continueAdded){		
			continueAdded = true;
			interactions.push_back(&continueButton);
		}

		if(continueAdded && continueButton.pressed)
		{
			//SAVE PERCENTAGE!
			changeView(new ScarMenu());
		}
	}

	ContinueMenu::ContinueMenu(): Frame(){
		backgroundIDIndex = 2;
		continueButton = Button(0.5f, 0.8f, 0.2f);
		interactions.push_back(&continueButton);
	}

	void ContinueMenu::update(){
		__super::update();

		if(continueButton.pressed){		
			changeView(new FeelingMenu());
		}
	}

	LogoMenu::LogoMenu(): Frame(){
		backgroundIDIndex = 1;
		clickAnywhere = Button(0.5f, 0.5f, 1.0f, 40);
		interactions.push_back(&clickAnywhere);
	}

	void LogoMenu::update(){
		__super::update();

		if(clickAnywhere.pressed){		
			ContinueMenu* contMenu = new ContinueMenu();
			changeView(contMenu);
		}
	}