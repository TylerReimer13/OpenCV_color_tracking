#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>

using namespace std;
using namespace cv;

class TrackColor {
    private:
        int num_erosions=8;
        int num_dilations=8;
        
        int hsv_low[3] = {0, 0, 0};
        int hsv_hi[3] = {0, 0, 0};

        string original = "Original Video";
        string before = "Before Filter";
        string after = "After Filter";

    public:
        TrackColor();
        TrackColor(int n_erosion, int n_dilate, int hsv_lows[3], int hsv_highs[3]);
        void filter_image(Mat frame);
};
