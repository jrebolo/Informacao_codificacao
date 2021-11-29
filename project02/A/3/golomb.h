#pragma once
#include "bitStream.h"

class Golomb{
  public:
    uint32_t m;
    uint32_t q;
    uint32_t r;
    BitStream bs;
    Golomb(uint32_t m){
      this->m = m; 
    }
    ~Golomb(){}
    template <typename T>
    void encode(T n);
    template <typename T>
    T decode(T tmp);
};
template <typename T>
void Golomb::encode(T n){
  T tmp = 0;
  uint32_t q = n/(this->m);
  printf("q: %d\n",q);
  this->bs.writeBits(&tmp,0,q,1);
  this->q = this->bs.readBits(tmp,0,32);
  this->r = n-q*(this->m);
}

template <typename T>
T Golomb::decode(T tmp){
  int cnt=0;
  int i;
  for(i=0;i < sizeof(tmp)*8;i++){
    if (this->bs.readBit(this->q,i))
      cnt++;
  }
  return cnt*(this->m)+(this->r);
}

