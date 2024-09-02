#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

Mat dft(Mat I)
{
    Mat padded, complexI;

    auto m = getOptimalDFTSize(I.rows);
    auto n = getOptimalDFTSize(I.cols); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    cv::merge(planes, 2, complexI); // Add to the expanded another plane with zeros

    cv::dft(complexI, complexI); // this way the result may fit in the source matrix
    return complexI;
}

int main()
{
    Mat input, currentFourier, pastFourier, convMat;
    int cx, cy;

    VideoCapture cap;

    int deviceID = 0;        // 0 = open default camera
    int apiID = cv::CAP_ANY; // 0 = autodetect default API
    // open selected camera using selected API
    cap.open(deviceID, apiID);
    // check if we succeeded
    if (!cap.isOpened())
    {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

    for (int i = 0;; i++)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(input);
        // check if we succeeded
        if (input.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        cvtColor(input, input, cv::COLOR_RGB2GRAY);

        currentFourier = dft(input);

        if(i != 0)
        {
            mulSpectrums(currentFourier, currentFourier, convMat, 0);
            cv::dft(convMat, convMat, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
            normalize(convMat, convMat, 0, 1, NORM_MINMAX);
            imshow("Input Image", input); // Show the result
            imshow("spectrum magnitude", convMat);
        }

        currentFourier.copyTo(pastFourier);

        if (waitKey(5) >= 0)
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}