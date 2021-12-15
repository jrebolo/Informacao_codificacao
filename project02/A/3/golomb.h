#pragma once
#include "bitStream.h"
#include <iostream>
#include <math.h>

#define LOG2(x) (std::log((x))/std::log(2))

class Golomb{
  public:
    int m;
    char *filename_out;
    BitStream bs;
    Golomb(char* filename_out,uint32_t m){
      this->filename_out = filename_out;
      this->m = m;
      this->bs.open(filename_out,'w');
    }
    ~Golomb(){}
    
    template <typename T>
    void encode(T data,bool end=0);
    void decode();
};

template <typename T>
void Golomb::encode(T data,bool end){
  printf("%d\n",this->bs.getBitPointer());
  int q = data / (this->m);
  int r = data % (this->m);
  std::cout << "q: " <<q << " r: " << r << std::endl; 
  /// primeiro tratamento do sinal
  uint8_t signal = 0;
  if (q < 0){
    signal = 1;
    q = -1*q;
    r = -1*r;
  }
  
  /// escrever o codigo unario
   
  int cnt,i;
  uint8_t bit = 0;
    
  for (cnt = 0;cnt < q ;cnt++){
    /// set bits to q bits to 1
    this->bs.setBit();
  }
  /// write 0 to end unary code
  this->bs.movePointer();

  /// write signal
  if (signal) this->bs.setBit();
  else        this->bs.movePointer();
  
  // writeNbits criar

  /// write binary code
  this->bs.writeNBits(r,LOG2(this->m)/1); 
  
  if (end) {
    int i;
    std::vector<uint8_t> b = this->bs.getBuffer();
    for (i = 0; i < b.size();i++){
      std::cout << b[i] << std::endl;
    }
    this->bs.write();
    this->bs.close('w');
  }
} 



void Golomb::decode(){

  

}



