#include "DotSpot.h"

DotSpot::DotSpot(): Game(){
		//create donuts
		donuts.push_back(DotObject(0, 0.1f, 0.25f, 0.2f));
		donuts.push_back(DotObject(1, 0.1f,  0.45f, 0.2f));
		donuts.push_back(DotObject(2, 0.1f,  0.66f, 0.2f));

		shuffleDots();

		guide = DotObject(6, (GLfloat)0.04f, (GLfloat)0.0f, (GLfloat)0.0f);
		checkMark = DotObject(3, (GLfloat)0.4, (GLfloat)0.3f, (GLfloat)0.3f);
		backgroundIDIndex = 0;

		restart = Button(0.05f, 0.95f, 0.1f, 25);
		exit = Button(0.95f, 0.95f, 0.1f, 25);
		interactions.push_back(&restart);
		interactions.push_back(&exit);
		framesBetweenSquats = 200;
}

DotSpot::DotSpot(int difficulty, Frame* goBack) : Game(difficulty, goBack){
		//create donuts
		donuts.push_back(DotObject(0, 0.1f, 0.25f, 0.2f));
		donuts.push_back(DotObject(1, 0.1f,  0.45f, 0.2f));
		donuts.push_back(DotObject(2, 0.1f,  0.66f, 0.2f));

		shuffleDots();

		guide = DotObject(6, (GLfloat)0.04f, (GLfloat)0.0f, (GLfloat)0.0f);
		checkMark = DotObject(3, (GLfloat)0.4, (GLfloat)0.3f, (GLfloat)0.3f);
		backgroundIDIndex = 0;

		restart = Button(0.05f, 0.95f, 0.1f, 25);
		exit = Button(0.95f, 0.95f, 0.1f, 25);
		interactions.push_back(&restart);
		interactions.push_back(&exit);
		//SET DIFFICULTY PARAMETERS!
		//like this one!
		framesBetweenSquats = 200;
}

void DotSpot::shuffleDots(){
		//CHANGESTHE COLORS OF THE DONUTS!
		//update which one is green/the apple
		hotDonutTouched = false;
		hotDonut = rand() % 3;
		if(rand() % 2 == 0) 
			leftHand = true;
		else 
			leftHand = false;

		if(rand()% 2 == 0)
			leftLeg = true;
		else 
			leftLeg = false;
		//printf("Hot donut is %d\n", hotDonut);
		switch (hotDonut)
		{
			case 0:
				donuts.at(0).objectIDIndex = 0;
				if(rand() %2 == 0){
					donuts.at(1).objectIDIndex = 1;
					donuts.at(2).objectIDIndex = 2;
				}else{
					donuts.at(1).objectIDIndex = 2;
					donuts.at(2).objectIDIndex = 1;
				}
			break;
			case 1:
				donuts.at(1).objectIDIndex = 0;
				if(rand() %2 == 0){
					donuts.at(0).objectIDIndex = 1;
					donuts.at(2).objectIDIndex = 2;
				}else{
					donuts.at(0).objectIDIndex = 2;
					donuts.at(2).objectIDIndex = 1;
				}
			break;
			case 2:
				donuts.at(2).objectIDIndex = 0;
				if(rand() %2 ==0 ){
					donuts.at(0).objectIDIndex = 1;
					donuts.at(1).objectIDIndex = 2;
				}else{
					donuts.at(0).objectIDIndex = 2;
					donuts.at(1).objectIDIndex = 1;
				}
			break;
		}
		shuffled = true;
	}

void DotSpot::timer(int value){
		//This determines speed
		//Which in turn determines difficulty
	if(value%framesBetweenSquats == 0){
			shuffleDots();
		}
}

void DotSpot::render(const unsigned int* objectTexIDs){
	// Blend with dot objects
	for ( unsigned int i=0; i<donuts.size(); ++i )
		donuts[i].render(objectTexIDs);


	//DRAW GUIDE OVER CURRENT HAND
	guide.render(objectTexIDs);

	if(!shuffled && hotDonutTouched){
		//render a check mark
		checkMark.render(objectTexIDs);
	}

	//makes call to parent render
	//this renders all interactions if there are any that require rendering
	__super::render(objectTexIDs);

	//render Text
	 std::stringstream ss;
	 ss << "Score: " << score << "  Life: " << (life<0 ? 0 : life);
	    
    glRasterPos2f( 0.01f, 0.01f );
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );		//WHITE TEXT
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)ss.str().c_str() );
}

bool DotSpot::correctForm(){
	vertex3 hipData = GestureManager::Inst()->getCurrentData(2);
	vertex3 spineData = GestureManager::Inst()->getCurrentData(3);
	//if shoulders are over hips
	if(spineData.gety() < hipData.gety()){
		return false;
	}
}

void DotSpot::update(){

	//makes call to parent update which updates interaction info
	__super::update();

	//handle buttons!
	if(restart.pressed){
		score = 0; life = 100; 
	}
	if(exit.pressed)
		 glutLeaveMainLoop();
	if(score > 30){
		changeView(goBack);
	}

	if(leftHand){
		guide.position = GestureManager::Inst()->getCurrentData(0);
	}else{
		guide.position = GestureManager::Inst()->getCurrentData(1);
	}

	// Update fruit objects and intersections with the hands	
	if(!hotDonutTouched){
		//computes distance between fruit and left hand blade
		if(leftHand){
			//handling gestures?
			float distance = GestureManager::Inst()->distance(0, donuts.at(hotDonut).position);
			if ( distance<donuts.at(hotDonut).size ) hotDonutTouched = true;
		}
            
		//computes distance between fruit and right hand blade
		if(!leftHand){
			float distance = GestureManager::Inst()->distance(1, donuts.at(hotDonut).position);
			if ( distance<donuts.at(hotDonut).size ) hotDonutTouched = true;
		}
	}
	if (hotDonutTouched && shuffled)
	{
		//Increase score!
		score+=10;
		shuffled = false;
		//load a check mark, until shuffled!
	}    

}