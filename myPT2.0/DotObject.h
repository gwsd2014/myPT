#ifndef DotObject_H
#define DotObject_H

#include <GL/freeglut.h>
#include "common/TextureManager.h"
#include "common/GLUtilities.h"
#include "vertex3.h"

class DotObject
{

public:

	DotObject(){
		//deafault constructor
	}
	
    DotObject( unsigned int id, GLfloat s, GLfloat posx, GLfloat posy, 
                 GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tw=1.0f, GLfloat th=1.0f)
    {
        size=s;
        texOffset[0] = tx; texOffset[1] = ty;
        texOffset[2] = tx + tw; texOffset[3] = ty + th;
        position.x() = posx; position.y() = posy; position.z() = 0.0f;
        objectIDIndex = id;
    }

    void update()
    {
		//does not need to do anything.
    }
    
    void render(const unsigned int* objectTexIDs)
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
			glTranslatef( position.x(), position.y(), position.z());
			TextureManager::Inst()->BindTexture(objectTexIDs[objectIDIndex]);
			drawSimpleMesh( WITH_POSITION|WITH_TEXCOORD, 4, meshData, GL_QUADS );
        glPopMatrix();

		//drawDot();
    }

	//Member data
    GLfloat texOffset[4];
	GLfloat size;
    vertex3 position;
    unsigned int objectIDIndex;	//will also be able to take care of position
};

#endif