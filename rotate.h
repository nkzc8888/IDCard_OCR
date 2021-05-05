#ifndef ROTATE
#define ROTATE
#include <cstdlib>
#include <opencv2/opencv.hpp>

double detect_angle(cv::Mat srcImg);
cv::Mat rotate(cv::Mat srcImg);

#endif