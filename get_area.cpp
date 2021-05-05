#include "get_area.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int i = 0;
RNG rng(12345);
vector<vector<Point>> Contours;
vector<Vec4i> Hierarchy;

Mat get_number_area(Mat &src)
{	
	Mat mid;
	blur(src, mid, Size(3, 3));
	Canny(mid, mid, 50, 400, 3);
	findContours(mid, Contours, Hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(mid.size(), CV_8UC3);
	for (; i < Contours.size(); i++)
	{
		if ((int)(Contours[i].size()) > size_IDCARD)
		{
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			drawContours(drawing, Contours, i, color, 2, 8, Hierarchy, 0, Point());
			break;
		}
	}
	Rect IDCARD = boundingRect(Contours.at(i));
	rectangle(src, IDCARD, Scalar(255, 0, 255), 5, 8);
	Mat res = src(IDCARD);
	Rect rect(res.cols * p_x, res.rows * p_y, res.cols * width_idx, res.rows * height_idx); //根据坐标和长宽截取数组区域
	return res(rect);
}
