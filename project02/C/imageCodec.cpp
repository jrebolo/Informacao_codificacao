#include <string>
#include <stdio.h>
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "golomb.h"

using namespace cv;
using namespace std;


void convert2YUV(Mat img, Mat &y, Mat &u, Mat &v){

    for( int line = 0; line < img.rows; ++line )
    {
        if( !(line % 2) )
        {
            for( int x = 0; x < img.cols; x += 2 )
            {
                double r = img.at<Vec3b>(line,x)[0];
                double g = img.at<Vec3b>(line,x)[1];
                double b = img.at<Vec3b>(line,x)[2];

                int maty = (66*r + 129*g + 25*b) + 16;
                int matu = (-38*r + -74*g + 112*b) + 128;
                int matv = (112*r + -94*g + -18*b) + 128;

                y.at<uchar>(line, x) = maty;
                u.at<uchar>(line/2, x/2) = matu;
                v.at<uchar>(line/2, x/2) = matv;
                
            }
        }
        else
        {
            for( int x = 0; x < img.cols; x += 1 )
            {
                double r = img.at<Vec3b>(line,x)[0];
                double g = img.at<Vec3b>(line,x)[1];
                double b = img.at<Vec3b>(line,x)[2];

                int maty = (66*r + 129*g + 25*b) + 16;

                y.at<uchar>(line, x) = maty;
                
            }
        }
    }
}


int predictor(int a, int b, int c) {
    int x;
    if(c >= max(a,b)) {
        x = min(a,b);
    } else if(c <= min(a,b)){
        x = max(a,b);
    } else {
        x = a + b - c;
    }
}

void predictorJPEG(Mat matrix){
    int a,b,c;
    for(int i = 0; i < matrix.size().height; i++){
        for(int j = 0; j < matrix.size().width; j++){
            a = 0;
            b = 0;
            c = 0;
            
            if(i == 0 && j != 0){
                a = matrix.at<uchar>(i,j-1);
            } else if(i != 0 && j == 0){
                b = matrix.at<uchar>(i-1,j);
            } else if(i != 0 && j != 0){
                a = matrix.at<uchar>(i,j-1);
                b = matrix.at<uchar>(i-1,j);
                c = matrix.at<uchar>(i-1,j-1);   
            }

            int previsao = predictor(a,b,c);

            int pixelAtual = matrix.at<uchar>(i,j);

            .at<uchar>(i,j) = pixelAtual - previsao;
        }
    }
}

void encode(char* filename, int m){
    Golomb gb(filename, m);
}

void decode(char* filename, int m){
    Golomb gb(filename, m);
}

int main(int argc, char* argv[]){

    Mat img = imread("./imagesPPM/airplane.ppm");
    
    if (img.empty()) {
        cout << "Wrong path" << endl;
    }

    /*  Mat yuv;
    Mat again;

    cvtColor(img, yuv,COLOR_RGB2YUV_I420);
    cvtColor(yuv,again,COLOR_YUV420p2BGR); 
    imshow("teste YUV", yuv);
    imshow("teste YUV 2 RGB",again );*/

    Mat y (img.size().height, img.size().width, CV_8UC1);
    Mat u (img.size().height/2, img.size().width/2, CV_8UC1);
    Mat v (img.size().height/2, img.size().width/2, CV_8UC1);

    convert2YUV(img, y, u, v);

    /* imshow("y component",y);
    imshow("u component",u);
    imshow("v component",v); */

    


    return EXIT_SUCCESS;
}
