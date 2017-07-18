
//
//  mountain.h
//  MP2
//
//  Created by Ginny Lee on 3/8/16.
//  Copyright (c) 2016 Hyung Eun Lee. All rights reserved.
//

#ifndef MP2_mountain_h
#define MP2_mountain_h

#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

int res = 257;

#define ADDR(i,j,k) (3*((j)*res + (i)) + (k))

GLfloat *verts = 0;
GLfloat *norms = 0;
GLuint *faces = 0;



float frand(float x, float y) {
    static int a = 1588635695, b = 1117695901;
    int xi = *(int *)&x;
    int yi = *(int *)&y;
    srand(((xi * a) % b) - ((yi * b) % a));
    return 2.0*((float)rand()/(float)RAND_MAX) - 1.0;
}

void static mountain(int i, int j, int s)
{
    if (s > 1) {
        
        float x0,y0,z0,x1,y1,z1,x2,y2,z2,x3,y3,z3,x01,y01,z01,x02,y02,z02,x13,y13,z13,x23,y23,z23,x0123,y0123,z0123;
        
        x0 = verts[ADDR(i,j,0)];
        y0 = verts[ADDR(i,j,1)];
        z0 = verts[ADDR(i,j,2)];
        
        x1 = verts[ADDR(i+s,j,0)];
        y1 = verts[ADDR(i+s,j,1)];
        z1 = verts[ADDR(i+s,j,2)];
        
        x2 = verts[ADDR(i,j+s,0)];
        y2 = verts[ADDR(i,j+s,1)];
        z2 = verts[ADDR(i,j+s,2)];
        
        x3 = verts[ADDR(i+s,j+s,0)];
        y3 = verts[ADDR(i+s,j+s,1)];
        z3 = verts[ADDR(i+s,j+s,2)];
        
        x01 = 0.5*(x0 + x1);
        y01 = 0.5*(y0 + y1);
        z01 = 0.5*(z0 + z1);
        
        x02 = 0.5*(x0 + x2);
        y02 = 0.5*(y0 + y2);
        z02 = 0.5*(z0 + z2);
        
        x13 = 0.5*(x1 + x3);
        y13 = 0.5*(y1 + y3);
        z13 = 0.5*(z1 + z3);
        
        x23 = 0.5*(x2 + x3);
        y23 = 0.5*(y2 + y3);
        z23 = 0.5*(z2 + z3);
        
        x0123 = 0.25*(x0 + x1 + x2 + x3);
        y0123 = 0.25*(y0 + y1 + y2 + y3);
        z0123 = 0.25*(z0 + z1 + z2 + z3);
        
        z01 += 0.5*((float)s/res)*frand(x01,y01);
        z02 += 0.5*((float)s/res)*frand(x02,y02);
        z13 += 0.5*((float)s/res)*frand(x13,y13);
        z23 += 0.5*((float)s/res)*frand(x23,y23);
        z0123 += 0.5*((float)s/res)*frand(x0123,y0123);
        
        verts[ADDR(i+s/2,j,0)] = x01;
        verts[ADDR(i+s/2,j,1)] = y01;
        verts[ADDR(i+s/2,j,2)] = z01;
        
        verts[ADDR(i,j+s/2,0)] = x02;
        verts[ADDR(i,j+s/2,1)] = y02;
        verts[ADDR(i,j+s/2,2)] = z02;
        
        verts[ADDR(i+s,j+s/2,0)] = x13;
        verts[ADDR(i+s,j+s/2,1)] = y13;
        verts[ADDR(i+s,j+s/2,2)] = z13;
        
        verts[ADDR(i+s/2,j+s,0)] = x23;
        verts[ADDR(i+s/2,j+s,1)] = y23;
        verts[ADDR(i+s/2,j+s,2)] = z23;
        
        verts[ADDR(i+s/2,j+s/2,0)] = x0123;
        verts[ADDR(i+s/2,j+s/2,1)] = y0123;
        verts[ADDR(i+s/2,j+s/2,2)] = z0123;
        
        mountain(i,j,s/2);
        mountain(i+s/2,j,s/2);
        mountain(i,j+s/2,s/2);
        mountain(i+s/2,j+s/2,s/2);
        
    } else {
        
        float dx,dy,dz;
        
        if (i == 0) {
            dx = verts[ADDR(i+1,j,2)] - verts[ADDR(i,j,2)];
        } else if (i == res-1) {
            dx = verts[ADDR(i,j,2)] - verts[ADDR(i-1,j,2)];
        } else {
            dx = (verts[ADDR(i+1,j,2)] - verts[ADDR(i-1,j,2)])/2.0;
        }
        
        if (j == 0) {
            dy = verts[ADDR(i,j+1,2)] - verts[ADDR(i,j,2)];
        } else if (j == res-1) {
            dy = verts[ADDR(i,j,2)] - verts[ADDR(i,j-1,2)];
        } else {
            dy = (verts[ADDR(i,j+1,2)] - verts[ADDR(i,j-1,2)])/2.0;
        }
        
        dx *= res;
        dy *= res;
        dz = 1.0/sqrt(dx*dx + dy*dy + 1.0);
        dx *= dz;
        dy *= dz;
        
        norms[ADDR(i,j,0)] = dx;
        norms[ADDR(i,j,1)] = dy;
        norms[ADDR(i,j,2)] = dz;
    }
}

void makemountain()
{
    int i,j;
    
    if (verts) free(verts);
    if (norms) free(norms);
    if (faces) free(faces);
    
    verts = (GLfloat *)malloc(res*res*3*sizeof(GLfloat));
    norms = (GLfloat *)malloc(res*res*3*sizeof(GLfloat));
    faces = (GLuint *)malloc((res-1)*(res-1)*6*sizeof(GLuint));
    
    verts[ADDR(0,0,0)] = -5.0;
    verts[ADDR(0,0,1)] = -5.0;
    verts[ADDR(0,0,2)] = 0.0;
    
    verts[ADDR(res-1,0,0)] = 5.0;
    verts[ADDR(res-1,0,1)] = -5.0;
    verts[ADDR(res-1,0,2)] = 0.0;
    
    verts[ADDR(0,res-1,0)] = -5.0;
    verts[ADDR(0,res-1,1)] = 5.0;
    verts[ADDR(0,res-1,2)] = 0.0;
    
    verts[ADDR(res-1,res-1,0)] = 5.0;
    verts[ADDR(res-1,res-1,1)] = 5.0;
    verts[ADDR(res-1,res-1,2)] = 0.0;
    
    mountain(0,0,res-1);
    
    GLuint *f = faces;
    for (j = 0; j < res-1; j++) {
        for (i = 0; i < res-1; i++) {
            *f++ = j*res + i;
            *f++ = j*res + i + 1;
            *f++ = (j+1)*res + i + 1;
            *f++ = j*res + i;
            *f++ = (j+1)*res + i + 1;
            *f++ = (j+1)*res + i;
        }
    }
    
}



#endif
