/*
 *  Graphics.cpp
 *  LaserSpray
 */

#include <iostream>
#include <gl/glut.h>	// windows
#include <iostream>		// windows
using namespace std;	// windows
//#include <GLUT/glut.h>	// mac OS X

#include "graphics.h"
#include "CalibrationScreen.h"
#include "StartScreen.h"
#include "PlayScreen.h"
#include "Target.h"
#include "CS112.h"
#include "FindRed.h"

// gluLookAt values
#define EYE				Vec3(0, 0, 5)
#define CENTER			Vec3(0, 0, 0)
#define UP				Vec3(0, 1, 0)

// glFrustum values
#define HW				0.6
#define ZNEAR			3.0
#define ZFAR			10.0

// Screen Ratio used to scale the images created correctly
#define WIDTH		(double)glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT		(double)glutGet(GLUT_SCREEN_HEIGHT)

// Define the current window state of the game.
#define STATE_CALIBRATE		0
#define STATE_START			1
#define STATE_PLAY			2

int* shot = new int[2];
bool isShotFired = false;

short gameState = 0;

// Display fuction used to redraw our graphics as our game runs.
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear frame buffer.
	
	switch(gameState)
	{
		case STATE_CALIBRATE:
			gameState = calibrateDisplay();
			glutPostRedisplay();
			break;
		case STATE_START:
			gameState = startDisplay();
			break;
		case STATE_PLAY:
			playDisplay();
			break;
	}
	
	isShotFired = false;
	
	glFlush();
	glutSwapBuffers();
}

void key_press(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 's':
		case 'S':
			if(gameState == STATE_CALIBRATE)
			{	
				shot = capturePoints();
				cout << shot[0] << "      " << shot[1] << endl;
			}	
			else
				calculateCoor();
			
			isShotFired = true;
			checkAllHits();
			glutPostRedisplay();
			break;
		case 'r':
		case 'R':
			resetTargets();
			glutPostRedisplay();
			break;
		case 'q':
        case 'Q':
			stopCamera();
            exit(0);
	}
}

void initializeGraphics(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("SuperSpray");
	glutFullScreen();
	glClearColor(0.0, 0.0, 0.0, 0.0); // clear window.

	// Various callback functions.
	glutDisplayFunc(display);
	glutKeyboardFunc(key_press);
	
	// Enable and set certain features within our OpenGL environment,
	// such as depth rendering and alpha.
	glEnable(GL_DEPTH_TEST); // Turn on depth buffering.
	glEnable(GL_BLEND);
	glFrontFace(GL_CCW);     // Make "front" faces counter-clockwise (True by default).
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	// Set up the viewing frustum.  Zooming will be performed here by changing the size
    // of the XY extent of the frustum.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-WIDTH/2.0, WIDTH/2.0, -HEIGHT/2.0, HEIGHT/2.0, -2.0, 2.0);
    glFrustum(-HW, HW, -HW, HW, ZNEAR, ZFAR);
	
	// Set up the viewing position.  Which we'll store as part of the MODELVIEW matrix.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE, CENTER, UP);
	
	// Give OpenGL control, which is never returned to this program.
    glutMainLoop();
}