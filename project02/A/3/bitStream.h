#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <math.h> 

/*
https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit/47990#47990

setting a bit:             number |= 1UL << n
Clearing a bit:            number &= ~(1UL << n)
Toggling a bit:            number ^= 1UL << n
Checking a bit:            bit = (number >> n) & 1U
Changing the nth bit to x: number ^= (-x ^number) & (1UL << n)

This program can reads binary files and stores it in a unsigend char array with a size of maximum of 1024

- It can read every byte of each unsigend char in the buffer array

*/

class BitStream {
  private:
    std::ofstream ofs;
    std::ifstream ifs;
    std::vector<uint8_t> buffer;
    int pointer = 0;
    uint8_t bit = 0;
    int bit_pointer = 7;
  public:
    BitStream(){}
    BitStream(char* filename,char condition){
      if (condition == 'r')
        this->ifs.open(filename,std::ios::binary);
      else if (condition == 'w')
        this->ofs.open(filename, std::ios::binary);
      this->bit_pointer = 7;
    }
    BitStream(char* filename1, char* filename2){
      this->ifs.open(filename1, std::ios::binary);
      this->ofs.open(filename2, std::ios::binary);
    }
    ~BitStream(){
      this->ofs.close();
      this->ifs.close();
    }
    void setBit();
    void movePointer();
    template<typename T>
    bool readByte(T v,uint8_t i);
    void printBit(uint8_t v);
    void write();
    void write2Buffer(uint8_t v);
    void flush();
    void close(char condition);
    std::vector<uint8_t> getBuffer();
    void writeBit(uint8_t v);
    void open(char *filename,char condition);
    template <typename T>
    T read(T buffer);
    uint8_t getBitPointer();
};

uint8_t BitStream::getBitPointer(){
  return this->bit_pointer;
}

std::vector<uint8_t> BitStream::getBuffer(){
  return this->buffer;
}

void BitStream::open(char * filename,char condition){
  if (condition == 'r')
    this->ifs.open(filename,std::ios::binary);
  else if (condition == 'w')
    this->ofs.open(filename, std::ios::binary);


}

void BitStream::movePointer(){
  if (this->bit_pointer < 0) {
    this->write2Buffer(this->bit);
    this->bit_pointer = 7;
    this->bit = 0;
  }
  else this->bit_pointer--;
}

void BitStream::setBit(){
  /// set a bit value to 1 in the index i
  if (this->bit_pointer < 0){
    this->bit = 0;
    this->bit_pointer = 7;
  }
  this->bit |= 1 << this->bit_pointer;
  this->bit_pointer--;
}
// é preciso ter em conta que só lê valores até 256
template <typename T>
bool BitStream::readByte(T v, uint8_t i){
  /// read the value of a byte in a bit of index i
  return (v >> i) & 1;
}


void BitStream::printBit(uint8_t v){
  int i;
  for(i=7;i>=0;i--){
    if (this->readByte(v,i)) printf("1");
    else                     printf("0");
  }
  printf("\n");
}

template <typename T>
void BitStream::writeNBits(T data, uint8_t n){
  int i;
  for (i=n; i >= 0;i--){
    if (this->readByte(data,i)) this->setBit();
    else                        this->movePointer();
  }
}

void BitStream::writeBit(uint8_t v){
  int i;
  for(i=7;i>=0;i--){
    if (this->readByte(v,i)) this->setBit();
    else                     this->movePointer();
  }
  
}

void BitStream::write(){
  this->write2Buffer(this->bit);
  int i;
  for(i = 0; i < this->buffer.size();i++)
    this->ofs << buffer[i];
  this->flush();
}

void BitStream::write2Buffer(uint8_t v){
  (this->buffer).push_back(v);
  (this->pointer)++;
}

void BitStream::flush(){
  (this->buffer).clear();
  this->pointer = 0;
}

template <typename T>
T BitStream::read(T buffer){
  /// give one buffer to read from file the same size of buffer
  return this->ifs.read(&buffer,sizeof(T));
}

void BitStream::close(char condition){
  if (condition == 'w')      this->ofs.close();
  else if (condition == 'r') this->ifs.close();
}
