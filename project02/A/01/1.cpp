#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include "bitStream.h"

int main(int argc,char* argv[]){
  
  unsigned char bit;
  BitStream bs("bits.bin",'r');
  
  /*  
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(1);
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(1);
  bs.writeBit(1);
  bs.printBuffer();  
  */
  
  bit = bs.readBit(2);
  printf("%d\n",bit);
  bs.printBuffer();
  bs.close();
  return 0;
}
