#include "rotate.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

const int thr_high = 255;
const int thr_low = 150;
const int can_high = 200;
const int can_low = 50;

double detect_angle(Mat srcImage)
{
	Mat midImage;
	if (srcImage.empty()) { 
		perror("read img error"); 
	}
	threshold(srcImage, midImage, thr_low, thr_high, 0);
	Canny(midImage, midImage, can_low, can_high, 3);
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
	double angle = 0;
	angle = lines[0][1] / CV_PI * 180 - 90;
	return angle;
}

Mat rotate(Mat srcImage)
{
	Mat rotMat(2, 3, CV_32FC1);
	Mat dstImage_rotate;
	if (srcImage.empty()) { 
		perror("read img error"); 
	}
	double angle = detect_angle(srcImage);
	dstImage_rotate = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());
	Point center = Point(srcImage.cols / 2, srcImage.rows / 2);
	double scale = 0.8;
	rotMat = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcImage, dstImage_rotate, rotMat, dstImage_rotate.size(), INTER_LINEAR, BORDER_REPLICATE); 
	return dstImage_rotate;
}

 