#include "GameDotSpot.h"



void GameDotSpot::init(){
			//Create background texture
	if ( TextureManager::Inst()->LoadTexture("DotSpotRoom-01.jpg", backgroundTexID, GL_BGR_EXT) )
	{
		printf("Background Texture opened succesfullyl\n\n\n\n");
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}

	//create fruit textures?
	for ( int i=0; i<3; ++i )
	{
		std::stringstream ss;
		ss << "FruitNinja" << i+2 << ".png";
		if ( TextureManager::Inst()->LoadTexture(ss.str().c_str(), donuts.at(i).objectTextureID, GL_BGRA_EXT, 4) )
		{
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		}
	}

	//create game over texture 
	if ( TextureManager::Inst()->LoadTexture("FruitNinja6.jpg", gameOverTexID, GL_BGR_EXT) )
	{
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}
}

GameDotSpot::GameDotSpot(): Game(){
	hotDonut = 1;
	donuts.push_back(DotObject(1, 0.1f, 0.25f, 0.45f));
	donuts.push_back(DotObject(2, 0.1f,  0.45f, 0.45f));
	donuts.push_back(DotObject(0, 0.1f,  0.66f, 0.45f));
	init();
}

GameDotSpot::GameDotSpot(Player* playerPtr): Game(){
	player = playerPtr;
	hotDonut = 1;
	donuts.push_back(DotObject(1, 0.1f,  0.25f, 0.45f));
	donuts.push_back(DotObject(2, 0.1f,  0.45f, 0.45f));
	donuts.push_back(DotObject(0, 0.1f,  0.66f, 0.45f));
	init();
}

bool isTouched = false;
void GameDotSpot::update(){
	// Update fruit objects and intersections with the hands
	
	float donutX = donuts.at(hotDonut).position.getx();
	float donutY = donuts.at(hotDonut).position.gety();

	//computes distance between fruit and left hand blade
	float distance = player->leftDistance(donutX, donutY);
    if ( distance<donuts.at(hotDonut).size ) isTouched = true;
        
	//computes distance between fruit and right hand blade
    distance = player->rightDistance(donutX, donutY);
    if ( distance<donuts.at(hotDonut).size ) isTouched = true;
    
    if ( isTouched )
    {
		//Increase score!
		score+=10;
    }    
}

void GameDotSpot::timer(int frame){
	if(frame % 200 == 0){
		printf("Shuffling donuts!\n\n\n\n\n");
		shuffleDots();
	}
}

void GameDotSpot::shuffleDots(){
	//CHANGESTHE COLORS OF THE DONUTS!
	//update which one is green!
	hotDonut = rand() % 3;
	printf("Hot donut is %d\n", hotDonut);
	switch (hotDonut)
	{
		case 0:
			donuts.at(0).dcolor = green;
			donuts.at(1).dcolor = red;
			donuts.at(2).dcolor = blue;
			donuts.at(0).objectTextureID = 0;
			if(rand() %2){
				donuts.at(1).objectTextureID = 1;
				donuts.at(2).objectTextureID = 2;
			}else{
				donuts.at(1).objectTextureID = 2;
				donuts.at(2).objectTextureID = 1;
			}
		break;
		case 1:
			donuts.at(1).dcolor = green;
			donuts.at(0).dcolor = red;
			donuts.at(2).dcolor = blue;
			donuts.at(1).objectTextureID = 0;
			if(rand() %2){
				donuts.at(0).objectTextureID = 1;
				donuts.at(2).objectTextureID = 2;
			}else{
				donuts.at(0).objectTextureID = 2;
				donuts.at(2).objectTextureID = 1;
			}
		break;
		case 2:
			//Set colors
			donuts.at(0).dcolor = blue;
			donuts.at(1).dcolor = red;
			donuts.at(2).dcolor = green;
			donuts.at(2).objectTextureID = 0;
			if(rand() %2){
				donuts.at(0).objectTextureID = 1;
				donuts.at(1).objectTextureID = 2;
			}else{
				donuts.at(0).objectTextureID = 2;
				donuts.at(1).objectTextureID = 1;
			}
		break;
	}
}

 void GameDotSpot::render(){
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
	if (lives<=0 ){
		TextureManager::Inst()->BindTexture( gameOverTexID );
	}
	else{ 
		printf("Binding background texture\n");
		TextureManager::Inst()->BindTexture( backgroundTexID );	//or keep it the same
	}
	drawSimpleMesh( WITH_POSITION|WITH_TEXCOORD, 4, meshData, GL_QUADS );

	player->render();

	drawSimpleMesh( WITH_POSITION|WITH_TEXCOORD, 4, meshData, GL_QUADS );

	// Blend with dot objects does order matter?
	for ( unsigned int i=0; i<donuts.size(); ++i )
		donuts[i].render();

	player->renderHandTrails();
	glDisable( GL_BLEND );

	// Draw HUD text
	std::stringstream ss;
	ss << "Score: " << score << "  Life: " << (lives<0 ? 0 : lives);


	glRasterPos2f( 0.01f, 0.01f );
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );		//WHITE TEXT
	glutBitmapString( GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)ss.str().c_str() );

}