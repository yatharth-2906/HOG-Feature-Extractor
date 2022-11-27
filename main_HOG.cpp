#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<stdint.h>
#include<math.h>

using namespace cv;
using namespace std;

void main()
{
	string path = "F:\\C++ Project\\HOG-Histogram_Of_Oriented _Gradients\\HOG-Histogram_Of_Oriented _Gradients\\Resources\\Yatharth_Pics\\Y-5.jpg"; 
	//string path = "F:\\C++ Project\\HOG-Histogram_Of_Oriented _Gradients\\HOG-Histogram_Of_Oriented _Gradients\\Resources\\Viku.jpeg";
	//string path = "F:\\C++ Project\\HOG-Histogram_Of_Oriented _Gradients\\HOG-Histogram_Of_Oriented _Gradients\\Resources\\VC_1.png";
	//string path = "F:\\C++ Project\\HOG-Histogram_Of_Oriented _Gradients\\HOG-Histogram_Of_Oriented _Gradients\\Resources\\doo.png";
	Mat img = imread(path);
	resize(img, img, Size(400, 400));
	//resize(HOG, HOG, Size(64,128));
	//resize(phase, phase, Size(64, 128));
	cvtColor(img, img, COLOR_BGR2GRAY);
	//cvtColor(HOG, HOG, COLOR_BGR2GRAY);
	//cvtColor(phase, phase, COLOR_BGR2GRAY);
	const int r = img.rows, c = img.cols;
	Mat HOG = Mat::zeros(r, c, CV_8U), phase = Mat::zeros(r, c, CV_8U);
	cout << img.rows << " " << img.cols << endl;
	cout << img.size() << endl;
	cout << HOG.rows << " " << HOG.cols << endl;
	cout << HOG.size() << endl;
	cout << ((atan(-4 / 3) * 180) / (float)3.14) << endl;
	int k = 0;
	//int8_t Gx[r*c] = { 0 }, Gy[r*c] = { 0 }, M[r*c] = { 0 }, P[r*c] = { 0 };
	int8_t* Gx = new int8_t[r * c];
	int8_t* Gy = new int8_t[r * c];
	int8_t* M = new int8_t[r * c];
	int8_t* P = new int8_t[r * c];
	int8_t** Bins = new int8_t * [r * c];
	int8_t C[9] = { 10, 30, 50, 70, 90, 110, 130, 150, 170 };
	int8_t Histo[9] = { 0 };
	/*Gx = Horizontal Gradients
	  Gy = Vertical Gradients
	  M = Magnitude Gradient Array
	  P = Phase Gradient Array*/
	for (int rows = 0; rows < img.rows; rows++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			Bins[k] = new int8_t[9];
			//HOG.at<Vec3b>(rows, col) = img.at<Vec3b>(rows, col) * 0.5f; 
			if (col + 1 < img.cols && col - 1 >= 0)
				Gx[k] = img.at<int8_t>(rows, col + 1) - img.at<int8_t>(rows, col - 1);
			else if (col + 1 > img.cols)
				Gx[k] = -1 * img.at<int8_t>(rows, col - 1);
			else if (col - 1 < 0)
				Gx[k] = img.at<int8_t>(rows, col + 1);
			/*else
				continue;*/
			if (rows + 1 < img.rows && rows - 1 >= 0)
				Gy[k] = img.at<int8_t>(rows - 1, col) - img.at<int8_t>(rows + 1, col);
			else if (rows + 1 > img.rows)
				Gy[k] = img.at<int8_t>(rows - 1, col);
			else if (rows - 1 < 0)
				Gy[k] = -1 * img.at<int8_t>(rows + 1, col);
			/*else
				continue;*/
			M[k] = sqrt((Gx[k] * Gx[k]) + (Gy[k] * Gy[k]));
			HOG.at<int8_t>(rows, col) = M[k];
			if (Gx[k] != 0)
				P[k] = ((atan(Gy[k] / Gx[k]) * 180) / float(3.1415));
			else
				P[k] = 90;
			if (P[k] < 0)
				P[k] = 180 + P[k];
			phase.at<int8_t>(rows, col) = P[k];
			int j = floor((P[k] / (float)20.0) - 0.5);
			if (j <= 0)
				j = 0;
			Bins[k][j] = M[k] * abs((C[j + 1] - P[k]) / (float)20.0);
			Bins[k][j + 1] = M[k] * abs((P[k] - C[j]) / (float)20.0);
			Histo[j] = (Histo[j]) + (M[k] * ((C[j + 1] - P[k]) / (float)20.0));
			Histo[j + 1] = (Histo[j + 1]) + (M[k] * ((C[j + 1] - P[k]) / (float)20.0));
			k++;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (Histo[i] < 0)
			Histo[i] = abs(Histo[i]);
		cout << (int)Histo[i] << " ";
	}
	//imshow("Image", img);
	//imshow("HOG", HOG);
	//imshow("Phase", phase);
	Mat img_hog;
	hconcat(img, HOG, img_hog);
	imshow("IMG and HOG", img_hog);
	imwrite("IMG_AND_HOG.png", img_hog);
	//imwrite("Image.png", img);
	//imwrite("HOG.png", HOG);
	//imwrite("Phase.jpeg", phase);
	waitKey(0);
}