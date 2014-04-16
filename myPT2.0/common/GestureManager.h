#ifndef GestureManager_H
#define GestureManager_H

#include <vector>
#include "vertex3.h"
#include "GLUtilities.h"

enum EGesture{held, swiped, moving};

class GestureManager{
	public:
		static GestureManager* Inst();
		GestureManager();


		void guessGesture( unsigned int index,float zMax );
		void addLeftHandData(vertex3 vertex);
		void addRightHandData(vertex3 vertex);
		void addData(int index, vertex3 vertex);
		bool isStill(unsigned int index, int numFramesHeld);
		float distance(int index, vertex3 vertex);
		VertexData convertToMesh(int index);
		int getTrailsSize(int index);
		bool buttonHover(int index, float X, float Y, float threshold);
		int buttonPressed(int index, float X, float Y, int numFramesHeld, float threshold);
		vertex3 getCurrentData(int index);
		void resetData();

	protected:
		static GestureManager* m_inst;
		std::vector<vertex3> leftHandTrails;
		std::vector<vertex3> rightHandTrails;

		std::vector<vertex3> leftFootTrails;
		std::vector<vertex3> rightFootTrails;

		std::vector<vertex3> spineTrails;
		std::vector<vertex3> hipTrails;

		unsigned int holdGestureCount[6];
		unsigned int swipeGestureCount[6];
		GLfloat trailColors[20][4];
};

#endif