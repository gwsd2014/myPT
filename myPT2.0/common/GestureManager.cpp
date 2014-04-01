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

void GestureManager::guessGesture( unsigned int index, float yMin, float zMax )
{
	bool inRange;
	if(index==0){
		inRange = (yMin<leftHandTrails.back().y() && leftHandTrails.back().z()<zMax);
	}else{
		inRange = (yMin<rightHandTrails.back().y() && rightHandTrails.back().z()<zMax);
	}
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
            currentX = leftHandTrails.back().x();
            currentY = leftHandTrails.back().y();
            distance = sqrt(powf(currentX-leftHandTrails.front().x(), 2.0f)
                          + powf(currentY-leftHandTrails.front().y(), 2.0f));
        }
        else  // right hand
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
       //     if ( currentY>0.9f && currentX<0.1f )  // Restart
       //     { score = 0; life = 100; }
        //    else if ( currentY>0.9f && currentX>0.9f )  // Exit
         //       glutLeaveMainLoop();
        }
    }
}

bool GestureManager::buttonPressed(int index, float X, float Y){
    if ( index ==0 && holdGestureCount[0]>20 )	//if hand is being held over a button, handle it
    {
		float curX = leftHandTrails.back().getx();
		float curY = leftHandTrails.back().gety();
		//checks that hold is on button space!
        if (( curY>(Y-.05) && curY<(Y=.05)) && ( curX>(X-.05) && curX<(X=.05))){
			return true;
		}
    }
	if ( index == 1 && holdGestureCount[1]>20 )	//if hand is being held over a button, handle it
    {
		float curX = rightHandTrails.back().getx();
		float curY = rightHandTrails.back().gety();
		//checks that hold is on button space!
        if (( curY>(Y-.05) && curY<(Y=.05)) && ( curX>(X-.05) && curX<(X=.05))){
			return true;
		}
    }
	return false;
}

float GestureManager::distance(int index, vertex3 vertex){
	float distance = 0.0;
	if(index == 0){
		distance = sqrt(powf(vertex.x()-leftHandTrails.back().x(), 2.0f)
					+ powf(vertex.y()-leftHandTrails.back().y(), 2.0f));
	}else{
		distance = sqrt(powf(vertex.x()-rightHandTrails.back().x(), 2.0f)
					+ powf(vertex.y()-rightHandTrails.back().y(), 2.0f));
	}
	return distance;
}

VertexData GestureManager::convertToMesh(int index){
	if(index ==0){
		VertexData leftHandData = {&(leftHandTrails[0].x()), NULL, &(trailColors[0][0]), NULL };
		return leftHandData;
	}else{
		VertexData rightHandData = {&(rightHandTrails[0].x()), NULL, &(trailColors[0][0]), NULL };
		return rightHandData;
	}
}

int GestureManager::getTrailsSize(int index){
	if(index ==0)
		return leftHandTrails.size();
	else
		return rightHandTrails.size();
}

vertex3 GestureManager::getCurrentHandData(int index){
	if(index ==0)
		return leftHandTrails.back();
	else
		return rightHandTrails.back();
}