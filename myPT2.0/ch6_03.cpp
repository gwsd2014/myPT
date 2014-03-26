#include <GL/freeglut.h>
#include <MSHTML.h>
#include <NuiApi.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "common/TextureManager.h"
#include "common/GLUtilities.h"
#include "DotObject.h"
#include "vertex3.h"
#include "GestureManager.h"

INuiSensor* context = NULL;
HANDLE colorStreamHandle = NULL;
HANDLE depthStreamHandle = NULL;
TextureObject* playerDepthTexture = NULL;

NUI_TRANSFORM_SMOOTH_PARAMETERS smoothParams;

const unsigned int backgroundTexID = 1;
//array containing texture id's for fruit images
//watermelon, apple, mango and bomb
const unsigned int objectTexIDs[7] = {2, 3, 4, 5, 7, 8, 9};
const unsigned int gameOverTexID = 6;
int score = 0, life = 100;

// frame index
int g_frameIndex = 0;

//game globals
bool hotDonutTouched;
bool shuffled;
bool leftHand; //true for left, false if right;

int hotDonut;		//Location of the green donut

float randomValue( float min, float max )
{
    return (min + (float)rand()/(RAND_MAX+1.0f) * (max - min));
}

std::vector<DotObject> donuts;
DotObject guide;	//originally set to blue
DotObject checkMark;
bool initializeKinect()
{
	NuiCameraElevationSetAngle(0);
	NuiCameraElevationSetAngle(32);
	NuiCameraElevationSetAngle(0);

    int numKinects = 0;
    HRESULT hr = NuiGetSensorCount( &numKinects );
    if ( FAILED(hr) || numKinects<=0 )
    {
        std::cout << "No Kinect device found." << std::endl;
        return false;
    }
    
    hr = NuiCreateSensorByIndex( 0, &context );
    if ( FAILED(hr) )
    {
        std::cout << "Failed to connect to Kinect device." << std::endl;
        return false;
    }
    
    DWORD nuiFlags = NUI_INITIALIZE_FLAG_USES_SKELETON | NUI_INITIALIZE_FLAG_USES_COLOR |
                     NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX;
    hr = context->NuiInitialize( nuiFlags );
    if ( FAILED(hr) )
    {
        std::cout << "Failed to intialize Kinect: " << std::hex << (long)hr << std::dec << std::endl;
        return false;
    }
    
	//NuiCameraElevationSetAngle(4);

    hr = context->NuiImageStreamOpen( NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 0, 2, NULL, &colorStreamHandle );
    if ( FAILED(hr) )
    {
        std::cout << "Unable to create color stream: " << std::hex << (long)hr << std::dec << std::endl;
        return false;
    }
    
    hr = context->NuiImageStreamOpen( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, NUI_IMAGE_RESOLUTION_640x480,
                                      0, 2, NULL, &depthStreamHandle );
    if ( FAILED(hr) )
    {
        std::cout << "Unable to create depth stream: " << std::hex << (long)hr << std::dec << std::endl;
        return false;
    }
    
    hr = context->NuiSkeletonTrackingEnable( NULL, 0 );
    if ( FAILED(hr) )
    {
        std::cout << "Unable to start tracking skeleton." << std::endl;
        return false;
    }
    return true;
}

bool destroyKinect()
{
    if ( context )
    {
        context->NuiShutdown();
        return true;
    }
    return false;
}

