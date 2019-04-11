#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace std;;
using namespace cv;


int main ( int argc, char** argv )
{
    Mat img = imread(string(argv[1])); 
    resize( img, img, Size(), 0.5, 0.5 );

    Mat img_mdB;
    medianBlur( img, img_mdB, 1 );
    cvtColor( img_mdB, img_mdB, COLOR_BGR2GRAY );

    Mat img_rs, img_rs1;
    adaptiveThreshold( img_mdB, img_rs, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 1 );
    adaptiveThreshold( img_mdB, img_rs1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 1 );
    
    vector<cv::Vec4i> hierarchy;
    Mat img2;
    findContours( img, img2, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );

    imshow( "1", img );
    waitKey(0);
    return 0;
}