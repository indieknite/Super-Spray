#ifndef __Bluetooth__
#define __Bluetooth__


// call this ONE TIME to set up the connection for bluetooth
// in my example it is called in MAIN
void initializeBluetoothCOMPort(void);

// call this when you are FINISHED with bluetooth, this closes
// the connection.  Should be called right before the program
// exits, along with the method to close the camera for OpenCV.
void closeBluetoothCOMPort(void);

// The heart and soul of the bluetooth transmission.  Call this
// method repeatedly in a timer function.  This checks to see
// if there is data to be read.  If there is, it processes it
// and updates all local data variables.  They can then
// be read out via methods in BluetoothGameData.h
void pollForBluetoothData(void);






/***************************************************
THERE SHOULD BE NO NEED TO CALL THESE DIRECTLY.
USE THE SET METHODS IN BluetoothGameData.h INSTEAD
****************************************************/
void sendScore(int);
void sendAmmo(unsigned char);
void sendGameStartFlag();
void sendGameEndFlag();

#endif