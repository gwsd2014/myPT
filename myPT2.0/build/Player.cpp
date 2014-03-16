#include "Player.h"

//TextureObject* Player::playerDepthTexture = createTexture(640, 480, GL_LUMINANCE_ALPHA, 2);

void Player::init(){
	for ( int i=0; i<20; ++i )
	{
		trailColors[i][0] = 1.0f;
		trailColors[i][1] = 1.0f;
		trailColors[i][2] = 1.0f;
		trailColors[i][3] = (float)(i + 1) / 20.0f;
	}

	playerDepthTexture = createTexture(640, 480, GL_LUMINANCE_ALPHA, 2);

	vertex3 defaultPoint = vertex3(0.0f, 0.0f, 0.0f);  
	leftHandTrails.push_back( defaultPoint );
	rightHandTrails.push_back( defaultPoint );
	holdGestureCount[0] = 0; holdGestureCount[1] = 0;
	swipeGestureCount[0] = 0; swipeGestureCount[1] = 0;
}

Player::Player(){
	playerDepthTexture = NULL;
	interactionClient = InteractionClient();		//necessary?
	init();
}

void Player::destroy(){
	 destroyTexture( Player::playerDepthTexture );
}

void Player::render(){


	glEnable( GL_BLEND );
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LEQUAL);	
	//glDepthRange(0.0f, 1.0f);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glTranslatef( 0.0f, 0.0f, 0.1f );

	//Player::playerDepthTexture = createTexture(640, 480, GL_LUMINANCE_ALPHA, 2);

	glBindTexture( GL_TEXTURE_2D, playerDepthTexture->id );

}

void Player::renderHandTrails(){
	// Blend with hand trails
	glDisable( GL_TEXTURE_2D );
	glLineWidth( 50.0f );

	VertexData leftHandData = { &(leftHandTrails[0].x()), NULL, &(trailColors[0][0]), NULL };
	drawSimpleMesh( WITH_POSITION|WITH_COLOR, leftHandTrails.size(), leftHandData, GL_LINE_STRIP );

	VertexData rightHandData = { &(rightHandTrails[0].x()), NULL, &(trailColors[0][0]), NULL };
	drawSimpleMesh( WITH_POSITION|WITH_COLOR, rightHandTrails.size(), rightHandData, GL_LINE_STRIP );
}



float Player::leftDistance(float posX, float posY){
	float dist = sqrt(powf(posX-leftHandTrails.back().getx(), 2.0f)
                        + powf(posY-leftHandTrails.back().gety(), 2.0f));
	return dist;
}

float Player::rightDistance(float posX, float posY){
	float dist = sqrt(powf(posX-rightHandTrails.back().getx(), 2.0f)
                        + powf(posY-rightHandTrails.back().gety(), 2.0f));
	return dist;
}

//decides what happens
//@param index - 0 is for left hand, and 1 is for right hand
//@param inRange just checks that the hand is within the bounds of the sccreen
void Player::guessGesture( unsigned int index, bool inRange )
{
	//if the hand is off the screen, reset the counts
	if ( !inRange )
	{
		holdGestureCount[index] = 0;
		swipeGestureCount[index] = 0;
	}
	else
	{
		float distance = 0.0f, currentX = 0.0f, currentY = 0.0f;
		if ( index==0 )  // left hand
		{
			currentX = leftHandTrails.back().getx();
			currentY = leftHandTrails.back().gety();
			distance = sqrt(powf(currentX-leftHandTrails.front().getx(), 2.0f)
						  + powf(currentY-leftHandTrails.front().gety(), 2.0f));
		}
		else  // right hand
		{
			currentX = rightHandTrails.back().getx();
			currentY = rightHandTrails.back().gety();
			distance = sqrt(powf(currentX-rightHandTrails.front().getx(), 2.0f)
						  + powf(currentY-rightHandTrails.front().gety(), 2.0f));
		}
    
		if ( distance<0.02 )	// IF hand has not moved
		{
			holdGestureCount[index]++;
			swipeGestureCount[index] = 0;
		}
		else if ( distance>0.05 )	//If hand has moved quickly
		{
			holdGestureCount[index] = 0;
			swipeGestureCount[index]++;
		}
		else	//hand is moving, but not quickly
		{
			holdGestureCount[index] = 0;
			swipeGestureCount[index] = 0;
		}
    
		//should return position
		//or do what?
		/*
		if ( holdGestureCount[index]>30 )	//if hand is being held over a button, handle it
		{
			if ( currentY>0.9f && currentX<0.1f )  // Restart
			{ score = 0; life = 100; }
			else if ( currentY>0.9f && currentX>0.9f )  // Exit
				glutLeaveMainLoop();
		}
		*/
	}
}


//TODO make this code look less ugly
bool Player::heldButton(float percentX, float percentY){
	NUI_INTERACTION_INFO interaction;
	this->interactionClient.GetInteractionInfoAtLocation(curUserInfo.SkeletonTrackingId, curUserInfo.HandPointerInfos->HandType, percentX, percentY, &interaction);

	/*
	bool held = false;
	if(holdGestureCount[0]>30 || holdGestureCount[1]>30){
		held = true;
	}
	float currentX, currentY;
	for(unsigned int i=0; i<2; i++){
		if(i=0){
			currentX = leftHandTrails.back().getx();
			currentY = leftHandTrails.back().gety(); 
		}else{
			currentX = rightHandTrails.back().getx();
			currentY = rightHandTrails.back().gety();
		}
		//check X and Y within range of .1 percent
		if(held && (currentX > percentX-.05) && (currentX < percentX+.05)){
			if((currentY > percentY) && (currentY < percentY+.05)){
				return true;
			}
		}
		*/
	}
	return false;
}