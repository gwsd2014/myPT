#include <GL/freeglut.h>
//#include "Simple OpenGL Image Library\src\SOIL.h"
#include <iostream>

const unsigned int backgroundTexID = 1;
GLint winWidth = 600, winHeight = 600;
//Viewing parameters
GLfloat x_0 = 50.0, y_0=50.0, z_0=50.0;	//Viewing Coordinate origin
GLfloat xref= 50.0, yref=50.0, zref= 0.0;	//Look-at point.
GLfloat Vx=0.0, Vy=1.0, Vz=0.0;		//View-up vector.

/*Set coordinate limits for the clipping window */
GLfloat xwMin =-40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

/*Set positions for near and far clipping planes */
GLfloat dnear = 25.0, dfar = 125.0;

void init(){
 glClearColor(1.0,1.0,1.0,0.0);

 glMatrixMode(GL_MODELVIEW);
 gluLookAt(x_0, y_0, z_0, xref, yref, zref, Vx, Vy, Vz);

 glMatrixMode(GL_PROJECTION);
 glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void update()
{
    glutPostRedisplay();
}

void render()
{
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    glutSwapBuffers();

	glColor3f(0.0, 1.0, 0.0);	//Set fill color to green
	glPolygonMode(GL_FRONT, GL_FILL);	//fill front face
	glPolygonMode(GL_BACK, GL_LINE);	//Wireframe back face
	glBegin(GL_QUADS);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(100.0, 0.0, 0.0);
		glVertex3f(100.0, 100.0, 0.0);
		glVertex3f(0.0, 100.0, 0.0);
	glEnd();

	glFlush();
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

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_RGB| GLUT_SINGLE);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(winWidth, winHeight);
    //glutInitDisplayMode( GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH|GLUT_MULTISAMPLE );
    glutCreateWindow( "ch2_01_OpenGL_Env" );
   // glutFullScreen();
    
	init();
    //glutIdleFunc( update );
    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyEvents );
    
    glutMainLoop();
    return 0;
}
