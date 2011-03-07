/*
 *  Target.h
 *  LaserSpray
 */

#include "Vec3.h"
//#include <gl/glut.h>	// Windows
#include <GLUT/glut.h>	// Mac OS X

class Target
{
	private:
	int counter;
	Vec3 position;
	Vec3 color;
	
	bool hitStatus;
	double alpha;
	GLfloat radius;
	
	public:
	Target(Vec3 pos = Vec3(0.0, 0.0, 0.0), Vec3 col = Vec3(0.3, 0.3, 0.3), int count = 10);
	
	inline void setHitStatus(bool newStatus) { hitStatus = newStatus; };
	inline void decreaseCounter() { --counter; };
	inline void setAlpha(double newAlpha) { alpha = newAlpha; };
	inline void setColor(Vec3 newColor) { color = newColor; };
	
	void drawTarget();
	bool checkHit(int x, int y);
	
	inline bool getStatus() { return hitStatus; };
	inline int getCounter() { return counter; };
	inline Vec3 getPosition() { return position; };
};