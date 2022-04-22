#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using namespace cv;

int main(int argc, char** argv) {
    const String keys = 
        "{help h usage ? |    | ./program_name [flags] @input}"
        "{@input         |    | input image}"
        "{g              |    | gamma correction}";
    CommandLineParser parser( argc, argv, keys );
    parser.about( " Basic linear transforms " );

    if ( parser.has("help") ) {
        parser.printMessage();
        return 0;
    }
    
    Mat image = imread( samples::findFile( parser.get<String>( "@input" ) ) );
    Mat new_image;
    if ( image.empty() ) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input Image>" << endl;
        return -1;

    }
    
    
    if ( parser.has("g") ) {
        new_image = image.clone();
        double gamma_ = 0.4;

        Mat lookUpTable(1, 256, CV_8U);
        uchar* p = lookUpTable.ptr();
        for ( int i = 0; i < 256; i++) 
           p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);

        LUT( image, lookUpTable, new_image);
    } else {
        new_image = Mat::zeros( image.size(), image.type() );
        double alpha = 1.0; /*< Simple contrast control >*/
        int beta = 0; /*< Simple contrast control >*/

        cout << " Basic linear transforms " << endl;
        cout << "-------------------------" << endl;
        cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
        cout << "* Enter the alpha value [0-100]: "; cin >> beta;

        for ( int y = 0; y < image.rows; y++ ) {
            for ( int x = 0; x < image.cols; x++ ) {
                for ( int c = 0; c < image.channels(); c++ ) {
                    new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>( alpha * image.at<Vec3b>(y, x)[c] + beta );
                }
            }
        }
    }

    imshow("Original Image", image);
    imshow("New Image", new_image);

    waitKey(0);
    return 0;
}
