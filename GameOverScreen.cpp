/*
 *  GameOverScreen.cpp
 *  Super Spray
 */

//#include <gl/glut.h>		// Windows
#include <GLUT/glut.h>		// Mac OS X

#include "DrawText.h"
#include "SoundEffectsLibrary.h"

extern bool isShotFired;

// Define the current window state of the game.
#define STATE_START			1
#define STATE_GAMEOVER		4

int gameOverDisplay()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-50, 0);
	drawSentence("GAME OVER.");
	glPopMatrix();
	
	if(isShotFired)
	{
		playSound1();
		return STATE_START;
	}
	else
		return STATE_GAMEOVER;
}