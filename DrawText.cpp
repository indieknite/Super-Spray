/*
 *  DrawText.cpp
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 2/16/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
//#include <GLUT/glut.h>	// MAC OS X
#include <gl/glut.h>		// WINDOWS

#include "DrawText.h"

void drawSentence(char* str)
{
	for(int i = 0; i <= strlen(str); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}