/*
 *  HighScores.cpp
 *  Super Spray
 */

#include "HighScoreList.h"

HighScoreList table(3,10);

char* getPlayerName(int pos)
{
	return table.getName(pos);
}

int getPlayerScore(int pos)
{
	return table.getScore(pos);
}

bool checkNewScore(ScoreItem newScore)
{
	return table.isScoreHighEnough(newScore);
}

void addNewHighScore(ScoreItem newScore)
{
	table.addScoreItem(newScore);
}