#include<iostream>
#include<opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
  if (argc < 3){
    std::cout << "Wrong Input Arguments" << std::endl;
    return -1;

  }
  cv::Mat img;
  img = cv::imread(argv[1]);
  
  if (img.empty()) //check whether the image is loaded or not
  {
    std::cout << "Error : Image cannot be loaded..!!" << std::endl;
    return -1;
  }
  
  cv::Mat img2 = cv::Mat::zeros(cv::Size(img.rows, img.cols), CV_8UC3);
  
  for (int y = 0; y < img.rows; y++){
    for (int x = 0; x < img.cols; x++){
      img2.at<cv::Vec3b>(y,x)[0] = img.at<cv::Vec3b>(y,x)[0];
      img2.at<cv::Vec3b>(y,x)[1] = img.at<cv::Vec3b>(y,x)[1];
      img2.at<cv::Vec3b>(y,x)[2] = img.at<cv::Vec3b>(y,x)[2];
    }
  }

  cv::imwrite(argv[2], img2);

  return 0;
}
