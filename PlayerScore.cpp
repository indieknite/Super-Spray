/*
 *  PlayerScore.cpp
 *  Super Spray
 *
 *  Created by Adrian Guzman on 3/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
//#include <gl/glut.h>		// Windows
#include <GLUT/glut.h>		// Mac OS X

#include "PlayerScore.h"
#include "DrawText.h"

// The original width and height, as defined by the computers resolution.
#define WIDTH				(double)glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT				(double)glutGet(GLUT_SCREEN_HEIGHT)

ScoreItem playerScore(3);

void createNewScore()
{
	playerScore = ScoreItem(3);
}

ScoreItem getScoreItem()
{
	return playerScore;
}

int getScore()
{
	return playerScore.getScore();
}

void incrementScore(int addScore)
{
	playerScore.incrementScore(addScore);
}

void setPlayerName(char* newName)
{
	playerScore.setName(newName);
}