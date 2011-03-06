/*
 *  ScoreItem.cpp
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 3/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
#include "ScoreItem.h"

#define NO_SCORE		0
#define EMPTY_CHAR		0

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