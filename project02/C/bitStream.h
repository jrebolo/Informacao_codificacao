#pragma once
#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <math.h> 
#include <cmath>
#include <string>
#include <queue>
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
  public:
    std::ofstream ofs;
    std::ifstream ifs;
    std::vector<uint8_t> buffer;
    std::queue<uint8_t> buffer_decode;
    std::vector<int> decoded_values;
    int pointer = 0;
    uint8_t byte = 0;
    int byte_pointer = 7;
    BitStream(){}
    BitStream(std::string filename,char condition){
      if (condition == 'r')
        this->ifs.open(filename,std::ios::binary);
      else if (condition == 'w')
        this->ofs.open(filename, std::ios::binary);
      this->byte_pointer = 7;
    }
    BitStream(std::string filename1, std::string filename2){
      this->ifs.open(filename1, std::ios::binary);
      this->ofs.open(filename2, std::ios::binary);
    }
    ~BitStream(){
      this->ofs.close();
      this->ifs.close();
    }

    /// ENCODE RELATED

    /// write 1/N bit or bits to buffer
    void writeBit(bool bit);
    template <typename T>
    void writeNBits(T data, uint8_t n); 
    
    /// read bit from a value 
    template<typename T>
    bool readBit(T v,uint8_t i);
    
    /// byte operations
    void movePointer();

    void setBit();

    /// debug tools
    void printByte(uint8_t v);
    void printBuffer();
    
    /// buffer manipulations
    void write2Buffer(uint8_t v);
    std::vector<uint8_t> getBuffer();
  
    /// file manipulation
    void write2File(std::string filename, char mode);
    void flush();
    void close(char condition);
    void open(std::string filename, char mode);
    
    /// golomb operations
    int getUnary();
    bool readSignal();
    bool readBitDecode();

    
    /// DECODE RELATED
    
    void writeByte(uint8_t v);
    bool readEncodeBuffer();

    /// read value to buffer
    template <typename T>
    void read(T *buffer);
    void movePointerOnDecode();
    int readNBits(int n);

    uint8_t getBitPointer();
    void readFromFile2Buffer();
    void writeBit2Val(bool bit);
    uint8_t getByte();
    uint8_t getByteFromBuffer();
    int getBufferSize();

};

void BitStream::write2File(std::string filename,char mode){
  if (mode == 'e'){
    this->ofs.open(filename, std::ios::binary);
    if (this->byte_pointer != 7) this->buffer.push_back(this->byte);
    int i;
    for(i = 0; i < this->buffer.size();i++)
      this->ofs << buffer[i];
    this->flush();
  }
  else if (mode == 'd'){
    this->ofs.open(filename);
    int i;
    for (i = 0; i < this->decoded_values.size(); i++){
      printf("%d\n",this->decoded_values[i]);
      this->ofs << this->decoded_values[i]; 
    }
  }
}


/// ENCODE

void BitStream::writeBit(bool bit){
  /// set one bit to 0 or 1
  if (this->byte_pointer < 0)  this->write2Buffer(this->byte);
  this->byte |= bit << this->byte_pointer;
  this->movePointer();
}

template <typename T>
void BitStream::writeNBits(T data, uint8_t n){
  int i;
  bool bit;
  /// writes n bits to the internal variavel and when full saves to buffer
  for (i=n-1; i >= 0;i--){
    bit = this->readBit(data,i);
    this->writeBit(bit);
  }
}
void BitStream::movePointer(){
  /// move byte pointer down by 1
  if (this->byte_pointer - 1 < 0){
    this->write2Buffer(this->byte);
    this->byte_pointer = 7;
    this->byte = 0;
  }
  else this->byte_pointer--;
}

template <typename T>
bool BitStream::readBit(T v, uint8_t i){
  /// read the value of a bit in a byte of index i
  return (v >> i) & 1;
}

/// DECODE

void BitStream::readFromFile2Buffer(){
  char c;
  int i;
  while(this->ifs.get(c)){
    this->buffer_decode.push(c);
  }
  this->byte = buffer_decode.front();
  this->buffer_decode.pop();
}

int BitStream::getBufferSize(){
  return this->buffer_decode.size();
}

int BitStream::getUnary(){
  int cnt = 0;
  while(this->readEncodeBuffer())
    cnt += 1;
  return cnt;
}

bool BitStream::readEncodeBuffer(){
  bool bit = this->readBit(this->byte,this->byte_pointer);
  if (this->byte_pointer == 0){
    if (buffer_decode.size() == 0) return bit; /// cant get more values from buffer
    this->byte = buffer_decode.front();
    this->buffer_decode.pop();
    this->byte_pointer = 7;
  }
  else
    this->movePointer();
  return bit;
}




int BitStream::readNBits(int n){
  int i;
  int cnt = 0;
  bool bit;
  for(i=n-1;i >= 0;i--){
    bit = this->readEncodeBuffer();
    cnt += bit*pow(2,i);
  }
  return cnt;
}


void BitStream::printBuffer(){
  int i;
  for (i=0;i < this->buffer.size();i++){
    this->printByte(this->buffer[i]);
  }
}

void BitStream::printByte(uint8_t v){
  int i;
  for(i=7;i>=0;i--){
    if (this->readBit(v,i))   printf("1");
    else                      printf("0");
  }
  printf("\n");
}


/*
*   open files
*/

void BitStream::open(std::string filename,char mode){
  if (mode == 'r')
    this->ifs.open(filename,std::ios::binary);
  else if (mode == 'w')
    this->ofs.open(filename, std::ios::binary);
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
void BitStream::read(T *buffer){
  /// give one buffer to read from file the same size of buffer
  this->ifs.read(*buffer,sizeof(T));
}

void BitStream::close(char condition){
  if (condition == 'w')      this->ofs.close();
  else if (condition == 'r') this->ifs.close();
}


