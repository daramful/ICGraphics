//
//  main.cpp
//  MP1
//
//  Created by Hyung Eun Lee on 2/8/16.
//  Copyright (c) 2016 Hyung Eun Lee. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>
#include "helper.h"

void init(void)
{
    // init your data, setup OpenGL environment here
    glClearColor(0.9,0.9,0.9,1.0); // clear color is gray
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // uncomment this function if you only want to draw wireframe model
    // GL_POINT / GL_LINE / GL_FILL (default)
    glPointSize(4.0);
}


//Source: renderText partially brought from https://www.opengl.org/discussion_boards/showthread.php/143335-GLUT-to-display-text

void renderText(float x, float y, const char *string){
    const char *c;
    c = string;
    glColor3f(1.0, 0.0, 0.0);
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

//dance function
float dance(float c, float amp, float offset){
    //if the function has been turned on (=1)
    if (danceMode == 1){
        c = c+amp*cos(3.14*(elasped+offset));
    }
    return c;
}


void display(void){
    if(vertex==1){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // I filled with color
    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // I not filled with color
    }
    
    frame++;
    
    // put your OpenGL display commands here
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // reset OpenGL transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // reset transformation matrix to identity
    
    // setup look at transformation so that
    // eye is at : (0,0,3)
    // look at center is at : (0,0,0)
    // up direction is +y axis
    gluLookAt(0.f,0.f,3.f,0.f,0.f,0.f,0.f,1.f,0.f);
    glRotatef(fRotateAngle,0.f,1.f,0.f);
    
    //vertices
    //declare vertices
    //vertices derived from 2-D Meshes
    //link: https://courses.engr.illinois.edu/cs418/fa2012/apps/mesh2d.html
    
    float v1[] = {dance(-0.6, 0.06, 1.0), dance(1, 0.05, 0.05)};
    float v2[] = {dance(-0.6, 0.1, 0.6), dance(0.6, 0.1, 0.01)};
    float v3[] = {dance(-0.2, 0.05, 0.1), dance(0.6, 0.08, -0.1)};
    float v4[] = {dance(-0.2, 0.04, 0.6), dance(-0.6, -0.03, 0)};
    float v5[] = {dance(-0.6, 0.09, 0.2), dance(-0.6, 0.04, -0.3)};
    float v6[] = {dance(-0.6, 0.08,-1.0), dance(-1.0, 0.07, 0.5)};
    float v7[] = {dance(0.6, 0.02,-0.5), dance(-1.0, 0.03, 0.2)};
    float v8[] = {dance(0.6, -0.03, 0.09), dance(-0.6, -0.05, 0.05)};
    float v9[] = {dance(0.2, -0.01, 0.8), dance(-0.6, -0.03, 0)};
    float v10[] = {dance(0.2, -0.02, 0.7), dance(0.6, -0.05, 0.6)};
    float v11[] = {dance(0.6, -0.05, 0.8), dance(0.6, 0.03, 0.4)};
    float v12[] = {dance(0.6, -0.02, 0.5), dance(1.0, -0.02, 0.1)};
    //the dance function will change where the points are, which would make the I "dance" with its changed points
    //however, since dance function is not on, it will remain as a point
    
    glPushMatrix();
    //triangles -- connecting lines with other points
    int a = rand();
    float orange[] = {(float)a,(float) a, (float)a};
    glColor3fv(orange); //color of I
    
    if(rotateMode == 1){
        glRotatef(90, 0, 0, 1.0);
    }
    
    if(translateMode == 1){
        glTranslatef(0.2*sin(3.14*(elasped-0.3)), 0, 0);
    }
    
    if(instruction==0 && rotateMode == 0){
        renderText(-2, 2, "q = instruction");
    }
    if(instruction==1 && (rotateMode == 0 || translateMode == 0)){
        renderText(-2,2,"Keyboard controls:");
        renderText(-2,1.9,"v = vertex");
        renderText(-2,1.8,"t = move around");
        renderText(-2,1.7,"d = dance");
        renderText(-2, 1.6, "r = rotate");
        renderText(-2,1.5, "esc = exit");
        
        renderText(-2,1.2,"FPS:");
        renderText(-2,1.0,fpsArr);
    }
    
    
    glBegin(GL_TRIANGLE_FAN);
        glColor3fv(orange);
        glVertex2fv(v3);
        glVertex2fv(v2);
        glVertex2fv(v1);
        glVertex2fv(v12);
        glVertex2fv(v10);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
        glColor3fv(orange);
        glVertex2fv(v10);
        glVertex2fv(v11);
        glVertex2fv(v12);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
        glColor3fv(orange);
        glVertex2fv(v9);
        glVertex2fv(v10);
        glVertex2fv(v3);
        glVertex2fv(v4);
        glVertex2fv(v6);
        glVertex2fv(v7);
        glVertex2fv(v8);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
        glColor3fv(orange);
        glVertex2fv(v5);
        glVertex2fv(v6);
        glVertex2fv(v4);
    glEnd();
    //end of creating triangles
    
    //all from the lecture (2.4.2016)
    //connecting them all
    glBegin(GL_LINE_LOOP);
        glColor3f(0,0,1.f);
        glVertex2fv(v1);
        glVertex2fv(v12);
        glVertex2fv(v11);
        glVertex2fv(v10);
        glVertex2fv(v9);
        glVertex2fv(v8);
        glVertex2fv(v7);
        glVertex2fv(v6);
        glVertex2fv(v5);
        glVertex2fv(v4);
        glVertex2fv(v3);
        glVertex2fv(v2);
    
    glEnd();
    glPopMatrix();
    //
    
    
   //fps step
    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    elasped = time - start;
    if (elasped > 1000) {
        float fps = (frame*500.f)/(elasped);
        start = time;
        frame = 0;
        sprintf(fpsArr, "%f", fps);
    }
    
    if(instruction==1)
        renderText(-2,1.0,fpsArr);
    
    glFlush();        // force execution of GL commands in finite time
    glutSwapBuffers();	// swap front/back framebuffer to avoid flickering (from MP1 instruction)
}


//necessary to have it
void reshape (int w, int h)
{
    // reset viewport ( drawing screen ) size
    glViewport(0, 0, w, h);
    float fAspect = ((float)w)/h;
    // reset OpenGL projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f,fAspect,0.001f,30.f);
}


// put your keyboard control here
void keyboard(unsigned char key, int x, int y){
    if(key == 27) {
        // ESC hit, so quit
        printf("demonstration finished.\n");
        exit(0);
    }
    
    if (key == 'q'){
        instruction = 1 - instruction;
    }
    
    if(key == 'v'){
        vertex = 1-vertex;
        
    }
    if(key == 'd'){
        danceMode = 1-danceMode;
    }
    if(key == 't'){
        translateMode = 1-translateMode;
    }
    if(key == 'r'){
        rotateMode = 1-rotateMode;
    }
}

void timer(int v){
    // speed for animation
    
    elasped += 0.2;
    
    glutPostRedisplay(); // trigger display function by sending redraw into message queue
    glutTimerFunc(30,timer,0); // restart timer again
}


int main(int argc, char* argv[]){
    
    glutInit(&argc, (char**)argv);
    
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ((const char*)"MP1_hlee295");
    
    init(); // setting up user data & OpenGL environment
    
    //set up the call-back functions
    glutDisplayFunc(display);  // called when drawing
    glutReshapeFunc(reshape);  // called when change window size
    glutKeyboardFunc(keyboard); // called when received keyboard interaction
    glutTimerFunc(30,timer,0); // a periodic timer. Usually used for updating animation
    
    glutMainLoop(); //start the main message-callback loop
    
    return 0;
}

