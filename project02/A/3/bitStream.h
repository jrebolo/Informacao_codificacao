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
  private:
    typedef std::vector<uint8_t> v_bytes;
    v_bytes buffer;
    uint8_t pointer = 0;
    const char* filename;
    const char type;
    std::ifstream input;
    std::ofstream output;
  public:

    BitStream(const char* filename,const char type){
      this->filename = filename;
      this->type = type;
      if (type == 'r') this->input(filename,std::ios::binary);
      if (type == 'w') this->output(filename,std::ios::binary);
    }
    ~BitStream(){
      if (input.is_open())  input.close;
      if (output.is_open()) output.close;
    }
  
    void readToBuffer();
    void flush();
    template <typename T>
    bool readBit(const T data, const uint32_t i); 
    template <typename T>
    T readBits(const T data,const uint32_t i, const uint32_t n);

    template <typename  T>
    void writeBit(T *data,const uint32_t i,const bool bit);
    template <typename T>
    void writeBits(T *data, const uint8_t i, const uint8_t n,const bool bit);
    
};

void BitStream::readToBuffer(){
  char byte;
  if (input.get(byte)) this->buffer.push_back(byte);
}

void BitStream::flush(){}

template <typename T>
bool BitStream::readBit(const T data,const uint32_t i){
  if (this->pointer == 0) this->readToBuffer();
  if ((this->pointer) == this->buffer.size() * 8) this->flush();
  return data & (1 << i);//(data >> i%8) & 1;
}

template <typename T>
T BitStream::readBits(const T data,const uint32_t i, const uint32_t n){
  uint32_t tmp = 0;
  bool tmp2;
  uint32_t ii;
  for(ii = i;ii < n;ii++){
    tmp2 = this->readBit(data,ii);
    this->writeBit(&tmp,ii,tmp2);
  }
  return tmp;
}

template <typename T>
void BitStream::writeBit(T *data,const uint32_t i,const bool bit){
  if (bit == 1)
    *data |= 1UL << i;
  else if (bit == 0)
    *data &= ~(1UL << i);
}
template <typename T>
void BitStream::writeBits(T *data, const uint8_t i, const uint8_t n,const bool bit){
  int ii;
  for(ii=i; ii < n; ii++)
    this->writeBit(data,ii,bit);
}


