#include "Menu.h"

Menu::Menu(){
	backgroundTexID = 0; //make black screen or something?
}

Menu::Menu(const char* filename){
	backgroundTexID = Helper::nextTextureID();
	if ( TextureManager::Inst()->LoadTexture(filename, backgroundTexID, GL_BGR_EXT) )
	{
		printf("Menu background Texture opened succesfullyl\n\n\n\n");
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}
}

Menu::Menu(unsigned int backgroundID){
	backgroundTexID = backgroundID;
}

void Menu::addButton(Button* button){
	buttons.push_back(button);
}

