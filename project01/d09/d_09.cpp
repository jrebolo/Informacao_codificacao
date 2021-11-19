#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
unsigned char* readPPM(const char* filename,const char* filename2,int *width, int *height, int *mx) {
/*
*  This program reduce the number of bits used in an image 
*/
	FILE* f = fopen(filename, "rb");
  char ppm[10];
  
  // read header
	fscanf(f, "%s", ppm);

	if (strncmp(ppm, "P6" , 10) != 0) {
		printf("Its P6\n");
	} else {
		printf("Its not P6");
	}

	// read width and height
	fscanf(f, "%d\n %d\n", width, height);
  // read max pixel value
  fscanf(f, "%d\n", mx);
  
  // check to see if they were stored properly
  printf("ppm: %s\n", ppm);
  printf("Width: %d\n", *width);
  printf("Height: %d\n", *height);
  printf("maximum: %d\n", *mx);

  int size = 3*(*width)*(*height);

  unsigned char* pixels = new unsigned char[size];
  
	while (fread(pixels, sizeof(unsigned char), size, f))
    ;
  
  unsigned char red[size/3];
  unsigned char green[size/3];
  unsigned char blue[size/3];
  
  int j=0;
  int i;

  for (i = 0; i < size;i=i+3 ){
    red[j] = (pixels[i] >> 1) << 1;
    green[j] = (pixels[i+1] >> 1) << 1;
    blue[j] = (pixels[i+2]  >> 1) << 1;
    j++;
  }
  
	fclose(f);

  std::ofstream ofs(filename2, std::ios_base::out | std::ios_base::binary);
    ofs << "P6" << std::endl << *width << ' ' << *height << std::endl << "255" << std::endl;
 
  for (i=0;i < size/3;i++){
     ofs << (char) red[i] << (char) green[i]  << (char) blue[i];
  }
  
  ofs.close();



	return pixels;

}

int main(int argc, char* argv[]){
 
  int width;
  int height;
  int mx;
  unsigned char* pixels = readPPM(argv[1],argv[2],&width,&height,&mx);
  
  
  return 0;

}
