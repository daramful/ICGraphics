//
//  keyboard.h
//  MP2
//
//  Created by Ginny Lee on 3/8/16.
//  Copyright (c) 2016 Hyung Eun Lee. All rights reserved.
//

#ifndef MP2_keyboards_h
#define MP2_keyboards_h

#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

#include "airplane.h"

float sealevel = 0;
float polysize = 0.01;
int instruction = 0;    //false--turned off


    //referenced 1 from: http://graphics.cs.illinois.edu/sites/graphics.dev.engr.illinois.edu/files/mountain.cpp
    //referenced 2 from: http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/

    
    
    void static keyboard(unsigned char key, int x, int y)
    {
        switch (key) {
            case 'q':
                instruction = 1 - instruction;
                break;
            case '-':
                sealevel -= 0.01;
                break;
            case '+':
            case '=':
                sealevel += 0.01;
                break;
            case 'e':
                res = (res-1)*2 + 1;
                makemountain();
                break;
            case 'd':
                res = (res-1)/2 + 1;
                makemountain();
                break;
            case 'f':
                speed += 0.001;
                break;
            case 's':
                speed -= 0.001;
                break;
            case 27:
                exit(0);
                break;
        }
    }

    void direct(int key, int x, int y)    //pressing the key
    {
        switch(key){
            case GLUT_KEY_LEFT:
                roll_left = 1;
                break;
            case GLUT_KEY_RIGHT:
                roll_right = 1;
                break;
            case GLUT_KEY_UP:
                pitch_up = 1;
                break;
            case GLUT_KEY_DOWN:
                pitch_down = 1;
                break;
            case GLUT_KEY_F1:
                turn_left = 1;
                break;
            case GLUT_KEY_F2:
                turn_right = 1;
                break;
        }
    }

    void keyUp(int key, int x, int y) //releasing the key
    {
        switch(key){
            case GLUT_KEY_LEFT:
                roll_left = 0;
                break;
            case GLUT_KEY_RIGHT:
                roll_right = 0;
                break;
            case GLUT_KEY_UP:
                pitch_up = 0;
                break;
            case GLUT_KEY_DOWN:
                pitch_down = 0;
                break;
            case GLUT_KEY_F1:
                turn_left = 0;
                break;
            case GLUT_KEY_F2:
                turn_right = 0;
                break;
        }
    }
#endif