void updateImageFrame( NUI_IMAGE_FRAME& imageFrame )
{
	//----------------------------------------------------//
	//creates skeleton alpha channel!!
    INuiFrameTexture* nuiTexture = imageFrame.pFrameTexture;
    NUI_LOCKED_RECT lockedRect;
    nuiTexture->LockRect( 0, &lockedRect, NULL, 0 );
    if ( lockedRect.Pitch!=NULL )
    {
        const BYTE* buffer = (const BYTE*)lockedRect.pBits;
        for ( int i=0; i<480; ++i )
        {
            const BYTE* line = buffer + i * lockedRect.Pitch;
            const USHORT* bufferWord = (const USHORT*)line;
            for ( int j=0; j<640; ++j )
            {
                unsigned char* ptr = playerDepthTexture->bits + 2 * (i * 640 + j);
                if ( NuiDepthPixelToPlayerIndex(bufferWord[j])>0 )
                {
                    *(ptr + 0) = 200;
                    *(ptr + 1) = 80;
                }
                else
                {
                    *(ptr + 0) = 0;
                    *(ptr + 1) = 0;
                }
            }
        }
        
        TextureObject* tobj = playerDepthTexture;
        glBindTexture( GL_TEXTURE_2D, tobj->id );
        glTexImage2D( GL_TEXTURE_2D, 0, tobj->internalFormat, tobj->width, tobj->height,
                      0, tobj->imageFormat, GL_UNSIGNED_BYTE, tobj->bits );
    }
    nuiTexture->UnlockRect( 0 );
	//-------------------------------------------------------------------------------//
}

void shuffleDots(){
		//CHANGESTHE COLORS OF THE DONUTS!
		//update which one is green!
		hotDonutTouched = false;
		hotDonut = rand() % 3;
		if(rand() % 2 == 0) 
			leftHand = true;
		else 
			leftHand = false;
		printf("Hot donut is %d\n", hotDonut);
		switch (hotDonut)
		{
			case 0:
				donuts.at(0).dcolor = green;
				donuts.at(1).dcolor = red;
				donuts.at(2).dcolor = blue;
				donuts.at(0).objectID = 0;
				if(rand() %2 == 0){
					donuts.at(1).objectID = 1;
					donuts.at(2).objectID = 2;
				}else{
					donuts.at(1).objectID = 2;
					donuts.at(2).objectID = 1;
				}
			break;
			case 1:
				donuts.at(1).dcolor = green;
				donuts.at(0).dcolor = red;
				donuts.at(2).dcolor = blue;
				donuts.at(1).objectID = 0;
				if(rand() %2 == 0){
					donuts.at(0).objectID = 1;
					donuts.at(2).objectID = 2;
				}else{
					donuts.at(0).objectID = 2;
					donuts.at(2).objectID = 1;
				}
			break;
			case 2:
				//Set colors
				donuts.at(0).dcolor = blue;
				donuts.at(1).dcolor = red;
				donuts.at(2).dcolor = green;
				donuts.at(2).objectID = 0;
				if(rand() %2 ==0 ){
					donuts.at(0).objectID = 1;
					donuts.at(1).objectID = 2;
				}else{
					donuts.at(0).objectID = 2;
					donuts.at(1).objectID = 1;
				}
			break;
		}
		shuffled = true;
}

void updateSkeletonData( NUI_SKELETON_DATA& data )
{
    POINT coordInDepth;
    USHORT depth = 0;
    GLfloat yMin = 0.0f, zMax = 0.0f;
    for ( int i=0; i<NUI_SKELETON_POSITION_COUNT; ++i )
    {
        NuiTransformSkeletonToDepthImage(
            data.SkeletonPositions[i], &coordInDepth.x, &coordInDepth.y,
            &depth, NUI_IMAGE_RESOLUTION_640x480 );
        
        vertex3 vertex;
        vertex.x() = (GLfloat)coordInDepth.x / 640.0f;
        vertex.y() = 1.0f - (GLfloat)coordInDepth.y / 480.0f;
        vertex.z() = (GLfloat)NuiDepthPixelToDepth(depth) * 0.00025f;
        
        if ( i==NUI_SKELETON_POSITION_SPINE )
        {
            yMin = vertex.y();
            zMax = vertex.z();
        }
        else if ( i==NUI_SKELETON_POSITION_HAND_LEFT )
        {
			//pass data to gesture manager
			GestureManager::Inst()->addLeftHandData(vertex);
			if(leftHand) guide.position = vertex;
        }
        else if ( i==NUI_SKELETON_POSITION_HAND_RIGHT )
        {
			GestureManager::Inst()->addRightHandData(vertex);
			if(!leftHand) guide.position = vertex;
        }

		else if(i==NUI_SKELETON_POSITION_FOOT_LEFT || i== NUI_SKELETON_POSITION_FOOT_RIGHT){
			//add checks to make sure the user is in the correct spot
		}
    }
    //must be capable of handling buttons in some way...
	GestureManager::Inst()->guessGesture(0, yMin, zMax);
	GestureManager::Inst()->guessGesture(1, yMin, zMax);
}

