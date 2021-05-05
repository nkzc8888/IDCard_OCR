#ifndef RECOGNITION
#define RECOGNITION
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

static void getPXSum(cv::Mat &src, int &a);
int getSubtract(cv::Mat &src, int TemplateNum);
int recognition(cv::Mat &srcImg, const int width, const int height);

#endif