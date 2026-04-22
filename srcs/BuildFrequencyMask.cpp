// ============================================================
//  Builds a frequency-domain mask of the same size and type
//  as 'dftImage'.
//
//  Low-pass  → white canvas, black square cut from center
//             (keeps only low frequencies)
//  High-pass → black canvas, white square placed at center
//             (keeps only high frequencies)
//
//  'radius' controls the half-width of the square region.
// ============================================================

#include "main.hpp"

Mat buildFrequencyMask(const Mat& dftImage, bool isLowPass, int radius)
{
    const int centerX = dftImage.cols / 2;
    const int centerY = dftImage.rows / 2;

    // Build a single-channel Gaussian soft mask
    Mat softMask(dftImage.rows, dftImage.cols, CV_32F);

    for (int y = 0; y < softMask.rows; y++)
    {
        for (int x = 0; x < softMask.cols; x++)
        {
            float dx = x - centerX;
            float dy = y - centerY;
            float distanceSquared = dx*dx + dy*dy;

            // Gaussian falloff: 1.0 at center, smoothly approaching 0.0
            softMask.at<float>(y, x) = exp(-distanceSquared / (2.0f * radius * radius));
        }
    }

    // High-pass: invert the Gaussian (suppress center, keep edges)
    if (!isLowPass) 
        softMask = 1.0f - softMask;

    // Expand to 2 channels to match the complex DFT image (CV_32FC2)
    Mat mask;
    Mat channels[] = { softMask, softMask };
    merge(channels, 2, mask);

    return (mask);
}
