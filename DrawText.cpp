/*
 *  DrawText.cpp
 *  Super Spray
 */

#include <string>
//#include <gl/glut.h>	// Windows
#include <GLUT/glut.h>	// Mac OS X

void drawSentence(char* str)
{
	for(int i = 0; i <= strlen(str); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}