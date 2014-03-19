#ifndef _KINECT_H_
#define _KINECT_H_

#include <iostream>
#include "Player.h"


class Kinect{
private:
	//Event Handles
	HANDLE nextDepthFrameEvent;
	HANDLE nextSkeletonEvent;

	//Stream Handles
	HANDLE colorStreamHandle;
	HANDLE depthStreamHandle;
public:
	NUI_TRANSFORM_SMOOTH_PARAMETERS smoothParams;
	INuiSensor* context;
	Player* player;
	
	bool initializeKinect()
	{
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
    
		hr = context->NuiImageStreamOpen( NUI_IMAGE_TYPE_COLOR, NUI_IMAGE_RESOLUTION_640x480, 0, 2, NULL, &colorStreamHandle );
		if ( FAILED(hr) )
		{
			std::cout << "Unable to create color stream: " << std::hex << (long)hr << std::dec << std::endl;
			return false;
		}

		nextDepthFrameEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		hr = context->NuiImageStreamOpen( NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, NUI_IMAGE_RESOLUTION_640x480,
			0, 2, NULL, &depthStreamHandle );
		if ( FAILED(hr) )
		{
			std::cout << "Unable to create depth stream: " << std::hex << (long)hr << std::dec << std::endl;
			return false;
		}

		nextSkeletonEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
		hr = context->NuiSkeletonTrackingEnable( NULL, 0 );
		if ( FAILED(hr) )
		{
			std::cout << "Unable to start tracking skeleton." << std::endl;
			return false;
		}
		smoothParams.fCorrection = 0.5f;
		smoothParams.fJitterRadius = 1.0f;
		smoothParams.fMaxDeviationRadius = 0.5f;
		smoothParams.fPrediction = 0.4f;
		smoothParams.fSmoothing = 0.2f;
		return true;
	}

	Kinect(){
		//default constructor
		//this is not safe, don't use it!
		context = NULL;
		colorStreamHandle = NULL;
		depthStreamHandle = NULL;
		if(!initializeKinect())
			printf("Kinect failed to initialize\n");
		//this->player = playerPtr;
		this->player = new Player();
	}

	Kinect(Player* playerPtr){
		context = NULL;
		colorStreamHandle = NULL;
		depthStreamHandle = NULL;
		this->player = playerPtr;
		if(!initializeKinect())
			printf("Kinect failed to initialize\n");
		//this->player = playerPtr;
		//this is dangerous!!
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
			vertex.setx((GLfloat)coordInDepth.x / 640.0f);
			vertex.sety(1.0f - (GLfloat)coordInDepth.y / 480.0f);
			vertex.setz((GLfloat)NuiDepthPixelToDepth(depth) * 0.00025f);
        
			if ( i==NUI_SKELETON_POSITION_SPINE )
			{
				yMin = vertex.gety();
				zMax = vertex.getz();
			}
			else if ( i==NUI_SKELETON_POSITION_HAND_LEFT )
			{
				player->leftHandTrails.push_back( vertex );
				if ( player->leftHandTrails.size()>20 ) player->leftHandTrails.erase( player->leftHandTrails.begin() );
			}
			else if ( i==NUI_SKELETON_POSITION_HAND_RIGHT )
			{
				player->rightHandTrails.push_back( vertex );
				if ( player->rightHandTrails.size()>20 ) player->rightHandTrails.erase( player->rightHandTrails.begin() );
			}
		}		
		
		//put this somewhere else?
		player->guessGesture( 0, (yMin<player->leftHandTrails.back().gety() && player->leftHandTrails.back().getz()<zMax) );
		player->guessGesture( 1, (yMin<player->rightHandTrails.back().gety() && player->rightHandTrails.back().getz()<zMax) );
	}

	void updateImageFrame( NUI_IMAGE_FRAME& imageFrame)
	{
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
					unsigned char* ptr = player->playerDepthTexture->bits + 2 * (i * 640 + j);
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
        
			TextureObject* tobj = player->playerDepthTexture;
			glBindTexture( GL_TEXTURE_2D, tobj->id );
			glTexImage2D( GL_TEXTURE_2D, 0, tobj->internalFormat, tobj->width, tobj->height,
						  0, tobj->imageFormat, GL_UNSIGNED_BYTE, tobj->bits );
		}
		nuiTexture->UnlockRect( 0 );
	}


	void ProcessDepth(){
		//Update Kinect Skeleton Depth overlay
		NUI_IMAGE_FRAME depthFrame;
		HRESULT hr = context->NuiImageStreamGetNextFrame( depthStreamHandle, 0, &depthFrame );
		if(SUCCEEDED(hr)){
			updateImageFrame( depthFrame);
			context->NuiImageStreamReleaseFrame( depthStreamHandle, &depthFrame );
		}
	}

	void ProcessSkeleton(){
		//Process Skeleton
		NUI_SKELETON_FRAME skeletonFrame = {0};
		HRESULT hr = context->NuiSkeletonGetNextFrame( 0, &skeletonFrame );
		if ( SUCCEEDED(hr) )
		{
			context->NuiTransformSmooth( &skeletonFrame, &smoothParams );
			for ( int n=0; n<NUI_SKELETON_COUNT; ++n )
			{
				NUI_SKELETON_DATA& data = skeletonFrame.SkeletonData[n];
				if ( data.eTrackingState==NUI_SKELETON_TRACKED )
				{
					updateSkeletonData( data );

					//get accelerometer data
					//Vector4 v = {0};
					//context->NuiAccelerometerGetCurrentReading(&v);

					break;
				}	
			}		
		}
	}

	void update(){
		if (NULL == context)
		{
			return;
		}
		//if (WAIT_OBJECT_0 == WaitForSingleObject(nextDepthFrameEvent, 0))
		//{
			ProcessDepth();
		//}

		//if ( WAIT_OBJECT_0 == WaitForSingleObject(nextSkeletonEvent, 0) )
		//{
			ProcessSkeleton();
		//}

		//glutPostRedisplay();
	}

	bool destroy(){
		player->destroy();
		if ( context )
		{
			context->NuiShutdown();
			return true;
		}
		return false;
	}
};

#endif