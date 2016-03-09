//
//  rendering.h
//  MP2
//
//  Created by Ginny Lee on 3/8/16.
//  Copyright (c) 2016 Hyung Eun Lee. All rights reserved.

//NOT BEING USED

#ifndef MP2_rendering_h
#define MP2_rendering_h

//variables
//motions


// variables for fps
char fpsArr[30];
float fRotateAngle = 0.f;
int frame=0;
int timer;
int start=0;
float elasped = 0;

void render(char *string,float x,float y)
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glLoadIdentity();
    
    char *c;
    glWindowPos2i(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
    }
    
    glPopAttrib();
    glPopMatrix();
}


#endif
