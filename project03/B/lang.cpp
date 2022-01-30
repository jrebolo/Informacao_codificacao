#include "lang.h"
#include <getopt.h>
int main(int argc,char* argv[]){
  
  int n_files = 0;
  std::vector<std::string> filenames;
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
                  n_files +=1;
                  filenames.push_back(optarg);
                  break;
        case 'h': fprintf(stderr, "usuage is \n -a : <value> \n -f : [filename] \n -k: <value> \n");
                  break;
    }
  }

  if (n_files != 2){
    std::cout << "Need to give 2 files" << "\n"; 
    return -1;
  }

  Lang lang(k,a);
  lang.create_matrix(filenames[0]);
  lang.compare(filenames[1]);
  return 0;
}

