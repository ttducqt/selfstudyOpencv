#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio/videoio.hpp>

#include <iostream>


using namespace std;
using namespace cv;

Mat grayNBlured( Mat &frame )
{
    Mat gray;
    cvtColor( frame, gray, COLOR_BGR2GRAY );
    GaussianBlur( gray, gray, Size(5,5), 0 );
    return gray;
}

main( int argc, char** argv )
{

    VideoCapture cap(argv[1]);
    int frame_heigt = cap.get(CAP_PROP_FRAME_HEIGHT);
    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int fps = cap.get(CAP_PROP_FPS);
    VideoWriter ViWr("resource/highwayresult.avi", ViWr.fourcc('M','J','P','G'), fps, Size(frame_width,frame_heigt) );
    system("clear");

    Mat frame, fgMask, gray;
    Ptr<BackgroundSubtractorMOG2> BackgrdSub = createBackgroundSubtractorMOG2();
    
    while(cap.isOpened())
    {
        cap >> frame;
        gray = grayNBlured(frame);
        BackgrdSub->apply( gray, fgMask );
        erode( fgMask, fgMask, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );
        dilate( fgMask, fgMask, getStructuringElement(MORPH_ELLIPSE, Size(5,5)) );
        imshow("fgMask", fgMask);

        vector<vector<Point>> contours;
        findContours( fgMask, contours, RETR_LIST, CHAIN_APPROX_SIMPLE );
        vector<vector<Point>> contours_poly( contours.size() );
        vector<vector<Point>> hull( contours.size() );
        vector<Rect> boundRect( contours.size() );
        for( size_t i=0; i<contours.size(); i++ )
        {
            if( contourArea(contours[i])<600 )
                continue;
            approxPolyDP( contours[i], contours_poly[i], 3, true );
            convexHull( contours[i], hull[i] );
            drawContours( frame, hull, (int)i, Scalar(0,255,0) );
            //boundRect[i]= boundingRect( hull[i] );
            //rectangle( frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0), 2);
        }
        //ViWr << frame;
        imshow("frame", frame);
        if( (char)waitKey(1)=='q' )
            break; 
    }
    return 0;
}   