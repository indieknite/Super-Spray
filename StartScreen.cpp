/*
 *  StartScreen.cpp
 *  Super Spray
 */

//#include <windows.h>		// Windows
//#include <stdlib.h>		// Windows
#include <unistd.h>			// Mac OS X
//#include <gl/glut.h>		// Windows
#include <GLUT/glut.h>		// Mac OS X

#include "SoundEffectsLibrary.h"
#include "DrawText.h"
#include "Target.h"
#include "HighScores.h"
#include "PlayerScore.h"

// Define the current window state of the game.
#define STATE_CALIBRATE		0
#define STATE_START			1
#define STATE_PLAY			2

// The original width and height, as defined by the computers resolution.
#define WIDTH				(double)glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT				(double)glutGet(GLUT_SCREEN_HEIGHT)

#define MAX_NUM_TARGETS		50

// If true, a shot was fired by the user and an appropriate action
// should be done by the game.
extern bool isShotFired;

Target splash[MAX_NUM_TARGETS];	// Holds all the targets to be displayed that are created.
int i = 0;

// Draws a box to display behind the title so that it can be read easier.
void drawBox(int xSize, int ySize)
{
	glColor4d(0.3, 0.3, 0.3, 0.6);
	glBegin(GL_QUADS);
	glVertex3d(xSize, ySize, 0.0);
	glVertex3d(xSize, -ySize, 0.0);
	glVertex3d(-xSize, -ySize, 0.0);
	glVertex3d(-xSize, ySize, 0.0);
	glEnd();
}

void drawTitle()
{
	glPushMatrix();
	glTranslated(-(WIDTH/5.20), 8, 0.0);
	drawBox(100,25);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1, 1, 1);
	glRasterPos2f(-(WIDTH/4), 0);
	drawSentence("SUPER SPRAY");
	glPopMatrix();
}

// HIGHSCORES ------------------------------------------------------------

void drawScore(int num, char* name, int score, float xPos, float yPos)
{
	char numString[10];
	
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
	glPushMatrix();
	glTranslated(WIDTH/4.10, HEIGHT/20, 0.0);
	drawBox(150,230);
	glPopMatrix();
	
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(WIDTH/5, HEIGHT/4);
	drawSentence("High Scores");
	
	glPushMatrix();
	glTranslated(WIDTH/5.8, HEIGHT/4.5, 0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(200.0, 0.0, 0.0);
	glEnd();
	glLineWidth(1);
	glPopMatrix();
	
	glPushMatrix();
	int yPos = HEIGHT/5.5;
	for(int i = 0; i < 10; i++)
	{
		drawScore((i+1), getPlayerName(i), getPlayerScore(i), 270, yPos);
		yPos = yPos - 35;
	}
	glPopMatrix();
}

// -----------------------------------------------------------------------

short startDisplay()
{
	// Disable Depth Test to enable alpha to be shown.
	glDisable(GL_DEPTH_TEST);
	
	// Creates the targets to show on the splash screen.
	// Their location on screen is determined randomly, as
	// well as their color.
	Target target = Target(Vec3(rand() % glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_SCREEN_WIDTH)/2,
						 rand() % glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_SCREEN_HEIGHT)/2, 0));
	target.setColor(Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX));
	splash[i] = target;
	i = (i + 1) % MAX_NUM_TARGETS;
	
	// Displays the targets on screen.
	for(int j = 0; j < MAX_NUM_TARGETS; j++)
	{
		splash[j].drawTarget();
		//Sleep(1);				// Windows
		usleep(1000);			// Mac OS X
	}
	
	drawTitle();
	
	drawHighScoreTable();
	
	// Re-enable Depth Test after alpha rendering is done.
	glEnable(GL_DEPTH_TEST);
	
	if(isShotFired)
	{
		stopSound1();
		createNewScore();
		return STATE_PLAY;
	}
	else
		return STATE_START;
}