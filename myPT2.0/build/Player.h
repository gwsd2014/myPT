
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <GL/freeglut.h>
#include "InteractionClient.h"
#include "vertex3.h"
#include <vector>
#include "common/TextureManager.h"
#include "common/GLUtilities.h"

class Player{
	public:
		unsigned int holdGestureCount[2];
		unsigned int swipeGestureCount[2];
		GLfloat trailColors[20][4];

		//Hold 20 frames of data
		std::vector<vertex3> leftHandTrails;
		std::vector<vertex3> rightHandTrails;
		InteractionClient interactionClient;
		NUI_USER_INFO curUserInfo;		//holds important information about hands

		TextureObject* playerDepthTexture;

	void init();

	Player();

	float leftDistance(float posX, float posY);

	float rightDistance(float posX, float posY);

	void destroy();

	void render();

	void renderHandTrails();

	void guessGesture( unsigned int index, bool inRange );

	bool heldButton(float percentX, float percentY);
	
};

#endif	//PLAYER_H_