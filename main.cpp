#include "rotate.h"
#include "recognition.h"
#include "get_area.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	if ( argc != 2 )  
    {  
        perror("please input image path");
        return -1;  
    }
	Mat srcImg, midImg, dstImg;  
    srcImg = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);  
	
    if ( srcImg.empty() )  
    {  
        perror("No image data");
        return -1;  
    }
	midImg = rotate(srcImg);
	dstImg = get_number_area(midImg);

	const int width = dstImg.cols;
	const int height = dstImg.rows;
	
	threshold(dstImg, dstImg, 50, 250, 8);
	recognition(dstImg, width, height);
	return 0;
}