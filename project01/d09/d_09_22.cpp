#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

int main(int argc,char* argv[]){
  int *width;
  int *height;
  int *mx;

	FILE* f = fopen(argv[1], "rb");
  char ppm[10];
  
  // read header
	fscanf(f, "%s", ppm);

	if (strncmp(ppm, "P6" , 10) != 0) {
		printf("They are not the same\n");
	} else {
		printf("They are the same\n");
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
    red[j] = pixels[i];
    green[j] = pixels[i+1];
    blue[j] = pixels[i+2];
    j++;
  }

  fclose(f); 
  /* 

  std::ofstream fo(argv[2], std::ios::out | std::ios::binary);
  if(!fo) {
    std::cout << "Cannot open file!" << std::endl;
      return 1;
  }
   
  fo << "P6\n" << width << " " << height << "\n" << "255\n"; 
  for (i=0;i < size;i=i+3){
    fo << red[i];
    fo  << " ";
    fo << green[i];
    fo  << " ";
    fo << blue[i];
    if (i == size-1) continue;
    fo  << " ";
  }
  
  fo.close();
  */
  return 0;
}
