/*
 *  CalibrationScreen.cpp
 *  LaserSpray
 */

#include <stdlib.h>		// windows
#include <gl/glut.h>	// windows
#include <iostream>		// windows
using namespace std;	// windows
//#include <GLUT/glut.h>	// mac OS X
#include <limits.h>

#include "DrawText.h"
#include "FindRed.h"

// The original width and height, as defined by the computers resolution.
#define WIDTH				(double)glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT				(double)glutGet(GLUT_SCREEN_HEIGHT)

// Define the current window state of the game. 
#define STATE_CALIBRATE		0
#define STATE_START			1

// Store the location of a shot and whether a shot was fired.
// The main shooting function is defined here.
extern int* shot;
extern bool isShotFired;

// Values used to help calibrate the screen.
double xLeft = -1, xRight = -1, yUp = -1, yDown = -1;

// Defines the points used to draw an arrow.
void arrow()
{
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex3d(0.0, 50.0, 0.0);
	glVertex3d(50.0, 0.0, 0.0);
	glVertex3d(25.0, 0.0, 0.0);
	glVertex3d(25.0, -50.0, 0.0);
	glVertex3d(-25.0, -50.0, 0.0);
	glVertex3d(-25.0, 0.0, 0.0);
	glVertex3d(-50.0, 0.0, 0.0);
	glEnd();
	glLineWidth(1);
}

// Moves the arrow to the designated location defined by xMove, yMove, and rotate.
void moveArrow(int xOn, int yOn, int xMove, int yMove, int rotate)
{
	glPushMatrix();
	glTranslated(xOn * (WIDTH/2 + xMove), yOn * (HEIGHT/2 + yMove), 0.0);
	glRotated(rotate, 0, 0, 1);
	arrow();
	glPopMatrix();
}

// Called when if moving from the start screen back the to calibrating screen to recalculate the values of the corners.
void resetCalibration()
{
	xLeft = xRight = yUp = yDown = -1;
}

// Changes the point where the laser is picked up from webcam coordinates to the actual coordinates used by the glOrtho.
void calculateCoor()
{
	shot = capturePoints();
	
	shot[0] = (((shot[0] - xLeft) / (xRight - xLeft)) * WIDTH) - WIDTH;
	// invert the y axis...
	shot[1] = -1 * ((((shot[1] - yUp) / (yDown - yUp)) * HEIGHT) - HEIGHT);

	cout << shot[0] << "      " << shot[1] << endl;
}

// Main display function for the calibration screen. Will grab the values located
// at the corners of the display on the projector and use it to calibrate the
// actual screen width and height that will be used in our game.
short calibrateDisplay()
{
	// Draws the text on screen letting the player know to aim at the tips of the
	// arrows in order to set the calibrate values.
	glPushMatrix();
	glRasterPos2f(-275, 0);
	drawSentence("Point and shoot the tips of the arrows to calibrate screen.");
	glPopMatrix();
	
	// Gets the value of the left corner.
	if(xLeft < 0)
	{
		moveArrow(1, 0, -WIDTH+55, 0, 90);
		if(isShotFired)
		{
			xLeft = shot[0];
			cout << "xLeft " << xLeft << endl;
		}
	}
	// The right corner.
	else if(xRight < 0)
	{
		moveArrow(1, 0, -55, 0, -90);
		if(isShotFired)
		{
			xRight = shot[0];
			cout << "xRight " << xRight << endl;
		}
	}
	// The top corner.
	else if(yUp < 0)
	{
		moveArrow(0, 1, 0, -55, 0);
		if(isShotFired)
		{
			yUp = shot[1];
			cout << "yUp " << yUp << endl;
		}
	}
	// The bottom corner.
	else if(yDown < 0)
	{
		moveArrow(0, 1, 0, -HEIGHT+55, 180);
		if(isShotFired)
		{
			yDown = shot[1];
			cout << "yDown " << yDown << endl;
		}
	}
	// Calibration is done. Move on to the start screen.
	else
	{
		// fix the potential "flipping" of the image from our camera.
		int temp = 0;
		if (xLeft > xRight)
		{
			temp = xLeft;
			xLeft = xRight;
			xRight = temp;
		}
		if (yUp > yDown)
		{
			temp = yUp;
			yUp = yDown;
			yDown = temp;
		}
		cout << "**************************" << endl;
		cout << "xLeft " << xLeft << endl;
		cout << "xRight " << xRight << endl;
		cout << "yUp " << yUp << endl;
		cout << "yDown " << yDown << endl;
		cout << "**************************" << endl;

		return STATE_START;
	}
	
	isShotFired = false;
	return STATE_CALIBRATE;
}