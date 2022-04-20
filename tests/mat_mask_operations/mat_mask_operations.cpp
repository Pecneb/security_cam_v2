#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void help(char* progName) {
    cout << endl
        << "Usage: " << endl
        << progName << " [image_paht] [G -- grayscale] " << endl << endl;
}

void Sharpen(const Mat& myImage, Mat& Result);

int main(int argc, char** argv) {
   
    if (argc < 2) {
        help(argv[0]);     
        return -1;
    }

    const char* filename = argv[1];

    Mat src, dst0, dst1;

    if (argc >= 3 && !strcmp("G", argv[2]))
        src = imread( samples::findFile( filename ), IMREAD_GRAYSCALE);
    else
        src = imread( samples::findFile( filename ), IMREAD_COLOR);

    if ( src.empty() ) {
        cerr << "Can't open image [" << filename << "]" << endl;
        return EXIT_FAILURE;
    }

    namedWindow("Input", WINDOW_AUTOSIZE);
    namedWindow("Output", WINDOW_AUTOSIZE);

    imshow( "Input", src );
    
    Mat kernel = (Mat_<char>(3,3) << 0, -1, 0,
                                   -1,  5, -1,
                                   0, -1, 0);
    filter2D( src, dst1, src.depth(), kernel);

    imshow( "Output", dst1 );

    waitKey();
    return EXIT_SUCCESS;
}
