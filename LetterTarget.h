/*
 *  LetterTarget.h
 *  Super Spray
 */

#ifndef __LetterTarget__
#define __LetterTarget__

#include "Vec3.h"
#include "Target.h"

class LetterTarget : public Target
{
	protected:
	char* letter;

	public:
	LetterTarget(Vec3 pos = Vec3(-1000.0f, -1000.0f, -1000.0f), Vec3 col = Vec3(0.3, 0.3, 0.3), char* character = "_");
	
	inline void setChar(char* newChar) { letter = newChar; };
	inline char* getChar() { return letter; };
};

#endif