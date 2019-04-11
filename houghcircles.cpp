#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char** argv)
{
    Mat scr = imread(argv[1]);
    Mat gray, canny;
    cvtColor( scr, gray, COLOR_BGR2GRAY );
    //GaussianBlur( gray, gray, Size(3,3), 1, 1 );
    medianBlur( gray, gray, 5 );
    //Canny( gray, canny,  );

    vector<Vec3f> circles;
    HoughCircles( gray, circles, HOUGH_GRADIENT, 1, scr.rows/64, 200, 10, 5, 30 );
    for (size_t i=0; i<circles.size(); i++)
        {
            Point center( cvRound(circles[i][0]),cvRound(circles[i][1]) );
            int radius = cvRound(circles[i][2]);
            circle( scr, center, radius, Scalar(0,255,0), 2, 8, 0 );
        }
        
    imshow( "0", scr );
    waitKey(0);

    return 0;
}