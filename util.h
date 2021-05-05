#ifndef UTIL
#define UTIL
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;

vector<int> horizontalProjectionMat(cv::Mat srcImg, const int height, const int width);
cv::Mat horizontal_map(vector<int>& record, const int height, const int width);
vector<cv::Mat> horizontal_cut(cv::Mat srcImg, vector<int>& record, const int height, const int width);

vector<int> verticalProjectionMat(cv::Mat srcImg, const int height, const int width);
cv::Mat vertical_map(vector<int>& record, const int height, const int width);
vector<cv::Mat> vertical_cut(cv::Mat srcImg, vector<int>& record, const int height, const int width);

vector<cv::Mat> get_horizontal_cut(cv::Mat srcImg, const int height, const int width);
vector<cv::Mat> get_vertical_cut(cv::Mat srcImg, const int height, const int width);
#endif