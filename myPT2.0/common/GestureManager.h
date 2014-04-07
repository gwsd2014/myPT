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
		float distance(int index, vertex3 vertex);
		VertexData convertToMesh(int index);
		int getTrailsSize(int index);
		bool buttonHover(int index, float X, float Y, float threshold);
		int buttonPressed(int index, float X, float Y, int numFramesHeld, float threshold);
		vertex3 getCurrentHandData(int index);
		void resetData();

	protected:
		static GestureManager* m_inst;
		std::vector<vertex3> leftHandTrails;
		std::vector<vertex3> rightHandTrails;

		unsigned int holdGestureCount[2];
		unsigned int swipeGestureCount[2];
		GLfloat trailColors[20][4];
};

#endif