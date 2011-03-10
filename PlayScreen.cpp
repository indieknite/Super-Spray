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

#include "PlayScreen.h"
#include "SoundEffectsLibrary.h"
#include "DrawText.h"
#include "Target.h"
#include "PlayerScore.h"
#include "SessionTime.h"
#include "Explosion.h"

// Define the current window state of the game.
#define STATE_START			1
#define STATE_PLAY			2

#define MAX_NUM_TARGETS		100

#define WIDTH				(double)glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT				(double)glutGet(GLUT_SCREEN_HEIGHT)

extern int* shot;
extern bool isShotFired;

float spawnCounter= 0.0f;
float spawnTime = 5.0f;
Target newTarget;					// Used to create new targets to add to the pull of new targets.
Target targets[MAX_NUM_TARGETS];	// Holds all the targets to be displayed that are created.
int cur = 0;

bool explosionFlag = false;
int expX;
int expY;

int shotDuration = 0;

// Draws the reticle -------------------------------------------------------------------------

void drawBlueCircle(float radius, float x, float y, float z = 0)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	
	int sections = 128;
	
	// Two * Pi
	GLfloat twoPi = 2.0f * 3.14159f;
	
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	for(int i = 0; i <= sections; i++)
	{
		glVertex3f(radius * cos(i *  twoPi / sections), 
				   radius * sin(i * twoPi / sections), 0.0);
	}
	glEnd();
	
	glPopMatrix();
}

void reticle()
{
	glPushMatrix();
	glTranslatef(shot[0], shot[1], 0.0f);
	drawBlueCircle(rand()/(RAND_MAX/5),rand()/(RAND_MAX/10),rand()/(RAND_MAX/10));
	drawBlueCircle(rand()/(RAND_MAX/5),rand()/(RAND_MAX/10),rand()/(RAND_MAX/10));
	
	drawBlueCircle(rand()/(RAND_MAX/5),-rand()/(RAND_MAX/10),rand()/(RAND_MAX/10));
	drawBlueCircle(rand()/(RAND_MAX/5),-rand()/(RAND_MAX/10),rand()/(RAND_MAX/10));
	
	drawBlueCircle(rand()/(RAND_MAX/5),rand()/(RAND_MAX/10),-rand()/(RAND_MAX/10));
	drawBlueCircle(rand()/(RAND_MAX/5),rand()/(RAND_MAX/10),-rand()/(RAND_MAX/10));
	
	drawBlueCircle(rand()/(RAND_MAX/5),-rand()/(RAND_MAX/10),-rand()/(RAND_MAX/10));
	drawBlueCircle(rand()/(RAND_MAX/5),-rand()/(RAND_MAX/10),-rand()/(RAND_MAX/10));
	glPopMatrix();
}

// -------------------------------------------------------------------------------------------

// Time, Score, and Ammo ---------------------------------------------------------------------

void drawTime()
{
	char timeString[30];
	glPushMatrix();
	sprintf(timeString, "Time Left: %f", getTime());
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(WIDTH/2.59, HEIGHT/2.1);
	drawSentence(timeString);
	glPopMatrix();
}

void drawScore()
{
	char scoreString[15];
	glPushMatrix();
	sprintf(scoreString, "Score: %u", getScore());
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-WIDTH/2, HEIGHT/2.1);
	drawSentence(scoreString);
	glPopMatrix();
}

void drawAmmo()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-WIDTH/2, -HEIGHT/2.1);
	drawSentence("Ammo: ");
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glRasterPos2f(-WIDTH/2.25, -HEIGHT/2.1);
	for(int i = 0; i < 16/* AMMO AMOUNT */; i++)
		drawSentence("<>");
	glPopMatrix();
}

// -------------------------------------------------------------------------------------------

// Manage the targets ------------------------------------------------------------------------

void addTarget()
{
	newTarget = Target(Vec3(rand() % glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_SCREEN_WIDTH)/2,
						 rand() % glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_SCREEN_HEIGHT)/2, 0));
	
	if((double(rand())/RAND_MAX) > .9)
	{
		newTarget.setExplosionType(true);
		newTarget.setColor(Vec3(1.0f,1.0f,0.0f));
	}
	else
	{
		newTarget.setColor(Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX));
	}
	
	targets[cur] = newTarget;
	cur = (cur + 1) % MAX_NUM_TARGETS;
}

void drawTargets()
{
	if(spawnCounter <= 0)
	{
		addTarget();
		spawnCounter = spawnTime;
	}
	else
		spawnCounter -= 0.3;

	for(int j = 0; j < MAX_NUM_TARGETS; j++)
	{
		if(!targets[j].getStatus() && targets[j].getCounter() > 0)
			targets[j].drawTarget();
	}
}

void checkAllHits()
{
	for(int i = 0; i < MAX_NUM_TARGETS; i++)
	{
		if(!targets[i].getStatus() && (targets[i].getCounter() > 0) && targets[i].checkHit(shot[0], shot[1]))
		{
			targets[i].decreaseAlpha(0.34);
			
			if(targets[i].getAlpha() < 0)
			{
				targets[i].setHitStatus(true);
				incrementScore(100);
			}
		}
	}
}

void setSpawnTime()
{
	if(getTime() < 5.0f)
		spawnTime = 0.3f;
	else if(getTime() < 10.0f)
		spawnTime = 0.6f;
	else if(getTime() < 20.0f)
		spawnTime = 1.2f;
	else if(getTime() < 30.0f)
		spawnTime = 2.4f;
	else if(getTime() < 40.0f)
		spawnTime = 4.8f;
	else
		spawnTime = 6.0f;
}

void decreaseTargetTimeOnScreen()
{
	for(int i = 0; i < MAX_NUM_TARGETS; i++)
	{
		targets[i].decreaseCounter();
		
		if((targets[i].getCounter() <= 0) && (targets[i].getExplosionType() == true) && !explosionFlag)
		{
			explosionFlag = true;
			Vec3 pos = targets[i].getPosition();
			expX = pos.x;
			expY = pos.y;
		}
	}
}

void setExplosionFlag(bool newFlag)
{
	explosionFlag = newFlag;
}

// -------------------------------------------------------------------------------------------

short playDisplay()
{
	glDisable(GL_DEPTH_TEST);
	
	setSpawnTime();
	
	drawTargets();
	
	drawTime();
	drawScore();
	drawAmmo();
	
	if(isShotFired)
		shotDuration = 5;
	if(shotDuration > 0)
	{
		reticle();
		shotDuration--;
	}
	
	if(explosionFlag)
	{
		glPushMatrix();
		glTranslatef(expX, expY, 0);
		drawExplosion(0, 0);
		glPopMatrix();
	}
	
	glEnable(GL_DEPTH_TEST);
	
	if(getTime() > 0)
	{
		return STATE_PLAY;
	}
	else
	{
		playSound1();
		return STATE_START;
	}
}