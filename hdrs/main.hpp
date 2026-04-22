#ifndef MAIN_HPP
#define MAIN_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat buildFrequencyMask(const Mat& dftImage, bool isLowPass, int radius);
void shiftDFT(Mat& fourierImage);

#endif