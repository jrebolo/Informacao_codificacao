#pragma once
#include "bitStream.h"
#include <iostream>
#include <vector>
#include <cmath>
#define LOG2(x) (std::log((x))/std::log(2))

class Golomb{
  public:
    int m = 0;
    BitStream bs;
    Golomb(uint32_t m){
      this->m = m;
    }
    ~Golomb(){}
    
    template <typename T>
    void encode(T data);
    void decode(std::string filename);
    void write(std::string filename,char mode);
    void open(std::string filename, char mode);
    void read(std::string filename);
};

void Golomb::open(std::string filename, char mode){
  this->bs.open(filename,mode);
}


template <typename T>
void Golomb::encode(T data){
  int q = data / (this->m);
  int r = data % (this->m);
  /// primeiro tratamento do sinal
  uint8_t signal = 0;
  if (r < 0 || q < 0){
    signal = 1;
    q = -1*q;
    r = -1*r;
  }
  
  /// escrever o codigo unario   
  int cnt;    
  for (cnt = 0;cnt < q ;cnt++){
    /// set bits to q bits to 1
    this->bs.writeBit(1);
  }

  /// write 0 to end unary code
  this->bs.writeBit(0);

  /// write signal
  this->bs.writeBit(signal);
  
  /// write binary code
  int n = LOG2(this->m-1)/1 + 1;
  this->bs.writeNBits(r,n); 
} 

void Golomb::decode(std::string filename){

  
  BitStream bs(filename,'r');
  /// read encoded file to a buffer
  bs.readFromFile2Buffer();

  int q = 0;
  int r = 0;
  bool signal = 0;
  int val = 0;
  int n;
  
   
  while(bs.getBufferSize() > 0){
    /// read from the encode buffer until it finds an 0
    q = bs.getUnary();
    // encontar sinal
    signal = bs.readEncodeBuffer();
    // encontrar r acho que n é necessário dividir por 1 para obter um inteiro  
    n = LOG2(this->m-1)/1 + 1;
    r = bs.readNBits(n);
    if (signal) val = -1*(q*(this->m)+r);
    else        val = q*(this->m) +r;
    bs.decoded_values.push_back(val);
  }
}


void Golomb::write(std::string filename,char mode){
  if (mode == 'e'){
    this->bs.write2File(filename,mode);
    this->bs.close('w');
  }
  else if(mode == 'd'){
    this->bs.write2File(filename,mode);
    this->bs.close('w');
  }
}
