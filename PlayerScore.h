/*
 *  PlayerScore.h
 *  LaserSpray
 */

#ifndef __PlayerScore__
#define __PlayerScore__

#include "ScoreItem.h"

void createNewScore();
ScoreItem getScoreItem();
int getScore();
void incrementScore(int addScore);
void setPlayerName(char* newName);

#endif