#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>


int image(std::string src, std::string dst)
{
  cv::Mat img;
  img = cv::imread(src);
  
  if (img.empty()) //check whether the image is loaded or not
  {
    std::cout << "Error : Image cannot be loaded..!!" << std::endl;
    return 1;
  }
  
  cv::Mat img2 = cv::Mat::zeros(cv::Size(img.rows, img.cols), CV_8UC3);
  
/*
*   iterates the input image and saves each color in the output image
*/
  for (int y = 0; y < img.rows; y++){
    for (int x = 0; x < img.cols; x++){
      img2.at<cv::Vec3b>(y,x)[0] = img.at<cv::Vec3b>(y,x)[0];
      img2.at<cv::Vec3b>(y,x)[1] = img.at<cv::Vec3b>(y,x)[1];
      img2.at<cv::Vec3b>(y,x)[2] = img.at<cv::Vec3b>(y,x)[2];
    }
  }

  cv::imwrite(dst, img2);
  return 0;
}
 
int main(int argc, char* argv[])
{
/*
*   This program reads an image and store it's content in a new image 
*/
  int i;
  if (argc != 3){
    std::cout << "WRONG NUMBER OF ARGUMENTS" << std::endl;
    return 1;
  } 
  if (image(argv[i+1],argv[i+2])){
    return 1;
  }
  return 0;
}
