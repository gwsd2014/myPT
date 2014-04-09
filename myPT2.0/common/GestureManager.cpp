#include "GestureManager.h"


GestureManager* GestureManager::m_inst(0);

GestureManager* GestureManager::Inst()
{
	if(!m_inst)
		m_inst = new GestureManager();

	return m_inst;

}

GestureManager::GestureManager()
{
	vertex3 defaultPoint = vertex3(0.0f, 0.0f, 0.0f);
	addLeftHandData(defaultPoint);
	addRightHandData(defaultPoint);


	for ( int i=0; i<20; ++i )
    {
        trailColors[i][0] = 1.0f;
        trailColors[i][1] = 1.0f;
        trailColors[i][2] = 1.0f;
        trailColors[i][3] = (float)(i + 1) / 20.0f;
    }
}

void GestureManager::addLeftHandData(vertex3 vertex){
	leftHandTrails.push_back(vertex);
	if ( leftHandTrails.size()>10 ) leftHandTrails.erase( leftHandTrails.begin() );
}

void GestureManager::addRightHandData(vertex3 vertex){
	rightHandTrails.push_back(vertex);
	if ( rightHandTrails.size()>10 ) rightHandTrails.erase( rightHandTrails.begin() );
}

void GestureManager::addData(int index, vertex3 vertex){
	switch(index){
		case 0:
			leftHandTrails.push_back(vertex);
			if ( leftHandTrails.size()>10 ) leftHandTrails.erase( leftHandTrails.begin() );
		break;
		case 1:
			rightHandTrails.push_back(vertex);
			if ( rightHandTrails.size()>10 ) rightHandTrails.erase( rightHandTrails.begin() );
		break;
		case 2:
			spineTrails.push_back(vertex);
			if ( spineTrails.size()>5 ) spineTrails.erase( spineTrails.begin() );
		break;
		case 3:
			hipTrails.push_back(vertex);
			if ( hipTrails.size()>5 ) hipTrails.erase( hipTrails.begin() );
		break;
		case 4:
			leftFootTrails.push_back(vertex);
			if ( leftFootTrails.size()>10 ) leftFootTrails.erase( leftFootTrails.begin() );
		break;
		case 5:
			rightFootTrails.push_back(vertex);
			if ( rightFootTrails.size()>10 ) rightFootTrails.erase( rightFootTrails.begin() );
		break;
	}
}

void GestureManager::guessGesture( unsigned int index, float zMax )
{
	bool inRange;
	if(index==0){
		inRange = (leftHandTrails.back().z()<zMax);
	}else if(index==1){
		inRange = (rightHandTrails.back().z()<zMax);
	}
    if ( !inRange )
    {
		if(index==1)
        holdGestureCount[index] = 0;
        swipeGestureCount[index] = 0;
    }
    else
    {
        float distance = 0.0f, currentX = 0.0f, currentY = 0.0f;
        if ( index==0 )  // left hand
        {
            currentX = leftHandTrails.back().x();
            currentY = leftHandTrails.back().y();
            distance = sqrt(powf(currentX-leftHandTrails.front().x(), 2.0f)
                          + powf(currentY-leftHandTrails.front().y(), 2.0f));
        }
        else if(index ==1) // right hand
        {
            currentX = rightHandTrails.back().getx();
            currentY = rightHandTrails.back().gety();
            distance = sqrt(powf(currentX-rightHandTrails.front().x(), 2.0f)
                          + powf(currentY-rightHandTrails.front().y(), 2.0f));
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
        
        if ( holdGestureCount[index]>20 )	//if hand is being held over a button, handle it
        {
			//deprecated!
			//check all Button interactions...
			//if ( currentY>0.9f && currentX<0.1f )  // Restart
			//{ score = 0; life = 100; }
			//else if ( currentY>0.9f && currentX>0.9f )  // Exit
			//glutLeaveMainLoop();
			//printf("Current X is %f and Current Y is %f\n", rightHandTrails.back().getx(), rightHandTrails.back().gety());
        }
    }
}

bool GestureManager::buttonHover(int index, float X, float Y, float threshold){
	float curX = leftHandTrails.back().getx();
	float curY = leftHandTrails.back().gety();
		//printf("-------CurX = %f and CurY = %f", curX, curY);
		//checks that hold is on button space!
    if (( curY>(Y-threshold) && curY<(Y+threshold)) && ( curX>(X-threshold) && curX<(X+threshold))){
			//printf("Button has been pressed with Left hand\n");
			return true;
	}
}

//returns 0 if nothing, returns 1 on hover, retruns 2 on pressed(held).
int GestureManager::buttonPressed(int index, float X, float Y, int numberFramesHeld, float threshold){
	 if (index==0 ){
		float curX = leftHandTrails.back().getx();
		float curY = leftHandTrails.back().gety();		
		
		//printf("-------CurX = %f and CurY = %f", curX, curY);
		//checks that hold is on button space!
		 if(curY>(Y-threshold) && curY<(Y+threshold) && ( curX>(X-threshold) && curX<(X+threshold))){
		
			 if (holdGestureCount[0]>numberFramesHeld ){	//if hand is being held over a button, handle it
				return 2;	
			 }
			return 1;
		}
		 return 0;
    }
	 if (index==1 ){
		float curX = rightHandTrails.back().getx();
		float curY = rightHandTrails.back().gety();		
		
		//printf("-------CurX = %f and CurY = %f", curX, curY);
		//checks that hold is on button space!
		 if(curY>(Y-threshold) && curY<(Y+threshold) && ( curX>(X-threshold) && curX<(X+threshold))){
			 if (holdGestureCount[1]>numberFramesHeld ){	//if hand is being held over a button, handle it
				return 2;	
			 }
			return 1;
		}
		 return 0;
    }
}

float GestureManager::distance(int index, vertex3 vertex){
	float distance = 0.0;
	if(index == 0){
		distance = sqrt(powf(vertex.x()-leftHandTrails.back().x(), 2.0f)
					+ powf(vertex.y()-leftHandTrails.back().y(), 2.0f));
	}else if(index ==1){
		distance = sqrt(powf(vertex.x()-rightHandTrails.back().x(), 2.0f)
					+ powf(vertex.y()-rightHandTrails.back().y(), 2.0f));
	}
	return distance;
}

VertexData GestureManager::convertToMesh(int index){
	if(index ==0){
		VertexData leftHandData = {&(leftHandTrails[0].x()), NULL, &(trailColors[0][0]), NULL };
		return leftHandData;
	}else if(index ==1){
		VertexData rightHandData = {&(rightHandTrails[0].x()), NULL, &(trailColors[0][0]), NULL };
		return rightHandData;
	}
}

int GestureManager::getTrailsSize(int index){
	if(index ==0)
		return leftHandTrails.size();
	else if(index==1)
		return rightHandTrails.size();
}

vertex3 GestureManager::getCurrentData(int index){
	if(index == 0)
		return leftHandTrails.back();
	else if(index ==1)
		return rightHandTrails.back();
	else if(index ==2)
		return spineTrails.back();
	else if(index ==3)
		return hipTrails.back();
	else if(index ==4)
		return leftFootTrails.back();
	else if(index == 5)
		return rightFootTrails.back();
}

void GestureManager::resetData(){
	for(int i=0; i<2; i++){
		holdGestureCount[i] = 0;
		swipeGestureCount[i] = 0;
	}
	leftHandTrails.clear();
	rightHandTrails.clear();

	vertex3 defaultPoint = vertex3(0.0f, 0.0f, 0.0f);
	addLeftHandData(defaultPoint);
	addRightHandData(defaultPoint);
}