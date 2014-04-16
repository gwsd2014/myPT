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
		difficulty = 1;
}

DotSpot::DotSpot(int difficulty, Frame* goBack) : Game(difficulty, goBack){
		//create donuts
		donuts.push_back(DotObject(0, 0.1f, 0.25f, 0.2f));
		donuts.push_back(DotObject(1, 0.1f,  0.45f, 0.2f));
		donuts.push_back(DotObject(2, 0.1f,  0.66f, 0.2f));
		score = 0;

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
		this->difficulty = difficulty;
		if(difficulty ==1 || difficulty == 3){
			framesBetweenSquats = 120;
		}else{
			framesBetweenSquats = 70;
		}
		if(difficulty == 1 || difficulty == 2){
			squatMistake = DotObject(25, .6, .25, .25);
			footMistake = DotObject(27, .6, .25, .25);
		}else{
			squatMistake = DotObject(25, .6, .25, .25);
			footMistake = DotObject(26, .6, .25, .25);
		}			
		leftLeg = true;
		legHint = DotObject(28, 0.25f, -0.05f, 0.4);
		leftFootPlacement = DotObject(30, 0.1, 0.35, 0.05);
		rightFootPlacement = DotObject(30, 0.1, 0.5, 0.05);
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
		mistake = 0;
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

	//Draw Leg Guides
	if(difficulty == 3 || difficulty == 4){
		legHint.render(objectTexIDs);
		if(leftLeg){
			leftFootPlacement.render(objectTexIDs);
		}else{
			rightFootPlacement.render(objectTexIDs);
		}
	}else{
		leftFootPlacement.render(objectTexIDs);
		rightFootPlacement.render(objectTexIDs);
	}

	//printf("Mistake# %d shuffled is %d\n", mistake, shuffled);
	if(mistake > 0){
		if(mistake == 1){
			squatMistake.render(objectTexIDs);
			printf("Render squat mistake!\n");
		}else if(mistake == 2){
			//printf("Render foot mistake!\n");
			footMistake.render(objectTexIDs);
		}
	}else if(!shuffled && hotDonutTouched){
		//render a check mark
		checkMark.render(objectTexIDs);
	}

	//makes call to parent render
	//this renders all interactions if there are any that require rendering
	__super::render(objectTexIDs);

    glDisable( GL_TEXTURE_2D );
	//render Text
	 std::stringstream ss;
	// ss << "Score: " << score << "  Life: " << (life<0 ? 0 : life);
	 ss << "Score: " << score; 
	    
    glRasterPos2f( 0.01f, 0.01f );
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );		//WHITE TEXT
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)ss.str().c_str() );
}

//second boolean is useless if singleLeg is false
bool DotSpot::feetOnTheGround(bool singleLeg, bool leftFoot){
	vertex3 leftLegData = GestureManager::Inst()->getCurrentData(4);
	vertex3 rightLegData = GestureManager::Inst()->getCurrentData(5);
	//Checks that both feet are on the ground in a safe position
	//printf("LEFT (%f, %f) vs RIGHT (%f, %f)\n", leftLegData.gety(), leftLegData.getz(), rightLegData.gety(), rightLegData.getz());
	bool bothOnGround = true;
	if((leftLegData.getz() > (rightLegData.getz() + 0.02)) || (leftLegData.getz() < (rightLegData.getz() - 0.02))){
		printf("leftLeg Z -- %f, rightLegZ -- %f\n", leftLegData.getz(), rightLegData.getz());
		bothOnGround = false;
	}
	if((leftLegData.gety() > (rightLegData.gety() + 0.02)) || (leftLegData.gety() < (rightLegData.gety() - 0.02))){		
		//printf("Both feet NOT on ground!");
		printf("leftLeg Y -- %f, rightLegY -- %f\n", leftLegData.gety(), rightLegData.gety());
		bothOnGround = false;
	}
	//FOR DIFFICULTY's 1 and 2
	//must be regular squat for safety!
	if(!singleLeg && !bothOnGround)
		return false;


	//FOR DIFFICULTYS 3 & 4
	if(singleLeg){
		if(bothOnGround){
			printf("Foot mistake is that the threshold is too low!\n");
			return false;
		}
		//checks that one Leg is steady!
		if(leftFoot && !GestureManager::Inst()->isStill(4, 10)){
			return false;
		}
		if(!leftFoot && !GestureManager::Inst()->isStill(5, 10)){
			return false;
		}
	}
	return true;
}

bool DotSpot::correctForm(){
	vertex3 hipData = GestureManager::Inst()->getCurrentData(3);
	vertex3 spineData = GestureManager::Inst()->getCurrentData(2);
	//if shoulders are over hips
	//printf("Shoulder %f hips %f\n\n", spineData.gety(), hipData.gety() );
	if(spineData.gety() < hipData.gety()+.15){
		//return false;
		//printf("spine %f vs. hips %f\n", spineData.gety(), hipData.gety());
		printf("Shoulder problem!");
		mistake = 1;
		return false;
	}
	//Now split up by difficulty
	//this is a phase 3 Exercise!
		//printf("Left Leg Data (%f, %f, %f) vs. right (%f, %f, %f)\n", 
	//	leftLegData.x(), leftLegData.y(), leftLegData.z(), rightLegData.x(), rightLegData.y(), rightLegData.z());
	if(difficulty == 1 || difficulty == 2){
		//checks that both feet are on the ground!
		if(!feetOnTheGround(false, false)){
			mistake = 2;
			//printf("Foot problem!");
			return false;
		}
	}
	if(difficulty == 3 || difficulty ==4){
		if(!feetOnTheGround(true, leftLeg)){
			mistake = 2;
			return false;
		}
	}
	return true;
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
	if(score > 150){
		leftLeg = false;
		legHint.objectIDIndex = 29;
	}
	if(score > 300){
		changeView(goBack);
	}

	if(leftHand){
		guide.position = GestureManager::Inst()->getCurrentData(0);
	}else{
		guide.position = GestureManager::Inst()->getCurrentData(1);
	}

	// Update fruit objects and intersections with the hands	
	if(!hotDonutTouched && correctForm()){
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