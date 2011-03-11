/*
 *  highScores.cpp
 *  Super Spray
 */

#include "HighScoreList.h"

#define MAX_NUM_HIGHSCORES		10

// Creates a new high score table and initializes all values as empty.
HighScoreList::HighScoreList(int NameLength, int MaxScores)
{
	nameLength = NameLength;
	maxScores = MaxScores;
	numEntries = 0;

	table = new ScoreItem[maxScores];
	for(int i = 0; i < maxScores; i++)
	{
		table[i].changeNameSize(NameLength);
		table[i].setName("JH");
	}
}

bool HighScoreList::isScoreHighEnough(ScoreItem newScore)
{
	// Is the new entry a high score?
	if(numEntries == MAX_NUM_HIGHSCORES) // The array is full.
	{
		if(newScore.getScore() <= table[MAX_NUM_HIGHSCORES - 1].getScore())
			return false; // The new entry is not a high score in this case.
	}
	else
		numEntries++;
	
	return true;
}

void HighScoreList::addScoreItem(ScoreItem newScore)
{
	//Locate the place the new entry belongs.
	int i = numEntries - 1;
	for(; (i >= 1) && (newScore.getScore() > table[i-1].getScore()); i--)
		table[i] = table[i-1];
	table[i] = newScore;
}