#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>

using namespace cv;

int main(int argc, char** argv) {
    
    if ( argc != 2 ) {
        std::cout << "Usage: GettingStartedWithImages.app <imagepath>";
        return -1;
    }

    Mat img = imread(argv[1], IMREAD_COLOR);

    if ( img.empty() ) {
        std::cout << "Could not read the image: " << argv[1] << std::endl;
        return 1;
    }

    imshow("Display Window", img);
    int k = waitKey(0); // Wait for keystroke in the window

    if ( k == 's' ) {
        imwrite("starry_night.png", img);
    }
    return 0;
}
