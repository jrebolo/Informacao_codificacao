#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>

#define BUFFERSIZE 1024

/*
https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit/47990#47990

setting a bit:             number |= 1UL << n
Clearing a bit:            number &= ~(1UL << n)
Toggling a bit:            number ^= 1UL << n
Checking a bit:            bit = (number << n) & 1U
Changing the nth bit to x: number ^= (-x ^number) & (1UL << n)

This program can reads binary files and stores it in a unsigend char array with a size of maximum of 1024

- It can read every byte of each unsigend char in the buffer array

*/

class BitStream{
  public:
    uint8_t arr_b;
    unsigned char buf[BUFFERSIZE] = {0};
    int cnt;
    int cnt_b;
    FILE* f;
    size_t bytes = 0;
    size_t readsz = sizeof(buf);
    BitStream(const char *filename,char t) {     // Constructor
      if (t == 'r') {
        try {
          this->f = fopen(filename,"rb");
          while ((bytes = fread(buf, sizeof(*buf), readsz, f)) == readsz)
            ;
        } catch( int e) {
          throw "CANT OPEN FILE";      
        }
      }
      if (t == 'w') this->f = fopen(filename,"wb");
      this->cnt = 0;
      this->arr_b = 0;
    }
    ~BitStream(){     // Destructor
    }
    void writeBit(uint8_t b);
    void printBuffer();
    unsigned char readBit(int n);
    void close();
};



unsigned char BitStream::readBit(int n){
  //char c;
  //fread(&c, sizeof(uint8_t), 1, f);
  //printf("%c %d %x \n",c,c,c);;
  //this->arr_b = (uint8_t)c;
  //printf("%d %d\n",((this->arr_b)/8 >> n%8) & 1,((c)/8 >> n%8) & 1); // gets the specified bit
  this->arr_b = buf[this->cnt];
  return ((this->arr_b)/8 >> n%8) & 1;
}


void BitStream::writeBit(uint8_t b){
  if (b==1){
    this->arr_b |= ((uint8_t)0x00000001 << this->cnt);
    this->cnt++;
  }else
    this->cnt++;
  //b &= ~((uint8_t)0x00000001 << N)
}

void BitStream::close(){
  fclose(this->f);
}

void BitStream::printBuffer(){
  int i;
  for (i=7;i>=0;i--){
    if((this->arr_b >> i) & 0x1){
      printf("+");
    }else{
      printf(".");
    }
  }
  printf("\n");
}

