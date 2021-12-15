#include "golomb.h"
#include <fstream>
#include <iostream>
int main(int argc, char* argv[]){
  /*
  BitStream bs;
  uint8_t v = 10;
  printf("v: %d\n",v);
  bs.setByte(&v,0);
  printf("v: %d\n",v);
  bool is_1_or_0;
  is_1_or_0 = bs.readByte(v,0);
  printf("1 or 0: index 0: %d\n",is_1_or_0);
  is_1_or_0 = bs.readByte(v,1);
  printf("1 or 0: index 1: %d\n",is_1_or_0);
  is_1_or_0 = bs.readByte(v,2);
  printf("1 or 0: index 2: %d\n",is_1_or_0);
  bs.printBit(v);
  */
  
  Golomb gb("test.out",4);

  std::ifstream ifs("test.in");
  int val;
  int i = 0 ;
  while (ifs >> val) {
    //std::cout << val << std::endl;
    if (i == 4)
      gb.encode(val,1); 
    else gb.encode(val);
    i++;
  }


  return 0;
}
