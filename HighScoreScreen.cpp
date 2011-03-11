/*
 *  HighScoreScreen.cpp
 *  Super Spray
 */

#include <string>
//#include <gl/glut.h>		// Windows
#include <GLUT/glut.h>		// Mac OS X

#include "LetterTarget.h"
#include "HighScores.h"
#include "PlayerScore.h"
#include "DrawText.h"

#define WIDTH			(double)glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT			(double)glutGet(GLUT_SCREEN_HEIGHT)

// Define the current window state of the game.
#define STATE_START			1
#define STATE_HIGHSCORES	3

#define	KEYBOARD_VALUES		28

extern bool isShotFired;
extern int* shot;

LetterTarget letterTargets[KEYBOARD_VALUES];

std::string first = "_", second = "_", third = "_";

void initializeCharTargets()
{
	letterTargets[0] = LetterTarget(Vec3(-280,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "A");
	letterTargets[1] = LetterTarget(Vec3(-210,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "B");
	letterTargets[2] = LetterTarget(Vec3(-140,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "C");
	letterTargets[3] = LetterTarget(Vec3(-70,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "D");
	letterTargets[4] = LetterTarget(Vec3(0,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "E");
	letterTargets[5] = LetterTarget(Vec3(70,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "F");
	letterTargets[6] = LetterTarget(Vec3(140,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "G");
	letterTargets[7] = LetterTarget(Vec3(210,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "H");
	letterTargets[8] = LetterTarget(Vec3(280,0,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "I");
	letterTargets[9] = LetterTarget(Vec3(-280,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "J");
	letterTargets[10] = LetterTarget(Vec3(-210,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "K");
	letterTargets[11] = LetterTarget(Vec3(-140,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "L");
	letterTargets[12] = LetterTarget(Vec3(-70,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "M");
	letterTargets[13] = LetterTarget(Vec3(0,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "N");
	letterTargets[14] = LetterTarget(Vec3(70,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "O");
	letterTargets[15] = LetterTarget(Vec3(140,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "P");
	letterTargets[16] = LetterTarget(Vec3(210,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "Q");
	letterTargets[17] = LetterTarget(Vec3(280,-70,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "R");
	letterTargets[18] = LetterTarget(Vec3(-280,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "S");
	letterTargets[19] = LetterTarget(Vec3(-210,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "T");
	letterTargets[20] = LetterTarget(Vec3(-140,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "U");
	letterTargets[21] = LetterTarget(Vec3(-70,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "V");
	letterTargets[22] = LetterTarget(Vec3(0,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "W");
	letterTargets[23] = LetterTarget(Vec3(70,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "X");
	letterTargets[24] = LetterTarget(Vec3(140,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "Y");
	letterTargets[25] = LetterTarget(Vec3(210,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "Z");
	letterTargets[26] = LetterTarget(Vec3(280,-140,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), " ");
	letterTargets[27] = LetterTarget(Vec3(0,-210,0),Vec3(0, double(rand())/RAND_MAX, double(rand())/RAND_MAX), "DEL");
}

void drawCharTargets()
{
	for(int i = 0; i < KEYBOARD_VALUES; i++)
	{
		letterTargets[i].drawTarget();
		
		if(i == KEYBOARD_VALUES - 1)
			glRasterPos2f(letterTargets[i].getPosition().x - 23, letterTargets[i].getPosition().y - 8);
		else
			glRasterPos2f(letterTargets[i].getPosition().x - 8, letterTargets[i].getPosition().y - 8);
		
		drawSentence(letterTargets[i].getChar());
	}
}

void checkKeyboardTargets()
{
	for(int i = 0; i < KEYBOARD_VALUES; i++)
	{
		if(letterTargets[i].checkHit(shot[0], shot[1]))
		{
			if(i == 28)
			{
				if(third != "_")
					third = "_";
				else if(second != "_")
					second = "_";
				else
					first = "_";
			}
			else if(first == "_")
				first = letterTargets[i].getChar();
			else if(second == "_")
				second = letterTargets[i].getChar();
			else
				third = letterTargets[i].getChar();
		}
	}
}

int highScoreDisplay()
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-200, 200);
	drawSentence("Congratulations! Please enter your initials.");
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-50, 100);
	drawSentence(&first[0]);
	glRasterPos2f(0, 100);
	drawSentence(&second[0]);
	glRasterPos2f(50, 100);
	drawSentence(&third[0]);
	glPopMatrix();
	
	drawCharTargets();
	
	if((first == "_") || (second == "_") || (third == "_"))
		return STATE_HIGHSCORES;
	else
	{
		std::string combined = first + second + third;
		char name[combined.length()];
		for(int i=0;i<combined.length();i++)
			name[i]=(char)combined[i];
		
		setPlayerName(name);
		addNewHighScore(getScoreItem());
		
		first = second = third = "_";
		
		return STATE_START;
	}
}