/*
 *  SoundEffectsLibrary.cpp
 *  Super Spray
 */

#include "/Developer/FMOD Programmers API Mac/api/inc/fmod.hpp"
#include "/Developer/FMOD Programmers API Mac/api/inc/fmod_errors.h"
#include <iostream>

FMOD::System	*globalSystem;
FMOD::Sound		*sound1, *sound2, *sound3, *sound4, *sound5;
FMOD::Channel	*startSong;
FMOD_RESULT		result;

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-3);
    }
}

void playSound1()
{
	result = globalSystem->playSound(FMOD_CHANNEL_FREE, sound1, 0, &startSong);
	ERRCHECK(result);
}

void stopSound1()
{
	startSong->setMute(true);
}

void initializeSound()
{
	FMOD::System     *system;
    unsigned int      version;
	
	result = FMOD::System_Create(&system);
    ERRCHECK(result);
	
    result = system->getVersion(&version);
    ERRCHECK(result);
	
	if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        exit(-3);
    }
	
	result = system->init(32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);
	
	result = system->createSound("/Users/adrtwin/Music/What You Know (Mustang Remix).mp3", FMOD_SOFTWARE, 0, &sound1);
    ERRCHECK(result);
	
	
	
	/*
	result = system->createSound("CALIBRATING", FMOD_SOFTWARE, 0, &sound2);
    ERRCHECK(result);
	
    result = system->createSound("SHOT", FMOD_SOFTWARE, 0, &sound3);
    ERRCHECK(result);
	
    result = system->createSound("SHOT_NO_AMMO", FMOD_SOFTWARE, 0, &sound4);
    ERRCHECK(result);
	
	result = system->createSound("RELOADING", FMOD_SOFTWARE, 0, &sound5);
    ERRCHECK(result);
	*/
	globalSystem = system;
}

void releaseSounds()
{
	result = sound1->release();
    ERRCHECK(result);
    /*
	result = sound2->release();
    ERRCHECK(result);
    result = sound3->release();
    ERRCHECK(result);
    result = sound4->release();
    ERRCHECK(result);
	result = sound5->release();
    ERRCHECK(result);
	 */
}