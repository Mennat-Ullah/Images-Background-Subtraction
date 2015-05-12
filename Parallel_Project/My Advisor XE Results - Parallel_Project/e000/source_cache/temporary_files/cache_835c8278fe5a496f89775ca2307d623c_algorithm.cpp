#include <iostream>
#include <stdint.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui/highgui_c.h"
using std::cout;
using std::cin;
using std::endl;

using namespace cv;

void imhist(Mat image, int histogram[], int Number_of_Channels)
{

	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = 0;
	}

	// calculate the no of pixels for each intensity values
	for (int y = 0; y < image.rows; y++)
	for (int x = 0; x < image.cols; x++)
		histogram[(int)image.data[y*image.cols*Number_of_Channels + x*Number_of_Channels + 0]]++;  //0 for frist channal , luma represents the brightness in an image

}

void cumhist(int histogram[], int cumhistogram[])
{
	cumhistogram[0] = histogram[0];

	for (int i = 1; i < 256; i++)
	{
		cumhistogram[i] = histogram[i] + cumhistogram[i - 1];
	}
}

void histDisplay(int histogram[], const char* name)
{
	int hist[256];
	for (int i = 0; i < 256; i++)
	{
		hist[i] = histogram[i];
	}
	// draw the histograms
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	// find the maximum intensity element from histogram
	int max = hist[0];
	for (int i = 1; i < 256; i++){
		if (max < hist[i]){
			max = hist[i];
		}
	}

	// normalize the histogram between 0 and histImage.rows

	for (int i = 0; i < 256; i++){
		hist[i] = ((double)hist[i] / max)*histImage.rows;
	}


	// draw the intensity line for histogram
	for (int i = 0; i < 256; i++)
	{
		line(histImage, Point(bin_w*(i), hist_h),
			Point(bin_w*(i), hist_h - hist[i]),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	// display histogram
	namedWindow(name, CV_WINDOW_AUTOSIZE);
	imshow(name, histImage);
}



int main()
{
	// Load the image
	//Mat image = imread("test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat image = imread("INPUT//test33.jpg", CV_LOAD_IMAGE_UNCHANGED);
	/////////////////////////////////////////
	Mat img_hist_equalized;
	int tem=image.channels();
	
	cvtColor(image, img_hist_equalized, CV_BGR2YCrCb); //change the color image to grayscale image CV_GRAY2BGR
	uint8_t* pixelPtr = (uint8_t*)img_hist_equalized.data;
	int Number_of_Channels = img_hist_equalized.channels();  //pixelPtr[i*img.cols*Number_of_Channels + j*Number_of_Channels + 0];
		// Generate the histogram
		int histogram[256];
		imhist(img_hist_equalized, histogram, Number_of_Channels);
		////////////////////////////////////////////////
	

	// Caluculate the size of image
	int size = image.rows * image.cols;
	float alpha = 255.0 / size;

	// Calculate the probability of each intensity
	float PrRk[256];
	for (int i = 0; i < 256; i++)
	{
		PrRk[i] = (double)histogram[i] / size;
	}

	// Generate cumulative frequency histogram
	int cumhistogram[256];
	cumhist(histogram, cumhistogram);

	// Scale the histogram
	int Sk[256];
	for (int i = 0; i < 256; i++)
	{
		Sk[i] = cvRound((double)cumhistogram[i] * alpha);
	}


	// Generate the equlized histogram
	float PsSk[256];
	for (int i = 0; i < 256; i++)
	{
		PsSk[i] = 0;
	}

	for (int i = 0; i < 256; i++)
	{
		PsSk[Sk[i]] += PrRk[i];
	}

	int final[256];
	for (int i = 0; i < 256; i++)
		final[i] = cvRound(PsSk[i] * 255);


	// Generate the equlized image
	Mat new_image = img_hist_equalized.clone(); //copy the data

	for (int y = 0; y < image.rows; y++)
	for (int x = 0; x < image.cols; x++)
		new_image.data[y*image.cols*Number_of_Channels + x*Number_of_Channels + 0] = saturate_cast<uchar>(Sk[(int)((uint8_t*)img_hist_equalized.data[y*img_hist_equalized.cols*Number_of_Channels + x*Number_of_Channels + 0])]); //saturate_cast round value from 0..255

	// Display the original Image
	namedWindow("Original Image");
	imshow("Original Image", image);

	// Display the original Histogram
	histDisplay(histogram, "Original Histogram");

	// Display equilized image
	cvtColor(new_image, new_image, CV_YCrCb2BGR); //change the color image from YCrCb to BGR format (to display image properly)
	namedWindow("Equilized Image");
	imshow("Equilized Image", new_image);

	// Display the equilzed histogram
	histDisplay(final, "Equilized Histogram");

	waitKey();
	return 0;
}