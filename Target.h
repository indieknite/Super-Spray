/*
 *  Target.h
 *  Super Spray
 */

#ifndef __Target__
#define __Target__

#include "Vec3.h"
//#include <gl/glut.h>	// Windows
#include <GLUT/glut.h>	// Mac OS X

class Target
{
	private:
	int counter;
	bool explosionType;
	bool hitStatus;
	
	protected:
	Vec3 position;
	Vec3 color;
	GLfloat radius;
	float alpha;
	
	public:
	Target(Vec3 pos = Vec3(-1000.0, -1000.0, 0.0), Vec3 col = Vec3(0.3, 0.3, 0.3), int count = 60);
	
	inline void setHitStatus(bool newStatus) { hitStatus = newStatus; };
	inline void decreaseCounter() { --counter; };
	inline void setExplosionType(bool newType) { explosionType = newType; };
	inline void decreaseAlpha(float deltaAlpha) { if(alpha > 0) alpha -= deltaAlpha; };
	inline void setColor(Vec3 newColor) { color = newColor; };
	
	void drawTarget();
	bool checkHit(int x, int y);
	
	inline bool getStatus() { return hitStatus; };
	inline int getCounter() { return counter; };
	inline Vec3 getPosition() { return position; };
	inline bool getExplosionType() { return explosionType; };
	inline float getAlpha() { return alpha; };
};

#endif