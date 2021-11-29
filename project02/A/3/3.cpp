#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include "bitStream.h"
#include "golomb.h"

template <typename T>
void print_bit(T b){
  int i;
  for (i=sizeof(b)*8-1;i>=0;i--){
    if((b >> i) & 0x01){
      printf("1");
    }else{
      printf("0");
    }
  }
  printf("\n");
}


int main(int argc,char* argv[]){
  uint8_t tmp = 10;
  printf("number: %d\n",tmp);
  print_bit(tmp);
  Golomb gl(4);
  gl.encode(tmp);
  print_bit(gl.r);
  printf("r: %d\n",gl.r);
  print_bit(gl.q);
  printf("q: %d\n",gl.q);
  tmp = gl.decode(tmp);
  print_bit(tmp);
  printf("----------------------\n");
  
  uint32_t tmp2 = 1000;
  printf("number: %d\n",tmp2);
  print_bit(tmp2);
  Golomb gl2(50);
  gl2.encode(tmp);
  print_bit(gl2.r);
  printf("r: %d\n",gl2.r);
  print_bit(gl2.q);
  printf("q: %d\n",gl2.q);
  tmp = gl2.decode(tmp);
  print_bit(tmp2);

  

  return 0;

}

