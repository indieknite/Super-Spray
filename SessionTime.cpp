/*
 *  SessionTime.cpp
 *  Super Spray
 */

//#include <gl/glut.h>		// Windows
#include <GLUT/glut.h>		// Mac OS X

#include "DrawText.h"

float sessionTime = 60.0f;

float getTime()
{
	return sessionTime;
}

void setTime(float newTime)
{
	sessionTime = newTime;
}

void decrementTime(float deltaTime)
{
	sessionTime -= deltaTime;
}