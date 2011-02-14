//#include "stdafx.h"
#include <iostream>
//#include "cv.h"
//#include "highgui.h"
#include "OpenCV/cv.h"
#include "OpenCV/highgui.h"
#include "limits.h"

// Initialize capturing live feed from the camera
CvCapture* capture = 0;

void initializeCamera()
{
    capture = cvCaptureFromCAM(0);
	
    // Couldn't get a device? Throw an error and quit
    if(!capture)
    {
        printf("Could not initialize capturing...\n");
		exit(-2);
    }
}

void stopCamera()
{
	// We're done using the camera. Other applications can now use it
    cvReleaseCapture(&capture);
}

IplImage* GetThresholdedImage(IplImage* img)
{
	 // Convert the image into an HSV image
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);

	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	cvInRangeS(imgHSV, cvScalar(100, 100, 80), cvScalar(255, 255, 200), imgThreshed);

	cvReleaseImage(&imgHSV);
    return imgThreshed;
}

int* capturePoints()
{
	// Will hold a frame captured from the camera
	IplImage* frame = 0;
	frame = cvQueryFrame(capture);
	
	// If we couldn't grab a frame... quit
	if(!frame)
		return NULL;
	
	// Holds the yellow thresholded image (yellow = white, rest = black)
	IplImage* imgRedThresh = GetThresholdedImage(frame);
	
	// Calculate the moments to estimate the position of the ball
	CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
	cvMoments(imgRedThresh, moments, 1);
	
	// The actual moment values
	double moment10 = cvGetSpatialMoment(moments, 1, 0);
	double moment01 = cvGetSpatialMoment(moments, 0, 1);
	double area = cvGetCentralMoment(moments, 0, 0);
	
	// Will store the X and Y coordinate where the red dot is located
	static int xy[2] = {0,0};
	
	xy[0] = moment10/area; // X
	xy[1] = moment01/area; // Y
	
	// Release the thresholded image+moments
	cvReleaseImage(&imgRedThresh);
	delete moments;
	
	return xy;
}