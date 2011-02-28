#include "uart.h"
#include "iostream"
#include "BluetoothGameData.h"
using namespace std;

// takes in an int and returns up to 3 bytes of data for a max value of 999,999 
// (99|99|99, all sent on seperate bytes)
// returns the passed in int broken up into an array of unsigned char's, ready to send over UART.
// dataPieces[] goes from most significant byte to least
unsigned char* convertForSend(int data)
{
	unsigned char* dataPieces = new unsigned char[4];

	// set the max allowed data transmitted to be 999999
	if (data > 999999)
	{
		data = 999999;
	}
	
	// initialize all bytes to zero.
	dataPieces[0] = '{'; // the start symbol of sending. ASCII value is 123 or 0x7B
	for (int i = 1; i < 4; i++)
	{
		dataPieces[i] = 0;
	}
	int tempData = data;
	
	// peel off the first digit
	unsigned char tempTens = unsigned char(tempData/100000);
	// remove first digit's data from temp
	tempData -= (tempTens * 100000);
	// peel off second digit
	unsigned char tempOnes = unsigned char(tempData/10000);
	// remove second digits data from temp
	tempData -= (tempOnes * 10000);
	// give the first digit its proper value for sending as a byte
	tempTens *= 10;
	// package up the two numbers into a byte for sending
	dataPieces[1] = tempTens + tempOnes;
	
	tempTens = unsigned char(tempData/1000);
	tempData -= (tempTens * 1000);
	tempOnes = unsigned char(tempData/100);
	tempData -= (tempOnes * 100);
	tempTens *= 10;
	dataPieces[2] = tempTens + tempOnes;
	
	tempTens = unsigned char(tempData/10);
	tempData -= (tempTens * 10);
	tempOnes = unsigned char(tempData);
	tempTens *= 10;
	dataPieces[3] = tempTens + tempOnes;
	
	/*
	cout << int(dataPieces[0]) << endl;
	cout << "First Bit: " << int(dataPieces[1]) << endl;
	cout << "Second Bit: " << int(dataPieces[2]) << endl;
	cout << "Third Bit: " << int(dataPieces[3]) << endl;
	*/

	return dataPieces;
}

// send the score in 3 bytes to microcontroller
// 3 bytes, 6 digits, max of 999,999
void sendScore(int score)
{
	unsigned char* scoreBuffer = convertForSend(score);
	WriteUart(scoreBuffer,sizeof(scoreBuffer));
}

// send the current ammo amount to the microcontroller
void sendAmmo(unsigned char ammo)
{
	unsigned char ammoBuffer[1];
	ammoBuffer[0] = ammo;
	WriteUart(ammoBuffer,sizeof(ammoBuffer));
}

// tell the microcontroller the game is starting.
// the start symbol is a capital 'S'
void sendGameStartFlag()
{
	unsigned char startBuffer[1];
	startBuffer[0] = 'S';
	WriteUart(startBuffer,sizeof(startBuffer));
}

// tell the microcontroller the game is over.
// the end symbol is a capital 'E'
void sendGameEndFlag()
{
	unsigned char endBuffer[1];
	endBuffer[0] = 'E';
	WriteUart(endBuffer,sizeof(endBuffer));
}

void processIncomingData(unsigned char data)
{
	if (data == 'P')
	{
		if (getAmmo() > 0)
		{
			setTriggerPull(true);
			decrementAmmo();
		}		
	}
	else
	{
		setTriggerPull(false);

		// reloading
		if (data == 'R')
		{
			incrementAmmo();
		}
		// gun is moving up and down
		else if (data == 'X')
		{
			setVerticalShake(true);
		}
		// gun is NOT moving up and down
		else if (data == 'W')
		{
			setVerticalShake(false);
		}
		// gun is moving left and right
		else if (data == 'Z')
		{
			setHorizontalShake(true);
		}
		// gun is NOTE moving left and right
		else if (data == 'X')
		{
			setHorizontalShake(false);
		}
	}
}

void initializeBluetoothCOMPort()
{
	SetupUart("COM5", 9600,8,1,NOPARITY);
}

void closeBluetoothCOMPort()
{
	CloseUart();
}

void pollForBluetoothData()
{
	int BytesRead;
    unsigned char inBuffer[20];

	BytesRead = ReadUart(inBuffer,sizeof(inBuffer));
		
	if(BytesRead > 0)
	{
		// for every piece of data in the buffer, process it
		for (int i = 0; i < BytesRead; i++)
		{
			processIncomingData(inBuffer[i]);
		}
	}	
}

/*****************************************************************************
This is basically what your timer function would look like, but instead of the
infinite while loop, it would be the timer block of code.  You need to call
initializeBluetoothCOMPORT() to open the access from the bluetooth to the computer,
and then for now, lets assume you need to set the MC's ammo to full and set the score to zero.
Then, inside what will be your timer function (the infinite while loop here) call
pollForBluetoothData().  This automatically checks if there is data to be read,
and if there is, it calls a method to process is it, and that updates all the necessary
data that you will then access via BluetoothGameData.h.  Lastly, close the bluetooth 
connection with closeBlutoothCOMPort().
*****************************************************************************/
int main()
{
	initializeBluetoothCOMPort();	
	setAmmo(getMaxAmmo());
	setScore(0);

	while(1)
	{		
		pollForBluetoothData();
	}
	closeBluetoothCOMPort();

	return 0;
}