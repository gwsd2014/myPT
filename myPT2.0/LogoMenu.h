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