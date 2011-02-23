#ifndef __BluetoothGameData__
#define __BluetoothGameData__

// send start signal to MC and updates its values
// resets the LCD, sets PSI to full, score to zero
void startGameOnGun(void);

// doesn't do anything yet on MC
void endGameOnGun(void);

// updates the score, and sends the new score to the MC
void setScore(int);

// updates the ammo, and sends the new ammo to the MC
void setAmmo(unsigned char);

// ammo increments, send to MC
void incrementAmmo(void);

// ammo decrememnts, send to MC
void decrementAmmo(void);

// get the current score
int getScore(void);

// get the current PSI
unsigned char getAmmo(void);

// get the max ammo
unsigned char getMaxAmmo(void);

// check if the trigger is pulled
bool triggerPulled(void);

//****************ADRIAN YOU SHOULDN'T NEED TO USE WHAT IS BELOW******************

// sets trigger pull to true
void setTriggerPull(bool);

// set the vertical shake
void setVerticalShake(bool);

// set the horizontal shake
void setHorizontalShake(bool);

#endif