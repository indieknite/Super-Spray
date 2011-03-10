/*
 *  PlayerScore.h
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 3/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PlayerScore__
#define __PlayerScore__

#include "ScoreItem.h"

void createNewScore();
ScoreItem getScoreItem();
int getScore();
void incrementScore(int addScore);
void setScoreName(char* newName);

#endif