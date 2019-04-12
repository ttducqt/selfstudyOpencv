#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;

void findFaceEye_fn( Mat &frame, CascadeClassifier &face_cc, CascadeClassifier &eye_cc )
{
    vector<Rect> faces;
    face_cc.detectMultiScale( frame, faces, 1.1, 5, 0|CASCADE_SCALE_IMAGE, Size(30,30) );
    for( size_t i=0; i<faces.size(); i++)
    {
        Rect f = faces[i];
        rectangle( frame, Point( f.x, f.y ), Point( f.x + f.width, f.y + f.height ),
            Scalar(0, 255, 0), 3 );
        
        Mat face_crop = frame(f);
        imshow( "face_crop", face_crop );
        vector<Rect> eyes;
        eye_cc.detectMultiScale( face_crop, eyes, 1.3, 5, 0, Size(30,30) );
        for( size_t j=0; j<eyes.size(); j++ )
        {
            Rect e = eyes[j];
            rectangle( frame, Point( f.x + e.x, f.y + e.y), 
                Point(f.x + e.x + e.width, f.y + e.y + e.height),
                Scalar(0,255,0), 3 );
        }
    }
}

int main( int argc, char** argv)
{
    VideoCapture cap;
    if (argc == 1)
        cap.open(0);
    else
        cap.open( string(argv[1]) );
    //choose read frame from the video or camera

    CascadeClassifier face_cc;
    face_cc.load("cascades/haarcascade_frontalface_default.xml");
    CascadeClassifier eye_cc;
    eye_cc.load("cascades/haarcascades/haarcascade_eye.xml");
    //read the cascade for detector

    for(;;)
    {
        Mat frame;
        cap >> frame;
        if( frame.empty() )
            break;
        //capture frame

        findFaceEye_fn( frame, face_cc, eye_cc);
        //find face and eye in frame

        imshow("Face", frame);
        if( (char)waitKey(1) == 'q' )
            break;
        //show the result
    }
    return 0;
}






