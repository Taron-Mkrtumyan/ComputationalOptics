#include "main.hpp"

int main()
{
    // ── Filter parameters ────────────────────────────────────
    const bool LOW_PASS  = false;   // true for low-pass, false for high-pass
    const int  RADIUS    = 50;      // half-width of the square mask region

    // ── Load image ───────────────────────────────────────────
    Mat image = imread("Pictures/Poseidon.png", IMREAD_GRAYSCALE);
    if (image.empty())
        return (-1);

    imwrite("original_grayscale.png", image);

    // ── Convert to float for DFT ─────────────────────────────
    Mat floatImage;
    image.convertTo(floatImage, CV_32F);

    // ── Forward DFT ──────────────────────────────────────────
    Mat dftImage;
    dft(floatImage, dftImage, DFT_COMPLEX_OUTPUT);

    // ── Shift zero-frequency to center ───────────────────────
    shiftDFT(dftImage);

    // // ── Visualize frequency spectrum ─────────────────────────
    // Mat planes[2];
    // split(dftImage, planes);                        // planes[0]=real, planes[1]=imaginary

    // Mat magnitude;
    // cv::magnitude(planes[0], planes[1], magnitude); // magnitude = sqrt(re^2 + im^2)
    // magnitude += Scalar::all(1);                    // shift by 1 to avoid log(0)
    // log(magnitude, magnitude);                      // log scale for visibility

    // Mat spectrum;
    // normalize(magnitude, spectrum, 0, 255, NORM_MINMAX, CV_8U);
    // imwrite("frequency_spectrum.png", spectrum);

    // ── Build and apply frequency mask ───────────────────────
    Mat mask = buildFrequencyMask(dftImage, LOW_PASS, RADIUS);
    multiply(dftImage, mask, dftImage);

    // ── Shift back and compute inverse DFT ───────────────────
    shiftDFT(dftImage);

    Mat inverseImage;
    idft(dftImage, inverseImage, DFT_REAL_OUTPUT | DFT_SCALE);

    // ── Normalize to 8-bit range for saving ──────────────────
    Mat result;
    normalize(inverseImage, result, 0, 255, NORM_MINMAX, CV_8U);

    // ── Save result ───────────────────────────────────────────
    string outputFilename = LOW_PASS ? "result_lowpass.png" : "result_highpass.png";
    imwrite(outputFilename, result);
    cout << "Image saved as: " << outputFilename << endl;

    return (0);
}
