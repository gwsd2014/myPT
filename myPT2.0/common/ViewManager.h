#ifndef ViewManager_H
#define ViewManager_H

#include "../Frame.h"
#include "GLUtilities.h"
#include "../Menu.h"
#include "../MazeRaceGame.h"

class ViewManager{
	public:
		static ViewManager* Inst();
		ViewManager();
		//std::stringstream getText();
		void update();
		void render(const unsigned int* arr);
		void timer(int frameIndex);
		unsigned int getBkgIndex();
		void changeView();
		void setLookAt(float Z_pos);
		bool is3D();
		int phaseIndex();
		int difficultyIndex();
		int gameButtonIndex();

	protected:
		static ViewManager* m_inst;
		//member data
		Frame* view;
		float positionZ;
		int phase;	//1-4
		//vector<Game> exercisePlan;
};
#endif