#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

void readPPM(const char* filename,const char* filename2,int *width, int *height, int *mx) {
/*
*  this program calculates the psnr of an image
*/
	FILE* f1 = fopen(filename, "rb");
  char ppm[10];
  
  // read header
	fscanf(f1, "%s", ppm);

	if (strncmp(ppm, "P6" , 10) != 0) {
		printf("They are not the same\n");
	} else {
		printf("They are the same\n");
	}

	// read width and height
	fscanf(f1, "%d\n %d\n", width, height);
  // read max pixel value
  fscanf(f1, "%d\n", mx);
  
  // check to see if they were stored properly
  printf("ppm: %s\n", ppm);
  printf("Width: %d\n", *width);
  printf("Height: %d\n", *height);
  printf("maximum: %d\n", *mx);

  int size = 3*(*width)*(*height);

  unsigned char* pixels1 = new unsigned char[size];
  
	while (fread(pixels1, sizeof(unsigned char), size, f1))
    ;
  
  int mean_rgb1[size/3];

  int j=0;
  int i;

  for (i = 0; i < size;i=i+3 ){
    mean_rgb1[j] = (pixels1[i] + pixels1[i+1] + pixels1[i+2])/3;
    j++;
  }
  
	fclose(f1);
  
  FILE* f2 = fopen(filename2, "rb");
  
  // read header
	fscanf(f2, "%s", ppm);

	if (strncmp(ppm, "P6" , 10) != 0) {
		printf("Its P6\n");
	} else {
		printf("Its not P6\n");
	}

	// read width and height
	fscanf(f2, "%d\n %d\n", width, height);
  // read max pixel value
  fscanf(f2, "%d\n", mx);
  
  // check to see if they were stored properly
  printf("ppm: %s\n", ppm);
  printf("Width: %d\n", *width);
  printf("Height: %d\n", *height);
  printf("maximum: %d\n", *mx);

  size = 3*(*width)*(*height);

  unsigned char* pixels2 = new unsigned char[size];
  
	while (fread(pixels2, sizeof(unsigned char), size, f2))
    ;

  fclose(f2);

  int mean_rgb2[size/3];
  j = 0;
  
  // calculate mean
  for (i = 0; i < size;i=i+3 ){
    mean_rgb2[j] = (pixels2[i] + pixels2[i+1] + pixels2[i+2])/3;
    j++;
  }
	
  double e_rgb = 0; // squared error 

  for (i=0; i < size/3; i++){
    e_rgb = e_rgb + pow((mean_rgb1[i]-mean_rgb2[i]),2);
  }
  e_rgb = e_rgb/(size/3);
  double max_val = pow(255,2); 
   
  double psnr = 10*log(max_val/e_rgb)/std::log(10);
  
  std::cout << "psnr " << psnr << std::endl; 
}

int main(int argc, char* argv[]){
 
  int width;
  int height;
  int mx;
  readPPM(argv[1],argv[2],&width,&height,&mx);
  
  
  return 0;

}
