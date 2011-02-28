#include "Bluetooth.h"

const unsigned char MAX_PSI = 32;
unsigned char currentPSI = MAX_PSI;
int score = 0;
bool triggerPulled = false;
bool verticalShake = false;
bool horizontalShake = false;

void startGameOnGun()
{
	sendGameStartFlag();
}

void endGameOnGun()
{
	sendGameEndFlag();
}

void setScore(int myScore)
{
	score = myScore;
	sendScore(score);
}

void setAmmo(unsigned char myAmmo)
{
	currentPSI = myAmmo;
	sendAmmo(currentPSI);
}

void incrementAmmo()
{
	currentPSI++;
	sendAmmo(currentPSI);
}

void decrementAmmo()
{
	currentPSI--;
	sendAmmo(currentPSI);
}

void setTriggerPull(bool triggerStatus)
{
	triggerPulled = triggerStatus;
}

void setVerticalShake(bool verticalShakeStatus)
{
	verticalShake = verticalShakeStatus;
}

void setHorizontalShake(bool horizontalShakeStatus)
{
	horizontalShake = horizontalShakeStatus;
}

int getScore()
{
	return score;
}

unsigned char getAmmo()
{
	return currentPSI;
}

unsigned char getMaxAmmo()
{
	return MAX_PSI;
}

bool triggerIsPulled()
{
	return triggerPulled;
}

bool isVerticalShake()
{
	return verticalShake;
}

bool isHorizontalShake()
{
	return horizontalShake;
}