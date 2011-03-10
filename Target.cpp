/*
 *  Target.cpp
 *  LaserSpray
 */

#include "Target.h"

Target::Target(Vec3 pos, Vec3 col, int count)
{
	position = pos;
	color = col;
	counter = count;
	explosionType = false;
	
	
	hitStatus = false;
	alpha = 1.0;
	radius = 50.0f;
}

void Target::drawTarget()
{
	glPushMatrix();
	glTranslated(position.x, position.y, position.z);
	
	int sections = 128;
	
	// Radius
	radius = 50.0f;
	// Two * Pi
	GLfloat twoPi = 2.0f * 3.14159f;
	
	glLineWidth(3);
	glColor4d(color.x, color.y, color.z, alpha);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i <= sections; i++)
	{
		glVertex3f(radius * cos(i *  twoPi / sections), 
				   radius * sin(i * twoPi / sections), 0.0);
	}
	glEnd();
	glLineWidth(1);
	
	glPopMatrix();
}

bool Target::checkHit(int x, int y)
{
	float distance = sqrt(pow(position.x - x,2) + pow(position.y - y,2));
	if(distance <= (float)radius)
		return true;
	else
		return false;
}