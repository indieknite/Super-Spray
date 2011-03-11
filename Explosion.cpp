/*
 *  Explosion.cpp
 *  Super Spray
 */

//#include <gl/glut.h>		// Windows
#include <GLUT/glut.h>		// Mac OS X

#include "Vec3.h"

#define WIDTH		(double)glutGet(GLUT_SCREEN_WIDTH)

GLfloat explosionSize = 0.0f;
float alpha = 1.0f;

void drawExplosion(int x, int y)
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	int sections = 128;
	
	// Radius
	GLfloat radius = explosionSize;
	// Two * Pi
	GLfloat twoPi = 2.0f * 3.14159f;
	
	glColor4f(0.0f, 0.25f, 1.0f, alpha);
	glBegin(GL_TRIANGLE_FAN);
	for(int i = 0; i <= sections; i++)
	{
		glVertex3f(radius * cos(i *  twoPi / sections), 
				   radius * sin(i * twoPi / sections), 0.0);
	}
	glEnd();
	glPopMatrix();

	if(explosionSize < (WIDTH * 1.5))
	{
		explosionSize += 3.0f;
		glutPostRedisplay();
	}
	
}

bool decrementExplosionAlpha(float deltaAlpha)
{
	alpha -= deltaAlpha;
	
	if(alpha <= 0)
	{
		explosionSize = 0.0;
		alpha = 1.0f;
		
		return false;
	}
	
	return true;
}