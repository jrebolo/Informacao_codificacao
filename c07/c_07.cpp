#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
unsigned char* readPPM(const char* filename,int *width, int *height, int *mx) {

	FILE* f = fopen(filename, "rb");
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

	return pixels;

}

void entropy(unsigned char* pixels,int width,int height, std::string dst){

  int i,j;
  int size = 3*width*height;  
  unsigned int red[256];
  unsigned int green[256];
  unsigned int blue[256];
  
  float p_red[256];
  float p_green[256];
  float p_blue[256];
  
  // inicializacao dos arrays rgb a 0
  for (i = 0; i < 256; i++){
    red[i] = 0;
    green[i] = 0;
    blue[i] = 0;
  }
  
  // calculo das ocorrencias de cada cor rgb
  for (i = 0; i < size; i=i+3){
    red[pixels[i]]++ ;  
    green[pixels[i+1]]++; 
    blue[pixels[i+2]]++; 
  }

  // calculo de P(x_i) para cada cor rgb
  for (i = 0; i < 256; i++){
    if (red[i] != 0)
      p_red[i] = (float)red[i]/(float)(size/3);
    if (green[i] != 0)
      p_green[i] = (float)green[i]/(float)(size/3);
    if (blue[i] != 0)
      p_blue[i] = (float)blue[i]/(float)(size/3);
  }
  
  float e_red[256];
  float e_green[256];
  float e_blue[256];
  
  // calculo da entropia to plot graph
  for (i = 0; i < 256; i++){
    if (red[i] != 0)
      e_red[i] = -p_red[i]*std::log(p_red[i])/std::log(2);
    else
      e_red[i] = 0;
    if (green[i] != 0)
      e_green[i] = -p_green[i]*std::log(p_green[i])/std::log(2);
    else
      e_green[i] = 0;
    if (blue[i] != 0)
      e_blue[i] = -p_blue[i]*std::log(p_blue[i])/std::log(2);
    else
      e_blue[i] = 0;
  }
  
  // calculo do grayscale 
  unsigned int grayscale[256];

  for (i=0;i < 256; i++){
    grayscale[i] = 0; 
  }
  for (i=0;i < 256; i++){
    grayscale[i] = (red[i]+green[i]+blue[i])/3;
  }

  // save to file values to plot histogram
  std::ofstream ofs(dst);
  if (dst.compare("") != 0){
    for (i = 0; i < 256; i++){
      ofs << red[i] << " " << green[i] << " " << blue[i] << " "<< e_red[i] << " " << e_green[i] << " " << e_blue[i] << " " <<grayscale[i] << std::endl;
    }
  }
  ofs.close();
  
  
  float rr = 0;
  float gg = 0;
  float bb = 0;
  // calculo do valor da entropia para cada valor de rgb
  for (i = 0; i < 256; i++){
    rr = rr + e_red[i];
    gg = gg + e_green[i];
    bb = bb + e_blue[i];
  }
  
  std::cout << "Entropy: "<< rr << " " << gg << " " << bb << std::endl;
}

int main(int argc, char* argv[]){
 
  int width;
  int height;
  int mx;
  unsigned char* pixels = readPPM(argv[1],&width,&height,&mx);
  
  entropy(pixels,width,height,argv[2]);

  return 0;

}
