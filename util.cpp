#include "util.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

const int pixel_white = 255;
const int pixel_black = 0;

vector<int> horizontalProjectionMat(Mat srcImg, const int height, const int width)
{
	Mat binImg;
	blur(srcImg, binImg, Size(3, 3));
	threshold(binImg, binImg, 0, 255, 8);
	int perPixelValue = 0;
	vector<int> projectValArry(height, 0);
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			perPixelValue = binImg.at<char>(row, col);
			if (perPixelValue == 0)
			{
				projectValArry[row]++;
			}
		}
	}
	return projectValArry;
}

Mat horizontal_map(vector<int>& record, const int height, const int width)
{
	Mat horizontalProjectionMat(height, width, CV_8UC1);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			horizontalProjectionMat.at<uchar>(i, j) = pixel_white;
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < record[i]; j++)
		{
			horizontalProjectionMat.at<uchar>(i, width - 1 - j) = pixel_black;
		}
	}
	return horizontalProjectionMat;
}

vector<Mat> horizontal_cut(Mat srcImg, vector<int>& record, const int height, const int width)
{
	vector<Mat> roiList;
	int startIndex = 0;
	int endIndex = 0;
	bool inBlock = false;
	for (int i = 0; i <srcImg.rows; i++)
	{
		if (!inBlock && record[i] != 0)
		{
			inBlock = true;
			startIndex = i;
		}
		else if (inBlock && record[i] == 0)
		{
			endIndex = i;
			inBlock = false;
			Mat roiImg = srcImg(Range(startIndex, endIndex + 1), Range(0, srcImg.cols));
			roiList.push_back(roiImg);
		}
	}
	return roiList;
}
/*
得到图像的投影分布数组
*/
vector<int> verticalProjectionMat(Mat srcImg, const int height, const int width)
{
	Mat binImg;
	blur(srcImg, binImg, Size(3, 3));
	threshold(binImg, binImg, 0, 255, CV_THRESH_OTSU);
	int perPixelValue;
	vector<int> projectValArry(width, 0);
	for (int col = 0; col < width; col++)
	{
		for (int row = 0; row < height; row++)
		{
			perPixelValue = binImg.at<uchar>(row, col);
			if (perPixelValue == 0)
			{
				projectValArry[col]++;
			}
		}
	}
	
	return projectValArry;
}
/*
根据投影分布数组，绘制投影图像
*/
Mat vertical_map(vector<int>& record, const int height, const int width)
{
	Mat verticalProjectionMat(height, width, CV_8UC1);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{ 
			verticalProjectionMat.at<uchar>(i, j) = pixel_white;
		}
	}
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < record[i]; j++)
		{
			verticalProjectionMat.at<uchar>(height - 1 - j, i) = pixel_black;
		}
	}
	return verticalProjectionMat;
}
/*
根据投影分布数组，对图像进行字符切分
*/
vector<Mat> vertical_cut(Mat srcImg, vector<int>& record, const int height, const int width)
{
	vector<Mat> roiList;
	int startIndex = 0;
	int endIndex = 0;
	bool inBlock = false;
	for (int i = 0; i < width; i++)
	{
		if (!inBlock && record[i] != 0)
		{
			inBlock = true;
			startIndex = i;
		}
		else if (record[i] == 0 && inBlock)
		{
			endIndex = i;
			inBlock = false;
			Mat roiImg = srcImg(Range(0, height), Range(startIndex, endIndex + 1));
			roiList.push_back(roiImg);
		}
	}
	return roiList;
}

vector<Mat> get_horizontal_cut(Mat srcImg, const int height, const int width) 
{
	vector<int> horizontal_rec = horizontalProjectionMat(srcImg, height, width);
	Mat horizontalProjectionMat = horizontal_map(horizontal_rec, height, width);
	vector<Mat> a = horizontal_cut(srcImg, horizontal_rec, height, width);
	return a;
}

vector<Mat> get_vertical_cut(Mat srcImg, const int height, const int width) 
{
	vector<int> vertical_rec = verticalProjectionMat(srcImg, height, width);
	Mat verticalProjectionMat = vertical_map(vertical_rec, height, width);
	vector<Mat> a = vertical_cut(srcImg, vertical_rec, height, width);
	return a;
}