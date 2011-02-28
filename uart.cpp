/******************************* C SOURCE FILE ******************************
**
** Project : RS232 UART Library
** Filename : Uart.cpp
** Version : 1
** Date :  03 05 2005
**
*****************************************************************************
** 
** www.re-mastered.co.uk
** andy@re-mastered.co.uk
**
**	You are free to use this library in anyway you see fit. I accept no responsibility
**	for any damages or injury caused. No warranty is offered what so ever.
**	If you use this library i would like a mention, but this is not required,
**	you could just drop me a quick email :)
**
*****************************************************************************
** VERSION HISTORY:
** ----------------
** Version : 1.0
** Created by : Andrew Nickson		Date :  03 05 2005
** Description : Original version. 
**
****************************************************************************/

#include "UART.h"

DCB PortDCB; 
COMMTIMEOUTS CommTimeouts; 
HANDLE hPort; 

/*
void SerialTest()	//temp routine for testing.
{
	unsigned char data[10];
	data[0] = 0x01;
	data[1] = 0x02;
	data[2] = 0x03;
	data[3] = 0x04;
	WriteUart(data,4);
}
*/

/****************************************************************************
* SetupUart()
*
* This function initialises the serial port and opens it ready to send and 
* receive data.
*
* The default setup is:		(define in Uart.h)
*		COM1 9600,8,1,NOPARITY
*
* Usage for default setup:				SetupUart();		
* Or usage for specific parameters:		SetupUart("COM2",2400,8,1,NOPARITY);
*
*	Parity can be:			Bitsize can be:		
*		EVENPARITY				5 - 8
*		MARKPARITY
*		NOPARITY
*		ODDPARITY
*		SPACEPARITY
*
* Will return 0 if the function fails
******************************************************************************/
int SetupUart(char *Port,int baud,int Bitsize,int StopBits,int Parity)
{
	int STOPBITS;

	if(StopBits == 1)	STOPBITS = ONESTOPBIT;
//	if(StopBits == 1.5) STOPBITS = ONE5STOPBITS;
	if(StopBits == 2)	STOPBITS = TWOSTOPBITS;

	// Open the serial port. 
	hPort = CreateFile (TEXT(Port),						// Name of the port 
						GENERIC_READ | GENERIC_WRITE,   // Access (read-write) mode 
						0,                                  
						NULL,                             
						OPEN_EXISTING,                     
						0,                                 
						NULL);                             
             
	// If it fails to open the port, return 0. 
	if ( hPort == INVALID_HANDLE_VALUE ) 
	{ 
		//We failed to open!  
		return 0; 
	}   

	//Get the default port setting information. 
	GetCommState (hPort, &PortDCB); 
	// Change the settings. 
	PortDCB.BaudRate = baud;              // BAUD Rate
	PortDCB.ByteSize = Bitsize;           // Number of bits/byte, 5-8 
	PortDCB.Parity = Parity;              // 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = STOPBITS;          // StopBits 
	PortDCB.fNull = 0;					  // Allow NULL Receive bytes

	// Re-configure the port with the new DCB structure. 
	if (!SetCommState (hPort, &PortDCB)) 
	{ 
		// Could not create the read thread. 
		CloseHandle(hPort);   
		return 0; 
	} 

	// Retrieve the time-out parameters for all read and write operations 
	// on the port. 
	GetCommTimeouts (hPort, &CommTimeouts); 
	memset(&CommTimeouts, 0x00, sizeof(CommTimeouts)); 
	CommTimeouts.ReadIntervalTimeout = 10; 
	CommTimeouts.ReadTotalTimeoutConstant = 10; 
	CommTimeouts.WriteTotalTimeoutConstant = 10;     

	// Set the time-out parameters for all read and write operations on the port. 
	if (!SetCommTimeouts (hPort, &CommTimeouts)) 
	{ 
		// Could not create the read thread. 
		CloseHandle(hPort);  
		return 0; 
	} 

	// Clear the port of any existing data. 
	if(PurgeComm(hPort, PURGE_TXCLEAR | PURGE_RXCLEAR)==0) 
	{ 
		CloseHandle(hPort); 
		return 0; 
	} 

	return 1; //SERIAL SETUP OK
}

/****************************************************************************
* WriteUart()
*
* This function Writes data to the serial for receiving device
*
* Input: *buf - pointer to unsigned char array containing data
*		 len - length of data to be sent
*
* Usage:	WriteUart("HELLO COMS",strlen("HELLO COMS"));
*
* Will return 0 if the function fails
******************************************************************************/
int WriteUart(unsigned char *buf, int len)
{
	DWORD dwNumBytesWritten;

	WriteFile (hPort,				// Port handle 
		       buf,					// Pointer to the data to write 
			   len,					// Number of bytes to write 
			   &dwNumBytesWritten,	// Pointer to the number of bytes written 
			   NULL);				// Must be NULL 

	if(dwNumBytesWritten > 0) 
		return 1;					//Transmission was success
	
	else return 0;					//Error transmitting?
}

/****************************************************************************
* ReadUart()
*
* This function reads data from the serial port
*
* Input: *buf - pointer to unsigned char which will contain the received data 
*		 len  - size of buffer for receiving data
*
* Usage: ReadUart(indatabuffer,sizeof(indatabuffer));
*
* Will return 0 if no data available
******************************************************************************/
int ReadUart(unsigned char *buf, int len)
{
	BOOL ret;
	unsigned long retlen;
 
	ret = ReadFile(hPort,		// handle of file to read
					buf,		// pointer to buffer that receives data
					len,		// number of bytes to read
					&retlen,	// pointer to number of bytes read
					NULL		// pointer to structure for data
					);

	if(retlen > 0)				//If we have data
		return (int) retlen;	//return the length
    
	else return 0;				//else no data has been read
 }

/****************************************************************************
* CloseUart()
*
* Closes connection to the serial port
*
******************************************************************************/
int CloseUart()
{
	CloseHandle(hPort); 
	return 1;
}

