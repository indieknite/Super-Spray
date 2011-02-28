/*
 *  StartScreen.cpp
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 2/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

//#include <stdlib.h>	// Windows
#include <unistd.h>		// Mac OS X
//#include <gl/glut.h>	// Windows
#include <GLUT/glut.h>	// mac OS X

#include "DrawText.h"
#include "Target.h"

// Define the current window state of the game.
#define STATE_CALIBRATE		0
#define STATE_START			1
#define STATE_PLAY			2

// If true, a shot was fired by the user and an appropriate action
// should be done by the game.
extern bool isShotFired;

// The total amount of targets to display on the start screen.
const int maxNumTargets = 100;

// Placeholder for changing the values of the created target.
Target target;
// Holds all the targets to be displayed that are created.
Target splash[maxNumTargets];
int i = 0;

// Draws a box to display behind the title so that it can be read easier.
void drawBox()
{
	glColor4d(0.5, 0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3d(100.0, 50.0, 0.0);
	glVertex3d(100.0, -50.0, 0.0);
	glVertex3d(-100.0, -50.0, 0.0);
	glVertex3d(-100.0, 50.0, 0.0);
	glEnd();
}

short startDisplay()
{
	// Disable Depth Test to enable alpha to be shown.
	glDisable(GL_DEPTH_TEST);
	
	target = Target(Vec3(rand() % glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_SCREEN_WIDTH)/2,
						 rand() % glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_SCREEN_HEIGHT)/2, 0));
	target.setColor(Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX));
	splash[i] = target;
	i = (i + 1) % maxNumTargets;
	
	for(int j = 0; j < maxNumTargets; j++)
	{
		splash[j].drawTarget();
		//sleep(200);			// Windows
		usleep(200);			// Mac OS X
		glutPostRedisplay();
	}
	
	glPushMatrix();
	glTranslated(-193, 5.0, 0.0);
	drawBox();
	glPopMatrix();
	
	glColor3f(1, 1, 1);
	glRasterPos2f(-275, 0);
	drawSentence("SUPER SPRAY");
	
	// Re-enable Depth Test after alpha rendering is done.
	glEnable(GL_DEPTH_TEST);
	
	if(isShotFired)
	{
		//if(shot[0] < _ || shot[1] < _)
			return STATE_PLAY;
		//else if(shot[0] < _ || shot[1] < _)
		//	return STATE_CALIBRATE;
	}
	else
		return STATE_START;
}