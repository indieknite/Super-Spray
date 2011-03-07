/*
 *  PlayScreen.cpp
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 2/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

//#include <stdlib.h>		// Windows
//#include <gl/glut.h>		// Windows
#include <GLUT/glut.h>		// Mac OS X

#include "Target.h"

#define WIDTH		(double)glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT		(double)glutGet(GLUT_SCREEN_HEIGHT)

// Define the current window state of the game.
#define STATE_START			1
#define STATE_PLAY			2

extern int* shot;

Target target1;
Target target2(Vec3(300.0, -250.0, 0.0));
Target target3(Vec3(-600.0, 320.0, 0.0));

// Create reticle for debugging purposes.
void reticle()
{
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glLineWidth(8);
	glBegin(GL_LINES);
	glVertex3d(-15, 0.0, 0.0);
	glVertex3d(15, 0.0, 0.0);
	
	glVertex3d(0.0, -15, 0.0);
	glVertex3d(0.0, 15, 0.0);
	glEnd();
	glLineWidth(1);
}

void playDisplay()
{
	// Reticle.
	glPushMatrix();
	glTranslated(shot[0], shot[1], 0);
	reticle();
	glPopMatrix();
	
	// Targets
	target1.drawTarget();
	target2.drawTarget();
	target3.drawTarget();
}

void checkAllHits()
{
	if(target1.checkHit(shot[0], shot[1]))
		target1.setAlpha(0.0);
	else if(target2.checkHit(shot[0], shot[1]))
		target2.setAlpha(0.0);
	else if(target3.checkHit(shot[0], shot[1]))
		target3.setAlpha(0.0);
}

void resetTargets()
{
	target1.setAlpha(1.0);
	target2.setAlpha(1.0);
	target3.setAlpha(1.0);
}