/*
 *  HighScores.h
 *  Super Spray
 */

#ifndef	__HighScores__
#define	__HighScores__

#include "ScoreItem.h"

char* getPlayerName(int pos);
int getPlayerScore(int pos);
bool checkNewScore(ScoreItem newScore);
void addNewHighScore(ScoreItem newScore);

#endif