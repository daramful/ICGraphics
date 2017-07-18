//
//  main.cpp
//  MP2
//
//  Created by Ginny Lee on 2/22/16.
//  Copyright (c) 2016 Hyung Eun Lee. All rights reserved.
//
// derived from http://graphics.cs.illinois.edu/sites/graphics.dev.engr.illinois.edu/files/mountain-retained.cpp


#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <time.h>

#include "airplane.h"
#include "keyboards.h"
#include "mountain.h"
#include "rendering.h"


void init(void)
{
    GLfloat amb[] = {0.2,0.2,0.2};
    GLfloat diff[] = {1.0,1.0,1.0};
    GLfloat spec[] = {1.0,1.0,1.0};
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    
    glClearColor (0.5, 0.5, 1.0, 0.0);	// sky
    glEnable(GL_DEPTH_TEST);
    
    sealevel = 0.0;
    
    makemountain();
    
    gluLookAt(0.5, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    
}

void display(void)
{
    GLfloat tanamb[] = {0.2,0.15,0.1,1.0};
    GLfloat tandiff[] = {0.4,0.3,0.2,1.0};
    GLfloat tanspec[] = {0.0,0.0,0.0,1.0};	// dirt doesn't glisten
    
    GLfloat seaamb[] = {0.0,0.0,0.2,1.0};
    GLfloat seadiff[] = {0.0,0.0,0.8,1.0};
    GLfloat seaspec[] = {0.5,0.5,1.0,1.0};	// Single polygon, will only have highlight if light hits a vertex just right
    
    GLfloat lpos[] = {0.0,0.0,10.0,0.0};	// sun, high noon
    
    down();
    up();
    left();
    right();
    tleft();
    tright();
    
    moveForward();
    
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
   
    /*
    glLoadIdentity ();             /* clear the matrix
    /* viewing transformation, look at the origin
    gluLookAt (0.5, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    static GLfloat angle = 0.0;
    glRotatef(angle, 0.0, 0.0, 1.0);
    angle += 0.01;
    */
    
    // send the light position down as if it was a vertex in world coordinates
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    
    // load terrain material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tanamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tandiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tanspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);
    
    // Send terrain mesh through pipeline
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,verts);
    glNormalPointer(GL_FLOAT,0,norms);
    glDrawElements(GL_TRIANGLES, 6*(res-1)*(res-1), GL_UNSIGNED_INT, faces);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
    // load water material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, seaamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, seadiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, seaspec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
    
    if (instruction == 1){
        render("Buttons", 10, 475);
        render("- : sea level decreases", 10, 450);
        render("+(=) : sea level increases", 10, 440);
        render("e : resolution increases", 10, 430);
        render("d : resolution decreases", 10, 420);
        render("s : speed down", 10, 410);
        render("f : speed fast", 10, 400);
        
        render("/leftarrow : roll right", 300, 450);
        render("/rightarrow : roll left", 300, 440);
        render("/up_arrow : pitch up", 300, 430);
        render("/down_arrow : pitch down", 300, 420);
        render("/F1: turn left", 300, 410);
        render("/F2 : turn right", 300, 400);
        
        render("esc : escape from window", 10, 350);
        
        render("FPS:", 10, 360);
        //render(fpsArr, 25, 360);
    }
        render("mulitple buttons work together!", 200, 10);
    
    // Send water as a single quad
    glNormal3f(0.0,0.0,1.0);
    glBegin(GL_QUADS);
    glVertex3f(-5,-5,sealevel);
    glVertex3f(5,-5,sealevel);
    glVertex3f(5,5,sealevel);
    glVertex3f(-5,5,sealevel);
    glEnd();
    
    
    //fps step
    frame++;
    timer = glutGet(GLUT_ELAPSED_TIME);
    elasped = timer - start;
    if (elasped > 1000) {
        float fps = (frame*500.f)/(elasped);
        start = timer;
        frame = 0;
        sprintf(fpsArr, "%f", fps);
    }
    
    if(instruction==1)
        render(fpsArr, 40, 360);
    

    glutSwapBuffers();
    glFlush ();
    
    glutPostRedisplay();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0,(float)w/h,0.01,10.0);
    glMatrixMode (GL_MODELVIEW);
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ((const char*)"MP2_hlee295");
    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(direct);
    glutSpecialUpFunc(keyUp);
    glutMainLoop();
    return 0;
}