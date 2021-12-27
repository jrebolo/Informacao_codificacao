#include "bitStream.h"

int main(int argc, char* argv[]){
  
  BitStream bs;
  //bs.open(argv[1],'w');


  // write 1 in binary
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(0);
  bs.writeBit(1);
  bs.writeBit(1);
  bs.write2File(argv[1],'e'); 
  bs.close('w');
  


  // read the binary file
  bs.open(argv[1],'r');
  bs.readFromFile2Buffer();
  int val = bs.readNBits(8);
  
  bs.decoded_values.push_back(val);
  
  bs.write2File(argv[2],'d'); 
  bs.close('w');
  bs.close('r');
  return 0;
}
