//
//  airplane.h
//  MP2
//
//  Created by Ginny Lee on 3/7/16.
//  Copyright (c) 2016 Hyung Eun Lee. All rights reserved.
//

#ifndef MP2_airplane_h
#define MP2_airplane_h

//#include "vector.h"
//not using vector.h anymore b/c I found another solution
// Helper class for our airplane

#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

#include "mountain.h"

//variables
float camera[16];       //array used to store camera coordinates using glGetFloatv
float speed = 0.001;    //speed of forward translation
float rot_ang = 15;     //rotation angle or turning left and right

//state vars to turn rolling/pitching

float pitch_up = 0;
float pitch_down = 0;
float roll_right = 0;
float roll_left = 0;
float turn_left = 0;
float turn_right = 0;
float vert_u = 0;
float vert_d = 0;
/*
 *  referenced from: Chatper 8
 */

//default
void moveForward(void){
    glGetFloatv(GL_MODELVIEW_MATRIX, camera);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, speed);
    glMultMatrixf(camera);
}

void up(void){
    if(pitch_up)
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, camera);
        glLoadIdentity();
        glRotatef(-0.75,1, 0.0, 0.0);
        glMultMatrixf(camera);
    }
}

void down(void){
    if(pitch_down)
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, camera);
        glLoadIdentity();
        glRotatef(0.75,1, 0.0, 0.0);
        glMultMatrixf(camera);
    }
}

void right(void){
    if(roll_right)
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, camera);
        glLoadIdentity();
        glRotatef(0.75,1, 0.0, -1.0);
        glMultMatrixf(camera);
    }
}

void left(void){
    if(roll_left)
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, camera);
        glLoadIdentity();
        glRotatef(0.75,1, 0.0, 1.0);
        glMultMatrixf(camera);
    }
}

void tleft(void){
    if(turn_left){
        glGetFloatv(GL_MODELVIEW_MATRIX, camera);
        glLoadIdentity();
        glRotatef(-rot_ang, 0.0, 1.0, 0.0);
        glMultMatrixf(camera);
    }
}

void tright(void){
    if (turn_right){
        glGetFloatv(GL_MODELVIEW_MATRIX, camera);
        glLoadIdentity();
        glRotatef(rot_ang, 0.0, 1.0, 0.0);
        glMultMatrixf(camera);
    }
}


//airplane Blackbird; //SR-71 Blackbird



#endif

