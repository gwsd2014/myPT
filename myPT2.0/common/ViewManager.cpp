#include "ViewManager.h"


ViewManager* ViewManager::m_inst(0);

ViewManager* ViewManager::Inst()
{
	if(!m_inst)
		m_inst = new ViewManager();

	return m_inst;

}

ViewManager::ViewManager()
{
	this->view = new LogoMenu();
}

void ViewManager::update(){
	view->update();
	if(this->view->viewUpdated)
		changeView();
}

void ViewManager::render(const unsigned int* objectTexIDs){
	view->render(objectTexIDs);
}

void ViewManager::timer(int frameIndex){
	view->timer(frameIndex);
}

unsigned int ViewManager::getBkgIndex(){
	return view->backgroundIDIndex;
}

void ViewManager::changeView(){
	this->view = view->nextFrame;
}