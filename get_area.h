#ifndef GET_AREA
#define GET_AREA
#include <cstdlib>
#include <opencv2/opencv.hpp>

const int size_IDCARD = 10;
const double p_x = 0.27;
const double p_y = 0.77;
const double width_idx = 0.62;
const double height_idx = 0.18;
cv::Mat get_number_area(cv::Mat &src);

#endif