void update()
{

	//Update Kinect Skeleton Depth overlay
    NUI_IMAGE_FRAME depthFrame;
    HRESULT hr = context->NuiImageStreamGetNextFrame( depthStreamHandle, 0, &depthFrame );
    if ( SUCCEEDED(hr) )
    {
        updateImageFrame( depthFrame );
        context->NuiImageStreamReleaseFrame( depthStreamHandle, &depthFrame );
    }
    
    NUI_SKELETON_FRAME skeletonFrame = {0};
    hr = context->NuiSkeletonGetNextFrame( 0, &skeletonFrame );
    if ( SUCCEEDED(hr) )
    {
        context->NuiTransformSmooth( &skeletonFrame, &smoothParams );
        for ( int n=0; n<NUI_SKELETON_COUNT; ++n )
        {
            NUI_SKELETON_DATA& data = skeletonFrame.SkeletonData[n];
            if ( data.eTrackingState==NUI_SKELETON_TRACKED )
            {
                updateSkeletonData( data );
                break;
            }
        }
    }
    

	// Update fruit objects and intersections with the hands	
	if(!hotDonutTouched){
		//computes distance between fruit and left hand blade
		if(leftHand){

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
    glutPostRedisplay();
}

void render()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth(1.0f);
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glEnable( GL_TEXTURE_2D );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    // Draw background quad
    GLfloat vertices[][3] = {
        { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }
    };
    GLfloat texcoords[][2] = {
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}
    };
    VertexData meshData = { &(vertices[0][0]), NULL, NULL, &(texcoords[0][0]) };
    
	//Replace background with game over texture
    if ( life<=0 ){
		TextureManager::Inst()->BindTexture( gameOverTexID );
	}
    else{ 
		//printf("Binding background texture");
		TextureManager::Inst()->BindTexture( backgroundTexID );	//or keep it the same
	}
    drawSimpleMesh( WITH_POSITION|WITH_TEXCOORD, 4, meshData, GL_QUADS );
    
    // Blend with depth quad
	glEnable( GL_BLEND );
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);	
	glDepthRange(0.0f, 1.0f);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glTranslatef( 0.0f, 0.0f, 0.1f );
    
    glBindTexture( GL_TEXTURE_2D, playerDepthTexture->id );
    drawSimpleMesh( WITH_POSITION|WITH_TEXCOORD, 4, meshData, GL_QUADS );
    
    // Blend with dot objects
    for ( unsigned int i=0; i<donuts.size(); ++i )
		donuts[i].render(objectTexIDs);


	//DRAW GUIDE OVER CURRENT HAND
	guide.render(objectTexIDs);

	if(!shuffled && hotDonutTouched){
		//render a check mark
		checkMark.render(objectTexIDs);
	}
    
    // Blend with hand trails
    glDisable( GL_TEXTURE_2D );
    glLineWidth( 50.0f );
    
	VertexData leftHandData = GestureManager::Inst()->convertToMesh(0);
	drawSimpleMesh( WITH_POSITION|WITH_COLOR, GestureManager::Inst()->getTrailsSize(0), leftHandData, GL_LINE_STRIP );
    
	VertexData rightHandData = GestureManager::Inst()->convertToMesh(1);
	drawSimpleMesh( WITH_POSITION|WITH_COLOR, GestureManager::Inst()->getTrailsSize(1), rightHandData, GL_LINE_STRIP );
    
    glDisable( GL_BLEND );
	
    // Draw HUD text
	LONG temp;
	NuiCameraElevationGetAngle(&temp);
    std::stringstream ss;
    ss << "Score: " << score << "  Life: " << (life<0 ? 0 : life);
	ss << "Elevation Angle: " << temp;
    
    glRasterPos2f( 0.01f, 0.01f );
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );		//WHITE TEXT
    glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)ss.str().c_str() );
    
    glutSwapBuffers();
}

