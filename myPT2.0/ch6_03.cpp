#include <GL/freeglut.h>
#include <MSHTML.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "build/DotObject.h"
#include "build/Kinect.h"
#include "build/Game.h"
#include "build/vertex3.h"
#include "build/Player.h"
#include "common/TextureManager.h"
#include "common/GLUtilities.h"
#include "build\GameDotSpot.h"
// frame index
int g_frameIndex = 0;
Player* player = new Player();
Kinect kinect = Kinect(player);
Game *game = new GameDotSpot(player);


float randomValue( float min, float max )
{
    return (min + (float)rand()/(RAND_MAX+1.0f) * (max - min));
}

void update()
{
	kinect.update();
	game->update();
    glutPostRedisplay();
}

void render()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClearDepth(1.0f);
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glEnable( GL_TEXTURE_2D );
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, 1.0, 0.0, 1.0, -1.0, 1.0 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	//printf("");
	//switch statement here?
	game->render();
    
    glutSwapBuffers();
}

void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
}

void keyEvents( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: case 'Q': case 'q':
        glutLeaveMainLoop();
        return;
    }
    glutPostRedisplay();
}

void timer( int value ) {	
	// increase frame index
	g_frameIndex++;

	//This determines speed
	//Which in turn determines difficulty
	game->timer(g_frameIndex);
	// render
	//glutPostRedisplay();

	// reset timer
	// 16 ms per frame ( about 60 frames per second )
	glutTimerFunc( 16, timer, 0 );
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE );
    glutCreateWindow( "myPT" );
   // glutFullScreen();
	glutInitWindowSize( 500, 500 ); 
	glutInitWindowPosition( 100, 100 );
    
    glutIdleFunc( update );
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyEvents );
	glutTimerFunc( 16, timer, 0 );

    glutMainLoop();
    
    kinect.destroy();
    return 0;
}
