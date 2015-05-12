//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//#include <stdint.h>
//#include <omp.h>
//#include <ctime>
//#include <sstream>
//#include <string>
//#include "opencv2/highgui/highgui_c.h"
//#include "opencv2/imgproc/imgproc.hpp"
//using namespace cv;
//using namespace std;
//
//const int pic_num = 50;
//
//int main(int argc, const char** argv)
//{
//	Mat img_hist_equalized[pic_num + 1];
//	uint8_t** pixelPtr;
//	pixelPtr = new uint8_t*[pic_num + 1];
//	int Number_of_Channels = 0, Cols = 0, Rows = 0;
//	stringstream sin;
//	string s;
//
//	double start = clock();
//
//	for (int i = 0; i < pic_num; i++)
//		sin << i + 1 << endl;
//	sin << pic_num << endl;
//
//	for (int i = 0; i < pic_num; i++)
//	{
//		sin >> s;
//		img_hist_equalized[i] = imread("img//" + s + ".jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
//
//		if (img_hist_equalized[i].empty()) //check whether the image is loaded or not
//		{
//			cout << "Error : Image cannot be loaded..!!" << endl;
//			//system("pause"); //wait for a key press
//			return -1;
//		}
//		pixelPtr[i] = (uint8_t*)img_hist_equalized[i].data;
//	}
//	unsigned int sz = img_hist_equalized[pic_num - 1].cols*img_hist_equalized[pic_num - 1].rows*img_hist_equalized[pic_num - 1].channels();
//
//	unsigned long long* sums = new unsigned long long[sz];
//	for (int i = 0; i < sz; i++)
//		sums[i] = 0;
//
//	for (int k = 0; k < pic_num ; k++)
//	for (int i = 0; i < img_hist_equalized[k].cols*img_hist_equalized[k].rows*img_hist_equalized[k].channels() && i <sz; i++)
//		sums[i] += pixelPtr[k][i];
//
//
//	for (int i = 0; i < sz; i++)
//		sums[i] /= pic_num;
//
//	for (int i = 0; i < pic_num; i++)
//	for (int j = 0; j < sz; j++)
//		pixelPtr[i][j] = (sums[j] > pixelPtr[i][j] ? 0 : (pixelPtr[i][j] - sums[j]));
//
//	double end = clock();
//	printf("Using %d images the time is %lf \n", pic_num, (end - start) / double(CLOCKS_PER_SEC));
//
//	namedWindow("imagenew", CV_WINDOW_AUTOSIZE);
//	imshow("imagenew", img_hist_equalized[pic_num - 1]);
//
//	vector<int> compression_params;
//	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
//	compression_params.push_back(90);
//
//	sin << (end - start) / double(CLOCKS_PER_SEC) << endl;
//	sin >> s;
//	string T;
//	sin >> T;
//
//	stringstream fin;
//	for (int i = 0; i < pic_num; i++)
//		fin << i + 1 << endl;
//	string S;
//	for (int i = 0; i < pic_num; i++)
//	{
//		fin >> S;
//		bool ok = imwrite("OUTPUT\\" + S + "_res_" + s + "_" + T + "_omp2.jpg", img_hist_equalized[i], compression_params);
//		if (!ok)
//			cout << "can't write image" << endl;
//	}
//
//	waitKey();
//	return 0;
//}