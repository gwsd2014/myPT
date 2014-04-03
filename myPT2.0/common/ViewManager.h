#ifndef ViewManager_H
#define ViewManager_H

#include "../Frame.h"
#include "GLUtilities.h"
#include "../Menu.h"

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

	protected:
		static ViewManager* m_inst;
		//member data
		Frame* view;
};
#endif