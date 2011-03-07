#include <iostream>
//#include <cv.h>			// Windows
//#include <highgui.h>		// Windows
#include <OpenCV/cv.h>		// Mac OS X
#include <OpenCV/highgui.h>	// Mac OS X
#include <limits.h>

CvCapture* capture;			// Initialize capturing live feed from the camera

void stopCamera()
{
	// We're done using the camera. Other applications can now use it
    cvReleaseCapture(&capture);
}

void initializeCamera()
{
    capture = cvCaptureFromCAM(0);
	
    // Couldn't get a device? Throw an error and quit
    if(!capture)
    {
        printf("Could not initialize capturing...\n");
		stopCamera();
        exit(-2);
    }
}

IplImage* GetThresholdedImage(IplImage* img)
{
	// Creates a blank image where we will store our binary image.
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	// Images are handled using BGR color spectrum.
	// Creates a binary image where all color pixels that have
	// there values defined as
	//			Blue	--> 0	<= B < 50
	//			Green	-->	0	<= G < 50
	//			Red		--> 200	<= R < 255
	// are set to 1 and all others to 0.
	cvInRangeS(img, cvScalar(0, 0, 140), cvScalar(20, 20, 255), imgThreshed);
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
	
	// Holds the red thresholded image (yellow = white, rest = black)
	IplImage* imgRedThresh = GetThresholdedImage(frame);
	
	// Calculate the moments to estimate the position of the ball.
	CvMoments* moments = (CvMoments*)malloc(sizeof(CvMoments));
	cvMoments(imgRedThresh, moments, 1);
	
	// The actual moment values
	double moment10 = cvGetSpatialMoment(moments, 1, 0);
	double moment01 = cvGetSpatialMoment(moments, 0, 1);
	double area = cvGetCentralMoment(moments, 0, 0);
	
	// Will store the X and Y coordinate where the red dot is located
	static int xy[2] = {0,0};
	
	xy[0] = moment10/area; // X
	xy[1] = moment01/area; // Y
	
	// Release the images and moments
	cvReleaseImage(&imgRedThresh);
	delete moments;
	
	return xy;
}