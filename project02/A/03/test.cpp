#include "golomb.h"

int main(int argc, char* argv[]){
  printf("------------\n"); 
  printf("Encode\n"); 
  printf("------------\n"); 

  Golomb gb(5);
  std::ifstream ifs("buff.txt");
  int val;
  while (ifs >> val) {
    //std::cout << val << std::endl;
    gb.encode(val);
  }
  gb.write("test.bin",'e');
  printf("------------\n"); 
  printf("Decode\n"); 
  printf("------------\n"); 

  gb.decode("test.bin");
  gb.write("test_decode.out",'d');

  ifs.close();
  /*
  std::ifstream ifs2("test_decode.out");
  int val2;
  while(ifs2 >> val2){
    std::cout << val2 << std::endl;    
  }
  ifs2.close();
  */
  return 0;
}
