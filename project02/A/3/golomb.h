#pragma once
#include "bitStream.h"
#include <iostream>
#include <vector>
#include <cmath>
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
    void decode(char* filename,int m);
};

template <typename T>
void Golomb::encode(T data,bool end){
  printf("%d\n",data);
  int q = data / (this->m);
  int r = data % (this->m);
  std::cout << "q: " <<q << " r: " << r << std::endl; 
  /// primeiro tratamento do sinal
  uint8_t signal = 0;
  if (r < 0 || q < 0){
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
  

  /// write binary code
  //int n = std::ceil(LOG2(r))/1;
  
  this->bs.writeNBits(r,8); 
  if (end) {
    this->bs.write2File();
    this->bs.close('w');
  }
} 



void Golomb::decode(char* filename,int m){
  this->m = m;
  BitStream bs(filename,'r');
  bs.readFromFile2Buffer();
  //std::reverse(buff.begin(), buff.end());

  int q = 0;
  int r = 0;
  bool signal = 0;
  int val = 0;
  int cnt = 0;

  bs.printBuffer();
  printf("\n");
  while(bs.getBufferSize() > 0){
    q = bs.getUnary();
    // encontar sinal
    signal = bs.readSignal();
    // encontrar r 
    r = bs.readNBits(8);
    if (signal) val = -1*(q*m+r);
    else        val = q*m +r;

    printf("q: %d r: %d val: %d\n",q,r,val);
    cnt += 1;
  }
}



