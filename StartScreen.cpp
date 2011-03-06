/*
 *  StartScreen.cpp
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 2/10/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

//#include <windows.h>	// Windows
//#include <stdlib.h>	// Windows
#include <unistd.h>		// Mac OS X
//#include <gl/glut.h>	// Windows
#include <GLUT/glut.h>	// mac OS X

#include "DrawText.h"
#include "Target.h"
#include "HighScoreList.h"

// Define the current window state of the game.
#define STATE_CALIBRATE		0
#define STATE_START			1
#define STATE_PLAY			2

// If true, a shot was fired by the user and an appropriate action
// should be done by the game.
extern bool isShotFired;

// The total amount of targets to display on the start screen.
const int maxNumTargets = 50;

Target target;					// Placeholder for changing the values of the created target.
Target splash[maxNumTargets];	// Holds all the targets to be displayed that are created.
int i = 0;

// Objects that handle how scores are handled and stored when they are high enough
// to be displayed on the main start page.
HighScoreList table(3,10);
ScoreItem playerScore;

char numString[20];
int yPos;

// Draws a box to display behind the title so that it can be read easier.
void drawBox()
{
	glColor4d(0.3, 0.3, 0.3, 0.6);
	glBegin(GL_QUADS);
	glVertex3d(100.0, 25.0, 0.0);
	glVertex3d(100.0, -25.0, 0.0);
	glVertex3d(-100.0, -25.0, 0.0);
	glVertex3d(-100.0, 25.0, 0.0);
	glEnd();
}

void drawScore(int num, char* name, int score, float xPos, float yPos)
{
	sprintf(numString, "%d.", num);
	glRasterPos2f(xPos, yPos);
	drawSentence(numString);
	
	glRasterPos2f(xPos+60, yPos);
	drawSentence(name);
	
	sprintf(numString, "%d", score);
	glRasterPos2f(xPos+140, yPos);
	drawSentence(numString);
}

void drawHighScoreTable()
{
	glRasterPos2f(275, 300);
	drawSentence("High Scores");
	
	glPushMatrix();
	glTranslated(235, 290, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(200.0, 0.0, 0.0);
	glEnd();
	glLineWidth(1);
	glPopMatrix();
	
	yPos = 265;
	for(int i = 0; i < 10; i++)
	{
		drawScore((i+1), table.getName(i), table.getScore(i), 250, yPos);
		yPos = yPos - 35;
	}
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
		//Sleep(1);				// Windows
		usleep(400);			// Mac OS X
		glutPostRedisplay();
	}
	
	glPushMatrix();
	glTranslated(-195, 8.0, 0.0);
	drawBox();
	glPopMatrix();
	
	glColor3f(1, 1, 1);
	glRasterPos2f(-275, 0);
	drawSentence("SUPER SPRAY");
	
	drawHighScoreTable();
	
	// Re-enable Depth Test after alpha rendering is done.
	glEnable(GL_DEPTH_TEST);
	
	if(isShotFired)
	{
		playerScore = ScoreItem(3);
		return STATE_PLAY;
	}
	else
		return STATE_START;
}