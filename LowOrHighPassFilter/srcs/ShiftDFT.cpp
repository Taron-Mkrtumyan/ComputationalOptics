// ============================================================
//  Rearranges the quadrants of a Fourier image so that the
//  zero-frequency component is at the center of the image.
//
//  Before shift:          After shift:
//  [ Q0 | Q1 ]           [ Q3 | Q2 ]
//  [----+----|           [----+----|
//  [ Q2 | Q3 ]           [ Q1 | Q0 ]
// ============================================================

#include "main.hpp"

void shiftDFT(Mat & fourierImage)
{
    const int centerX = fourierImage.cols / 2;
    const int centerY = fourierImage.rows / 2;

    Mat topLeft     (fourierImage, Rect(0,       0,       centerX, centerY));
    Mat topRight    (fourierImage, Rect(centerX, 0,       centerX, centerY));
    Mat bottomLeft  (fourierImage, Rect(0,       centerY, centerX, centerY));
    Mat bottomRight (fourierImage, Rect(centerX, centerY, centerX, centerY));

    // Swap Q0 <-> Q3  (top-left  <-> bottom-right)
    Mat temp;
    topLeft.copyTo(temp);
    bottomRight.copyTo(topLeft);
    temp.copyTo(bottomRight);

    // Swap Q1 <-> Q2  (top-right <-> bottom-left)
    topRight.copyTo(temp);
    bottomLeft.copyTo(topRight);
    temp.copyTo(bottomLeft);

    return ;
}