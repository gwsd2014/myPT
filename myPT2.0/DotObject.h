#include <GL/freeglut.h>
#include <MSHTML.h>
#include <NuiApi.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "common/TextureManager.h"
#include "common/GLUtilities.h"

class DotObject
{
public:
	    
    GLfloat size;
    GLfloat texOffset[4];
    Vertex position;
    Vertex velocity;
    unsigned int objectID;
    bool canSlice;

    DotObject( unsigned int id, bool b, GLfloat s,
                 GLfloat tx=0.0f, GLfloat ty=0.0f, GLfloat tw=1.0f, GLfloat th=1.0f )
    {
        canSlice = b; size = s;
        texOffset[0] = tx; texOffset[1] = ty;
        texOffset[2] = tx + tw; texOffset[3] = ty + th;
        position.x = 0.0f; position.y = 0.0f; position.z = 0.0f;
        velocity.x = 0.0f; velocity.y = 0.0f; velocity.z = 0.0f;
        objectID = id;
    }
    
    void update()
    {
        position.x += velocity.x;
        position.y += velocity.y;
        
        const GLfloat gravity = -0.001f;
        velocity.y += gravity;
    }
    
    void render()
    {
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
        glTranslatef( position.x, position.y, position.z );
        TextureManager::Inst()->BindTexture( objectTexIDs[objectID] );
        drawSimpleMesh( WITH_POSITION|WITH_TEXCOORD, 4, meshData, GL_QUADS );
        glPopMatrix();
    }
};