void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
}

void keyEvents( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: case 'Q': case 'q':
        glutLeaveMainLoop();
        return;
    }
    glutPostRedisplay();
}

void timer( int value ) {	
	// increase frame index
	g_frameIndex++;

	//This determines speed
	//Which in turn determines difficulty
	if(g_frameIndex%200 == 0){
		shuffleDots();
	}
	
	// render
	glutPostRedisplay();

	// reset timer
	// 16 ms per frame ( about 60 frames per second )
	glutTimerFunc( 16, timer, 0 );
}

bool initTextures(){
	//Create background texture
    if ( TextureManager::Inst()->LoadTexture("DotSpotBkg-01.jpg", backgroundTexID, GL_BGR_EXT) )
    {
		printf("Background Texture opened succesfullyl\n\n\n\n");
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    } else return false;
    
	//create fruit textures?
    for ( int i=0; i<4; ++i )
    {
        std::stringstream ss;
        ss << "FruitNinja" << i+2 << ".png";
        if ( TextureManager::Inst()->LoadTexture(ss.str().c_str(), objectTexIDs[i], GL_BGRA_EXT, 4) )
        {
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        } else return false;
    } 

	//create guide textures
	//RED
	if(TextureManager::Inst()->LoadTexture("RedCircle.png", objectTexIDs[4], GL_BGRA_EXT, 4)){
		 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	} else return false;

	if(TextureManager::Inst()->LoadTexture("GreenCircle.png", objectTexIDs[5], GL_BGRA_EXT, 4)){
		 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	} else return false;

	
	if(TextureManager::Inst()->LoadTexture("BlueCircle.png", objectTexIDs[6], GL_BGRA_EXT, 4)){
		 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	} else return false;

	//create game over texture 
    if ( TextureManager::Inst()->LoadTexture("FruitNinja6.jpg", gameOverTexID, GL_BGR_EXT) )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    } else return false;

	return true;
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE );
    glutCreateWindow( "Dot Spot Window" );
    glutFullScreen();
    
    glutIdleFunc( update );
    glutDisplayFunc( render );

    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyEvents );
	glutTimerFunc( 16, timer, 0 );

	if(initTextures()){
		printf("Texture failed to load");
	}
    
    if ( !initializeKinect() ) return 1;
    playerDepthTexture = createTexture(640, 480, GL_LUMINANCE_ALPHA, 2);
    
    smoothParams.fCorrection = 0.5f;
    smoothParams.fJitterRadius = 1.0f;
    smoothParams.fMaxDeviationRadius = 0.5f;
    smoothParams.fPrediction = 0.4f;
    smoothParams.fSmoothing = 0.2f;

	//create donuts
	donuts.push_back(DotObject(1, 0.1f, 0.25f, 0.2f));
	donuts.push_back(DotObject(2, 0.1f,  0.45f, 0.2f));
	donuts.push_back(DotObject(0, 0.1f,  0.66f, 0.2f));

	shuffleDots();

	guide= DotObject(6, 0.04f, 0.0f, 0.0f);
	checkMark = DotObject(3, 0.1, 0.45f, 0.5f);


	glutMainLoop();
    
    destroyTexture( playerDepthTexture );
    destroyKinect();
    return 0;
}
