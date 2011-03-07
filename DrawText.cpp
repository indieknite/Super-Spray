/*
 *  DrawText.cpp
 *  LaserSpray
 *
 *  Created by Adrian Guzman on 2/16/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
//#include <gl/glut.h>	// Windows
#include <GLUT/glut.h>	// Mac OS X

#include "DrawText.h"

void drawSentence(char* str)
{
	for(int i = 0; i <= strlen(str); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}