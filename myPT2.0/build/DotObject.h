#ifndef _DOTOBJECT_H_
#define _DOTOBJECT_H_

#include <GL/freeglut.h>
#include "common/TextureManager.h"
#include "common/GLUtilities.h"
#include "vertex3.h"

enum Color{red, green, blue};
class DotObject
{
public:
	GLfloat texOffset[4];
	GLfloat size;
    vertex3 position;
   
    bool canTouch;
	bool tapped;
	int timer;
	Color dcolor;
	unsigned int objectTextureID;	//will also be able to take care of position

	//donuts.push_back(DotObject(dotNamesArray[0], 0.1f, 0.25f, 0.45f));
    DotObject( GLuint id, GLfloat s, GLfloat posx, GLfloat posy, 
                 GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tw=1.0f, GLfloat th=1.0f)
    {
        size=s;
        texOffset[0] = tx; texOffset[1] = ty;
        texOffset[2] = tx + tw; texOffset[3] = ty + th;
        position.setx(posx); position.sety(posy); position.setz(0.0f);
        objectTextureID = id;
		timer = 120;
    }

	void setDotColor(Color color){
		switch (color){
			case red:
				glColor3f(1,0,0);
			break;
			case green:
				glColor3f(0,1,0);
			break;
			case blue:
				glColor3f(0,0,1);
			break;
		}
	}

	void drawDot(){
		//glEnable(
		setDotColor(dcolor);
		glPushMatrix();
			glTranslatef(position.getx(), position.gety(), 0.0);
			glutSolidTorus(0.1, 0.3, 30,30);
		glPopMatrix();
	}
    
    void update()
    {
		//does not need to do anything.
    }
    
    void render()
    {
		// Draws images from bitmap
        GLfloat vertices[][3] = {
            { 0.0f, 0.0f, 0.0f }, { size, 0.0f, 0.0f },
            { size, size, 0.0f }, { 0.0f, size, 0.0f }
        };
        GLfloat texcoords[][2] = {
            {texOffset[0], texOffset[1]}, {texOffset[2], texOffset[1]},
            {texOffset[2], texOffset[3]}, {texOffset[0], texOffset[3]}
        };
        VertexData meshData = { &(vertices[0][0]), NULL, NULL, &(texcoords[0][0]) };
        

        glPushMatrix();
			glTranslatef( position.getx(), position.gety(), position.getz() );
			TextureManager::Inst()->BindTexture( objectTextureID );
			//printf("Binding Fruit object with texture %d\n", objectTextureID);
			drawSimpleMesh( WITH_POSITION|WITH_TEXCOORD, 4, meshData, GL_QUADS );
        glPopMatrix();

		//drawDot();
    }

};
#endif