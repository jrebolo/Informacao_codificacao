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
  std::vector<uint8_t> buff = bs.writeFromFile2Buffer();
  std::reverse(buff.begin(), buff.end());

  int i=7,ii;
  int q = 0;
  uint8_t r = 0;
  int signal = 0;
  uint8_t byte;
  bool f1=0,f2=0,f3=1;
  bool bit;
  int val = 0;
  int cnt = 0;
  int cnt2 = 0;
  byte = buff[buff.size()-1];
  bs.printBit(byte);
  buff.pop_back();
  while(buff.size()){
    if (i < 0){
      byte = buff[buff.size()-1];
      bs.printBit(byte);
      buff.pop_back();
      i = 7;
    }
    if (f1 == 0 && f2 == 0){
      bit = bs.readBit(byte,i);
      i--;
      if (bit){
        q += 1;
      }
      else {
        f1 = 1;
      }
    }
    // encontar sinal
    if (f1 == 1 && f2 == 0){
      if (i < 0) i = 7;
      bit = bs.readBit(byte,i);
      if (bit) signal = 1;
      i--;
      f2 = 1;
      f1 = 0;
    }
    // encontrar r
    if (f1 == 0 && f2 == 1){
      if (i < 0) i = 7;
      bit = bs.readBit(byte,i);
      if (cnt2 == 4){
        bs.printBit(byte);
        printf("bit: %d size: %d \n",bit,buff.size());
      }
      bs.writeBit2Val(bit);
      cnt += 1;
      i--;
      if (cnt == 8){
        f2 = 1;
        f1 = 1;
        cnt = 0;
        r = bs.getByteFromBuffer();
      }
    }

    if (f1 == 1 && f2 == 1){
      if (signal == 1) {
        val = (-1)*q*m;
        val += (-1)*r;
      }
      else 
        val = q*m + r;
      printf("q: %d r: %d m: %d\n",q,r,m);
      printf("decoded value: %d\n",val);
      f1 = 0;
      f2 = 0;
      cnt = 0;
      signal = 0;
      q = 0;
      cnt2 += 1;
    }
  }
}



