/*
 *  Main.cpp
 *  Super Spray
 */

#include "graphics.h"
#include "findRed.h"
#include "SoundEffectsLibrary.h"

int main (int argc, char** argv)
{
	initializeCamera();
	initializeSound();
	initializeGraphics(argc, argv);
	return 0;
}