#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>


//START OF FUNCTIONS (FILTERS/OPERATORS) SECTION
//Bilateral Filter
cv::Mat bilateralFilter(const std::string& imagePath) {
    cv::Mat image = cv::imread(imagePath);
    
    //for security, if image is empty/nonexistent
    if (image.empty()) 
    {throw std::runtime_error("Failed to load image at: " + imagePath + " , there's no such img.");}
    
    cv::Mat bilateralIMG;
    cv::bilateralFilter(image, bilateralIMG, 15,95,45);
    
    return bilateralIMG;    
}

//Sobel Operator (for circulars)
cv::Mat sobelOperator(const std::string& imagePath){
    cv::Mat imageIN = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);
    
    cv::Mat gradX, gradY, absGradX, absGradY, combined;
    
    cv::Sobel(imageIN, gradX, CV_16S, 1, 0, 3);
    cv::Sobel(imageIN, gradY, CV_16S, 0, 1, 3);
    
    cv::convertScaleAbs(gradX, absGradX);
    cv::convertScaleAbs(gradY, absGradY);
    
    cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, combined);
    
    return combined;
}

// SHOW Picture (from path)
void showPic(const std::string& imagePath, const std::string& windowName) {
    cv::Mat image = cv::imread(imagePath);              // read our image's path
    
    if (image.empty())                                  // check if image exists on the path
        {throw std::runtime_error("Failed to load image at: " + imagePath + " , there's no such img.");}
    
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);     // create the display window with the given name 
    cv::imshow(windowName, image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    
}
// SHOW Picture <OVERLOAD> (filter/operator, and from path)
void showPic(const cv::Mat& image, const std::string& windowName) {
    if (image.empty())                      // check if image exists
        {throw std::runtime_error("Failed to load, the image may be empty.");}
    
    cv::namedWindow(windowName, cv::WINDOW_NORMAL); // create the display window 
    cv::imshow(windowName, image);                  // display/show the image
    cv::waitKey(0);                                 // wait for key interruption to close the window
    cv::destroyAllWindows();                        // close/exit the windows
}


//END OF FUNCTIONS (FILTERS/OPERATORS) SECTION


int main() 
{

    //testing showPic()
    // showPic("Turtle.jpg", "TURTLE PICTURE");
    showPic("Anchovies.jpg","ANCHOVIES");
    
    //overload by object
    cv::Mat imgFiltered = bilateralFilter("Anchovies.jpg"); 
    showPic(imgFiltered, "FILTERED ANCHOVIES");
    
    showPic("Coins.jpg", "COINS");
    //by argument
    showPic(sobelOperator("coins.jpg"), "SOBEL OP'd COINS");
    

    return 0;
}

