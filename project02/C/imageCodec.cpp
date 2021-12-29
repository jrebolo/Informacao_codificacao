#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include "golomb.h"

using namespace std;

vector<u_char> y;
vector<u_char> u;
vector<u_char> v;


unsigned char* convert2YUV(const char* filename, int *width, int *height, int *mx) {
   
    FILE* f = fopen(filename, "rb");
    char ppm[10];
  
    // read header
	fscanf(f, "%s", ppm);

	if (strncmp(ppm, "P6" , 10) != 0) {
		printf("Its not P6\n");
	} else {
		printf("Its P6\n");
	}

	// read width and height
	fscanf(f, "%d\n %d\n", width, height);
    // read max pixel value
    fscanf(f, "%d\n", mx);
    
    // check to see if they were stored properly
    /* printf("ppm: %s\n", ppm);
    printf("Width: %d\n", *width);
    printf("Height: %d\n", *height);
    printf("maximum: %d\n", *mx);
    */

    int size = 3*(*width)*(*height);

    unsigned char* pixels = new unsigned char[size];
  
    while (fread(pixels, sizeof(unsigned char), size, f));
  
  
    int i,j;
    u_char r, g, b;
    u_char maty, matu, matv;

    for (i = 0; i < *height; i=i+1){        //linha
        for(j = 0; j < *width*3; j=j+3) {   //coluna
            r = pixels[i*(*width)+j];
            g = pixels[i*(*width)+j+1];
            b = pixels[i*(*width)+j+2];

            maty = 0.299*r + 0.587*g + 0.114*b;

            if(i%2 == 0 && (j/3)%2 == 0) {
                matu = 0.492*(b - maty);
                matv = 0.877*(r - maty);

                u.push_back(matu);
                v.push_back(matv);
            }
            y.push_back(maty);
        }
    }
  
	fclose(f);
	return pixels;

}

void convert2RGB(){
   
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
    return x;
}


void encode(char* filename, int m){
    Golomb gb(m);
}

void decode(char* filenameIn, char* filenameOut, int m){
    Golomb gb(m);
} 

int main(int argc, char* argv[]){

    if (argc != 2)
    {
        cout << "USAGE: ./ex1 <path to image>" << endl;
        exit(1);
    }
    
    int width, heigth, mx;

    unsigned char* pixels = convert2YUV(argv[1], &width, &heigth, &mx);

    
    return EXIT_SUCCESS;
}
