/*
 *  LetterTarget.cpp
 *  Super Spray
 */

#include "LetterTarget.h"

LetterTarget::LetterTarget(Vec3 pos, Vec3 col, char* character)
{
	position = pos;
	color = col;
	letter = character;
	
	radius = 30.0f;
	alpha = 1.0f;
}