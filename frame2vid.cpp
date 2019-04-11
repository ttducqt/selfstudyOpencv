#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
    Scalar OrangeLow = Scalar( 30, 55 ,150);
    Scalar OrangeHigh = Scalar( ); 

    VideoCapture ViCap(0);
    Mat frame;  
    
    
    int frame_heigt = ViCap.get(CAP_PROP_FRAME_HEIGHT);
    int frame_width = ViCap.get(CAP_PROP_FRAME_WIDTH);
        

    for(;;)
    {
        ViCap >> frame;
        //ViWr.write(frame);
        imshow( "hello", frame );
        if ( (char)waitKey(1)=='q' )
            break;
        
    }

    return 0;
}