#include "golomb.h"

int main(int argc, char* argv[]){
  printf("------------\n"); 
  printf("Encode\n"); 
  printf("------------\n"); 

  Golomb gb(4);
  std::ifstream ifs("test.in");
  int val;
  while (ifs >> val) {
    std::cout << val << std::endl;
    gb.encode(val);
  }
  gb.write("test.out",'e');
  printf("------------\n"); 
  printf("Decode\n"); 
  printf("------------\n"); 
  gb.decode("test.out");
  gb.write("test_decode.out",'d');
  ifs.close();
  return 0;
}
