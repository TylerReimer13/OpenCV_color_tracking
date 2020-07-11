#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include "color_tracking.h"

TrackColor::TrackColor() {};

TrackColor::TrackColor(int n_erosion, int n_dilate, int hsv_lower[3], int hsv_upper[3]) {
    num_erosions = n_erosion;
    num_dilations = n_dilate;
    memcpy(hsv_low, hsv_lower, sizeof(hsv_low));
    memcpy(hsv_hi, hsv_upper, sizeof(hsv_hi));
};

void TrackColor::filter_image(Mat frame) {
    // Convert original BGR frame to HSV frame
    Mat frame_BGR_to_HSV, blurred, blurred_thresh, eroded, filtered, blurred_thresh_filtered;
    cvtColor(frame, frame_BGR_to_HSV, CV_BGR2HSV);
	
    // Apply Gaussian blur to frame
    GaussianBlur(frame_BGR_to_HSV, blurred, Size(5, 5), 0);
	
    // Erode and Dilate to remove noise
    erode(blurred, eroded, Mat(), Point(-1, 1), num_erosions);
    dilate(eroded, filtered, Mat(), Point(-1, -1), num_dilations);

    // Frame that focuses on HSV values in specified ranges
    inRange(blurred, Scalar(hsv_low[0], hsv_low[1], hsv_low[2]), Scalar(hsv_hi[0], hsv_hi[1], hsv_hi[2]), blurred_thresh);	
    inRange(filtered, Scalar(hsv_low[0], hsv_low[1], hsv_low[2]), Scalar(hsv_hi[0], hsv_hi[1], hsv_hi[2]), blurred_thresh_filtered);

    imshow(original, frame);
    imshow(before, blurred_thresh);
    imshow(after, blurred_thresh_filtered);
};


int main(int argc, char* argv[])
{
    // Modify this to track different colors. Currently set for green.
    int low_hsv[3] = {45, 40, 40};
    int high_hsv[3] = {65, 255, 255};
    TrackColor tracker(8, 8, low_hsv, high_hsv);

    VideoCapture cap(-1);

    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        return -1;
    }

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame);
        if (bSuccess == false)
        {
            cout << "End of video" << endl;
            break;
        }

	tracker.filter_image(frame);

        if (waitKey(10) == 27)
        {
            cout << "Video ended by user" << endl;
            break;
        }
    }

    return 0;

}

