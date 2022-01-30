#include "lang.h"
#include <getopt.h>



void comparar(std::vector<std::string> languages,int k, double alpha){

  int i;
  std::vector<int> r1_bits;

  int n = languages.size();
  double nbits;
  int mn = 1e9;
  int idx = 0;
  for(i=0; i < languages.size()-1; i++ ){
    Lang lang(k,alpha);
    lang.create_matrix(languages[i]);
    nbits = lang.compare(languages[n-1]);
    r1_bits.push_back(nbits);
    if (nbits < mn) {
      mn = nbits;
      idx = i;
    }
  }
  
  std::cout << "the text is more correlated to the r1 " << languages[idx] << " with " << mn << " bits." << "\n"; 

}


int main(int argc, char* argv[]){
  std::vector<std::string> filenames;
  int n_files = 0;
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
                  n_files += 1;
                  filenames.push_back(optarg);
                  break;
        case 'h': fprintf(stderr, "usuage is \n -a : <value> \n -f : [filename] \n -k: <value> \n");
                  break;
    }
  }
  if (n_files < 2){
    std::cout << "need to give atleast 2 files" << "\n";
    return -1;
  }

  comparar(filenames,k,a);
  return 0;
}
