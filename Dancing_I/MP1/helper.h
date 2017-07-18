//
//  helper.h
//  MP1
//
//  Created by Ginny Lee on 2/9/16.
//  Copyright (c) 2016 Hyung Eun Lee. All rights reserved.
//

#ifndef MP1_helper_h
#define MP1_helper_h



//variables
//motions
int vertex = 1;             //dipmode from Hello Triangle
int translateMode = 0;  //false--turned off
int danceMode = 0;      //false--turned off
int rotateMode = 0;     //false--turned off
int instruction = 0;

// variables for fps
char fpsArr[30];
float fRotateAngle = 0.f;
int frame=0;
int time;
int start=0;
float elasped = 0;


#endif
