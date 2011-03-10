/*
 *  PlayScreen.h
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 2/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PlayScreen__
#define __PlayScreen__

#define TIME_STEP		0.05f

float getTime();
void setTime(float newTime);
void decrementTime(float deltaTime); 

void checkAllHits();
void decreaseTargetTimeOnScreen();

short playDisplay();

#endif