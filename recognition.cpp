#include "util.h"
#include "recognition.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

static void getPXSum(Mat &src, int &a)
{
	threshold(src, src, 100, 255, CV_THRESH_BINARY);
	a = 0;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			a += src.at <uchar>(i, j);
		}
	}
}
int getSubtract(Mat &src, int TemplateNum) 
{
	Mat img_result;
	int min = INT_MAX, diff = 0;
	int serieNum = 0;
    blur(src, src, Size(3,3));
    resize(src, src, Size(32, 48), 0, 0, CV_INTER_LINEAR);
	for (int i = 0; i < TemplateNum; i++) {
		string name = "../template/m" + std::to_string(i) + ".jpg";
		Mat Template = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
        blur(Template, Template, Size(3,3));
		resize(Template, Template, Size(32, 48), 0, 0, CV_INTER_LINEAR);
		absdiff(Template, src, img_result);
		getPXSum(img_result, diff);
		if (diff < min)
		{
			min = diff;
			serieNum = i;
		}
	}
	return serieNum;
}
int recognition(Mat &srcImg, const int width, const int height)
{
    Mat tmp = get_horizontal_cut(srcImg, height, width)[0];
    const int cur_height = tmp.rows;
    vector<Mat> nums = get_vertical_cut(tmp, cur_height, width);
    for(Mat num : nums) 
    {
        int res = getSubtract(num, 10);
        std::cout<<res<<' ';
    }
    cout<<'\n';
	return 0;
}
