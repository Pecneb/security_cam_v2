#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <sstream>

using namespace cv;

using std::cin;
using std::cout;
using std::endl;
using std::stringstream;

void help( char* programName ) {
    cout << " Simple Linear Blender " << endl;
    cout << "-----------------------" << endl;
    cout << "Usage: " << endl << programName << " [path_to_image1] [path_to_image2]" << endl;
}

int main( int argc, char** argv ) {
    if ( argc < 3 ) { 
        help( argv[0] );
        return EXIT_FAILURE;
    }
    
    double alpha = 0.5; double beta, input;
    cout << "Enter alpha [0.0 - 1.0]: "; cin >> input;

    if ( input >= 0 && input <= 1 )
        alpha = input;

    char* filename1 = argv[1];
    char* filename2 = argv[2];
    
    Mat src1, src2, dst;

    src1 = imread( samples::findFile( filename1 ) );
    src2 = imread( samples::findFile( filename2 ) );
    resize( src2, src2, src1.size(), 0, 0, INTER_AREA );

    if ( src1.empty() ) { cout << "Error loading image1" << endl; return EXIT_FAILURE; }
    if ( src2.empty() ) { cout << "Error loading image2" << endl; return EXIT_FAILURE; }

    beta = ( 1.0 - alpha );
    addWeighted( src1, alpha, src2, beta, 0.0, dst );
    namedWindow( "Linear Blend", WINDOW_AUTOSIZE );
    imshow( "Linear Blend", dst );
    waitKey(0);

    return 0;
}
