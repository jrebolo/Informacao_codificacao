#include "fcm.h"
#include <getopt.h>

int main(int argc,char* argv[]){
  
  double entropy;
  std::string filename;
  int opt,h,f;
  int k = 1;
  double a = 0.1;
  while ((opt = getopt(argc,argv,"hf:a:k:")) != EOF){
    switch(opt){
        case 'a': 
                  a = atof(optarg); 
                  if (a <= 0) a = 0.1;
                  break;
        case 'k': 
                  k = atoi(optarg);
                  if (k <= 0) k = 1;
                  break;
        case 'f': 
                  filename = optarg; 
                  std::cout << filename << "\n";
                  break;
        case 'h': fprintf(stderr, "usuage is \n -a : <value> \n -f : [filename] \n -k: <value> \n");
                  break;
    }
  }

  Fcm fcm;
  if(fcm.open(filename)){
    printf("Could not open file\n");
    return -1;
  }
  fcm.save_text();
  fcm.count_depth(k,a);
  fcm.entropy();
  return 0;
}
