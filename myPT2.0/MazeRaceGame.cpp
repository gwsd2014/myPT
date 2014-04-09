#include "MazeRaceGame.h"


MazeRaceGame::MazeRaceGame(): Game(){
	positionZ = -5.0;
	backgroundIDIndex = 1;
	threeD = true;
}

MazeRaceGame::~MazeRaceGame(){
	//do nothing
}

void MazeRaceGame::update(){
	positionZ += 0.1;
}

void MazeRaceGame::drawRoom(void)
{
	printf("In drawRoom function");
	//glEnable( GL_TEXTURE_2D );
	//TextureManager::Inst()->BindTexture(3);

    glBegin( GL_QUADS );
		// Floor
        glNormal3f( 0.0f, 1.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -5.0f, -5.0f, -5.0f );
		glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( -5.0f, -5.0f, 5.0f );
		glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 5.0f, -5.0f, 5.0f );
		glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( 5.0f, -5.0f, -5.0f );
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, m_wall_texture_id2);
    glBegin( GL_QUADS );
		// Ceiling
		glColor3f( 0.0, 1.0, 0.0 );
        glNormal3f( 0.0f, -1.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -5.0f, 5.0f, 5.0f );
		glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( -5.0f, 5.0f, -5.0f );
		glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 5.0f, 5.0f, -5.0f );
		glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( 5.0f, 5.0f, 5.0f );
	glEnd();

	
    glBegin( GL_QUADS );
		// Front wall
		glColor3f( 0.0, 0.0, 1.0 );
        glNormal3f( 0.0f, 0.0f, 1.0f );
		glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -5.0f, 5.0f, -5.0f );
		glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( -5.0f, -5.0f, -5.0f );
		glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 5.0f, -5.0f, -5.0f );
		glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( 5.0f, 5.0f, -5.0f );
	
        // Back wall
		glColor3f( 1.0, 1.0, 0.0 );
        glNormal3f( 0.0f, 0.0f, -1.0f );
		glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( 5.0f, 5.0f, 5.0f );
		glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( 5.0f, -5.0f, 5.0f );
		glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( -5.0f, -5.0f, 5.0f );
		glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( -5.0f, 5.0f, 5.0f );

        // Left wall
		glColor3f( 0.0, 1.0, 1.0 );
        glNormal3f( 1.0f, 0.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -5.0f, 5.0f, 5.0f );
		glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( -5.0f, -5.0f, 5.0f );
		glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( -5.0f, -5.0f, -5.0f );
		glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( -5.0f, 5.0f, -5.0f );

        // Right wall
		glColor3f( 1.0, 0.0, 1.0 );
        glNormal3f( -1.0f, 0.0f, 0.0f );
		glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( 5.0f, 5.0f, -5.0f );
		glTexCoord2f( 1.0f, 0.0f );
        glVertex3f( 5.0f, -5.0f, -5.0f );
		glTexCoord2f( 1.0f, 1.0f );
        glVertex3f( 5.0f, -5.0f, 5.0f );
		glTexCoord2f( 0.0f, 1.0f );
        glVertex3f( 5.0f, 5.0f, 5.0f );
	glEnd();

	//glDisable( GL_TEXTURE_2D );
}

void MazeRaceGame::render(unsigned int* objectTexIDs){
	//gluLookAt(0.0, 0.0, positionZ, 0.0, 0.0, positionZ + 10.0, 0.0, 1.0, 0.0);
	drawRoom();
}

void MazeRaceGame::timer(int value){
	value++;
}
