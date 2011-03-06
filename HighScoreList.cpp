/*
 *  highScores.cpp
 *  LaserSpray
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

// Deallocates the high score data array.
HighScoreList::~HighScoreList()
{
	delete(table);
}

void HighScoreList::addScoreItem(ScoreItem newScore)
{
	// Is the new entry a high score?
	if(numEntries == MAX_NUM_HIGHSCORES) // The array is full.
	{
		if(newScore.getScore() <= table[MAX_NUM_HIGHSCORES - 1].getScore())
			return; // The new entry is not a high score in this case.
	}
	else // The array is not full.
		numEntries++;
	//Locate the place the new entry belongs.
	int i = numEntries - 1;
	for(; (i >= 1) && (newScore.getScore() > table[i-1].getScore()); i--)
		table[i] = table[i-1];
	table[i] = newScore;
}