#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <math.h> 
#include <cmath>

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
    uint8_t byte = 0;
    int byte_pointer = 7;
  public:
    BitStream(){}
    BitStream(char* filename,char condition){
      if (condition == 'r')
        this->ifs.open(filename,std::ios::binary);
      else if (condition == 'w')
        this->ofs.open(filename, std::ios::binary);
      this->byte_pointer = 7;
    }
    BitStream(char* filename1, char* filename2){
      this->ifs.open(filename1, std::ios::binary);
      this->ofs.open(filename2, std::ios::binary);
    }
    ~BitStream(){
      this->ofs.close();
      this->ifs.close();
    }
    template <typename T>
    void writeNBits(T data, uint8_t n); 
    void setBit();
    void movePointer();
    template<typename T>
    bool readBit(T v,uint8_t i);
    void printBit(uint8_t v);
    void write2File();
    void write2Buffer(uint8_t v);
    void flush();
    void close(char condition);
    std::vector<uint8_t> getBuffer();
    void writeByte(uint8_t v);
    void open(char *filename,char condition);
    template <typename T>
    void read(T *buffer);
    uint8_t getBitPointer();
    std::vector<uint8_t> writeFromFile2Buffer();
    void writeBit2Val(bool bit);
    void printBuffer();
    uint8_t getByte();
    uint8_t getByteFromBuffer();
};

uint8_t BitStream::getByteFromBuffer(){

  return this->buffer[this->buffer.size()-1];
}

uint8_t BitStream::getBitPointer(){
  return this->byte_pointer;
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
  if (this->byte_pointer - 1 < 0){
    this->write2Buffer(this->byte);
    this->byte_pointer = 7;
    this->byte = 0;
  }
  else this->byte_pointer--;
}

void BitStream::setBit(){
  /// set a bit value to 1 in the index i
  if (this->byte_pointer < 0)  this->write2Buffer(this->byte);
  this->byte |= 1 << this->byte_pointer;
  this->movePointer();
}
// é preciso ter em conta que só lê valores até 256
template <typename T>
bool BitStream::readBit(T v, uint8_t i){
  /// read the value of a bit in a byte of index i
  return (v >> i) & 1;
}

void BitStream::printBuffer(){
  int i;
  for (i=0;i < this->buffer.size();i++){
    this->printBit(buffer[i]);
  }
}

void BitStream::printBit(uint8_t v){
  int i;
  for(i=7;i>=0;i--){
    if (this->readBit(v,i)) printf("1");
    else                     printf("0");
  }
  printf("\n");
}

template <typename T>
void BitStream::writeNBits(T data, uint8_t n){
  int i;
  bool bit;
  for (i=n-1; i >= 0;i--){
    bit = this->readBit(data,i);
    if (bit) this->setBit();
    else     this->movePointer();
  }
}


void BitStream::writeByte(uint8_t v){
  int i;
  for(i=7;i>=0;i--){
    if (this->readBit(v,i)) this->setBit();
    else                     this->movePointer();
  }
}


void BitStream::write2Buffer(uint8_t v){
  (this->buffer).push_back(v);
  (this->pointer)++;
}

std::vector<uint8_t> BitStream::writeFromFile2Buffer(){
  char c;
  int i;
  while(this->ifs.get(c)){
    this->buffer.push_back(c);
  }
  return this->buffer;
}

void BitStream::writeBit2Val(bool bit){
  if (bit){
    this->byte |= 1 << this->byte_pointer;
    this->movePointer();
  }
  else{
    this->movePointer();
  }
}

void BitStream::write2File(){
  if (this->byte_pointer != 7) this->buffer.push_back(this->byte);
  int i;
  for(i = 0; i < this->buffer.size();i++)
    this->ofs << buffer[i];
  this->flush();
}

void BitStream::flush(){
  (this->buffer).clear();
  this->pointer = 0;
}

template <typename T>
void BitStream::read(T *buffer){
  /// give one buffer to read from file the same size of buffer
  this->ifs.read(*buffer,sizeof(T));
}

void BitStream::close(char condition){
  if (condition == 'w')      this->ofs.close();
  else if (condition == 'r') this->ifs.close();
}

uint8_t BitStream::getByte(){
  return this->byte; 
}
