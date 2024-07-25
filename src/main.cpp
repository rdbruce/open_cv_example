#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/features2d.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Mat original, blur, bin, hsv, out;

    vector<Mat> channels(3);

    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;
    
    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.5;
    
    // Filter by Convexity
    params.filterByConvexity = true;
    params.maxConvexity = 0.1;
    
    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;

    // Set up the detector with default parameters.
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();

    vector<KeyPoint> keypoints;

    VideoCapture cap;

    if(argc >= 2)
    {
        cap.open("../../IMG_3783.MP4");
        if (!cap.isOpened())
        {
            cerr << "ERROR! Unable to open image\n";
            return -1;
        }
    }
    else
    {
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
    }

    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(original);
        // check if we succeeded
        if (original.empty())
        {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        cvtColor(original, hsv, COLOR_RGB2HSV);

        // split img:
        split(original, channels);

        // blur = cv.GaussianBlur(channels[2],(5,5),0)
        // boxFilter(channels[2], blur, -1, Size(30, 30));
        
        // adaptiveThreshold(I, I, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 17, 0);
        // threshold( channels[2], bin, threshold_value, max_binary_value, THRESH_OTSU );
        threshold( channels[2], bin, 245, 255, THRESH_BINARY_INV );
        
        // Detect blobs
        detector->detect(bin, keypoints);

        cout << keypoints.size() << " keypoints" << endl;
        
        // Draw detected blobs as red circles.
        // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
        drawKeypoints( bin, keypoints, out, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        imshow("Input Image", original); // Show the result
        imshow("Plane 2", channels[2]);
        imshow("Bin", bin);
        imshow("Output", out);
        // imshow("Blur", blur);
        if (waitKey(25) >= 0)
        {
            break;
        }
    }

    return EXIT_SUCCESS;
}