/*
 *  highScores.cpp
 *  LaserSpray
 */

//#include "stdafx.h"

#include "highScores.h"

// Initializes an empty ScoreItem with no name or score.
ScoreItem::ScoreItem()
{
	nameLength = 0;
	name = NULL;
	score = NO_SCORE;
}

// Initializes a ScoreItem with no name or score.
ScoreItem::ScoreItem(int NameLength)
{
	changeNameSize(NameLength);
	name[0] = EMPTY_CHAR;
	score = NO_SCORE;
}

// Deallocates the score name.
ScoreItem::~ScoreItem()
{
	if(name != NULL)
		free(name);
}

// Changes the amount of characters that can be used to spell the name of a Score Item.
void ScoreItem::changeNameSize(int NewNameLength)
{
	nameLength = NewNameLength;
	name = (char*) malloc (nameLength + 1);
}

// Changes the name that is associated with the ScoreItem's score.
void ScoreItem::setName(char* Name)
{
		if(name != NULL && Name != NULL)
		{
			strncpy(name, Name, nameLength);
			name[nameLength] = EMPTY_CHAR;
		}
}

// Checks if the ScoreItem has a defined name (not null) and score (greater than 0).
bool ScoreItem::isDefined()
{
	return (name != NULL && name[0] != EMPTY_CHAR);
}

// Creates a new high score table and initializes all values as empty.
HighScoreTable::HighScoreTable(int NameLength, int MaxScores)
{
	nameLength = NameLength;
	maxScores = MaxScores;
	numEntries = 0;

	table = new ScoreItem[maxScores];
	for(int i = 0; i < maxScores; i++)
		table[i].changeNameSize(NameLength);
}

// Deallocates the high score data array.
HighScoreTable::~HighScoreTable()
{
	delete(table);
}

void HighScoreTable::addScoreItem(ScoreItem newScore)
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