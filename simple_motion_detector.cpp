#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;

Mat grayNBlured( Mat frame )
{
    Mat gray;
    cvtColor( frame, gray, COLOR_BGR2GRAY );
    GaussianBlur( gray, gray, Size(5,5), 0 );
    return gray;
}

main( int argc, char** argv )
{
    system("clear");

    VideoCapture cap(argv[1]);

    Mat gray_rt;
    Mat gray_bt;
    Mat frame;
    cap >> frame;   
    gray_rt = grayNBlured( frame );
    
    while(cap.isOpened())
    {   
       
        gray_bt = gray_rt;

        cap >> frame;
        gray_rt = grayNBlured( frame );

        Mat diff;
        absdiff( gray_bt, gray_rt, diff );
        threshold( diff, diff, 25, 255, THRESH_BINARY );
        //erode( diff, diff, getStructuringElement(MORPH_ELLIPSE, Size(1, 1)) );
        //imshow("erode", diff );
        dilate( diff, diff, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );
        imshow( "dilae", diff);

        vector<vector<Point>> contours;
        //vector<Vec4i> hierachy;
        findContours( diff, contours, RETR_LIST, CHAIN_APPROX_SIMPLE );
        
        vector<Rect> boundRect( contours.size() );
        vector<vector<Point>> contours_poly( contours.size() );
        for( size_t i=0; i<contours.size(); i++ )
        {
            if( contourArea(contours[i])<800 )
                continue;
            approxPolyDP( contours[i], contours_poly[i], 3, true );
            boundRect[i]= boundingRect( contours_poly[i] );
            rectangle( frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0), 2);
        }
        imshow("diff", diff);
        imshow("frame", frame);
        if( (char)waitKey(1)=='q' )
            break; 
    }
    return 0;
}   