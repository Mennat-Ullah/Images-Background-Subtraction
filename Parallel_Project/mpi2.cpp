//#undef SEEK_SET
//#include <mpi.h>
//#include <omp.h>
//#include <stdio.h>
//#include <iostream>
//#include <stdint.h>
//#include <ctime>
//#include <sstream>
//#include <string>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/highgui/highgui_c.h"
//#include "opencv2/imgproc/imgproc.hpp"
//using namespace cv;
//using namespace std;
//
//const int pic_num = 5;
//
//int main(int argc, char** argv)
//{
//	MPI::Init(argc, argv);
//
//	int id = MPI::COMM_WORLD.Get_rank();
//	int Psz = MPI::COMM_WORLD.Get_size();
//	int P_cnt = pic_num / Psz + (pic_num % Psz > 0 ? 1 : 0);
//
//	Mat img_hist_equalized[pic_num + 1];
//	uint8_t** pixelPtr;
//	pixelPtr = new uint8_t*[pic_num + 1];
//	int Number_of_Channels = 0, Cols = 0, Rows = 0;
//	stringstream sin;
//	string s;
//	int sz;
//
//	double start = clock();
//
//
//	// -- if we load some of img:
//	//cout << "sin = ";
//	for (int i = (id*P_cnt); i < ((id *P_cnt) + P_cnt) && i < pic_num; i++)
//	{
//		sin << i + 1 << endl;
//		//cout << i + 1 << " ";
//	}
//	//cout << endl;
//
//	//=== reading the images
//	// -- if load all img :
//	//for (int i = 0; i < pic_num; i++)
//	//sin << i + 1 << endl;
//	//sin << pic_num << endl;
//
//	for (int i = 0; i < P_cnt; i++)
//	{
//		sin >> s;
//		img_hist_equalized[i] = imread("images\\" + s + ".jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
//
//		if (img_hist_equalized[i].empty()) //check whether the image is loaded or not
//		{
//			cout << id << " Error : Image cannot be loaded..!! " << s << endl;
//			//system("pause"); //wait for a key press
//			return -1;
//		}
//		pixelPtr[i] = (uint8_t*)img_hist_equalized[i].data;
//	}
//	//==end reading the images
//
//	cout << "done load \n";
//	sz = img_hist_equalized[0].cols*img_hist_equalized[0].rows*img_hist_equalized[0].channels();
//
//
//	//======== back ground subtraction
//	int* sums = new int[sz];
//	for (int i = 0; i < P_cnt; i++)
//		sums[i] = 0;
//
//	// -- here if we load some of img
//	for (int k = 0; k < P_cnt; k++)
//		//for (int k = (id*P_cnt); k < ((id *P_cnt) + P_cnt) && k < pic_num; k++) // if we load all img than use some of them
//	for (int i = 0; i < sz; i++)
//		sums[i] += pixelPtr[k][i];
//
//	cout << id << " now gather \n";
//	//gathering the data
//	int* Rsums = new int[sz];
//	//-- first we can use Gather :
//	//MPI::COMM_WORLD.Gather(&sums, sz , MPI::INT , &Rsums, sz , MPI::INT, 0);
//	// -- or use Reduce :
//	//MPI::COMM_WORLD.Reduce(&sums , &Rsums , sz , MPI::INT , MPI_SUM , 0);
//	// -- or use send and recv :
//	if (!id)
//		MPI::COMM_WORLD.Isend(&sums, sz, MPI::INT, 0, 0);
//
//	if (id == 0)
//	{
//		for (int i = 1; i < Psz; i++)
//		{
//			MPI::COMM_WORLD.Irecv(&Rsums + (i*sz), sz, MPI::INT, i, 0);
//		}
//
//		//	//== dividing the results
//		for (int j = 0; j < sz; ++j)
//		{
//			for (int i = 1; i < Psz; i++)
//				Rsums[j] += Rsums[j + (i*sz)];
//
//			pixelPtr[0][j] = Rsums[j] / pic_num;
//		}
//
//		//== bG subtraction
//		for (int j = 0; j < pic_num; j++)
//		for (int i = 0; i < sz; i++)
//			pixelPtr[j][i] = (sums[i] > pixelPtr[j][i] ? 0 : (pixelPtr[j][i] - sums[i]));
//
//		double end = clock();
//		cout << "Using " << pic_num << " images the time is " << (end - start) / double(CLOCKS_PER_SEC) << endl;
//
//		vector<int> compression_params;
//		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
//		compression_params.push_back(90);
//
//		sin << (end - start) / double(CLOCKS_PER_SEC) << endl;
//		sin >> s;
//		string T;
//		sin >> T;
//		stringstream fin;
//		for (int i = 0; i < pic_num; i++)
//			fin << i + 1 << endl;
//		string S;
//		for (int i = 0; i < pic_num; i++)
//		{
//			fin >> S;
//			bool ok = imwrite("OUTPUT\\" + S + "_res_" + s + "_" + T + "_omp2.jpg", img_hist_equalized[i], compression_params);
//			if (!ok)
//				cout << "can't write image" << endl;
//		}
//
//
//
//		//namedWindow("imagenew", CV_WINDOW_AUTOSIZE);
//		//imshow("imagenew", img_hist_equalized[pic_num - 1]);
//	}
//
//	MPI::Finalize();
//	waitKey();
//	return 0;
//}