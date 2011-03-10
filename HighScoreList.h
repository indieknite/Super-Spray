/*
 *  HighScores.h
 *  LaserSpray
 */

#ifndef __HighScores__
#define __HighScores__

#include "ScoreItem.h"

// Object that stores a collection of ScoreItems in highest to lowest score order.
class HighScoreList
{
protected:
	int nameLength;
	int maxScores;
	int numEntries;
	ScoreItem* table;
	
public:
	HighScoreList(int NameLength, int MaxScores);
	
	void addScoreItem(ScoreItem newScore);
	inline char* getName(int pos) const { return table[pos].getName(); };
	inline int getScore(int pos) const { return table[pos].getScore(); };
	inline int isDefined(int pos) const { return table[pos].isDefined(); };
};

#endif