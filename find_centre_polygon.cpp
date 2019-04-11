#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main( int argc, char** argv )
{
    Mat img = imread( argv[1], 0 );
    Mat origin = imread( argv[1] );
    Mat canny_op;
    GaussianBlur( img, img, Size(5,5), 0 );   
    Canny( img, canny_op, 70, 140 );

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours( canny_op, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );
    vector<Moments> mu( contours.size() );
    vector<Point2f> mc( contours.size() );
    
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar(0, 255, 0);
        drawContours( origin , contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
        mu[i] = moments( contours[i] );
        mc[i] = Point2f( static_cast<float>(mu[i].m10 / (mu[i].m00 + 1e-5)),
                    static_cast<float>(mu[i].m01 / (mu[i].m00 + 1e-5)) );
        //cout << "mc[" << i << "]=" << mc[i] << endl;
        circle( origin, mc[i], 4, color, 1 );
    }
    
    imshow( "", origin );
    waitKey(0);
    
    return 0;
}