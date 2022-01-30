#pragma once

#pragma once

#include <stdlib.h>
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include "fcm.h"

#define LOG2(x) std::log(x)/std::log(2)


class Lang{

  public:
    Fcm fcm;
    std::string text1;
    std::string text2;
    int k;
    double alpha;
    Lang(int k, double alpha){ 
      this->k = k;
      this->alpha = alpha;
    }
    int open(std::string text);
    void create_matrix(std::string text);
    double compare(std::string text);


};

int Lang::open(std::string text){
  if(this->fcm.open(text)){
    printf("Could not open file\n");
    return -1;
  }
  
  this->fcm.save_text();
  this->fcm.close();
  return 0;
}

void Lang::create_matrix(std::string text){
  this->open(text);
  this->fcm.count_depth(this->k,this->alpha);
}

double Lang::compare(std::string text){

  
  std::ifstream ifs(text);
  std::vector<char> buffer(k);
  int i,j;
  char ch;
  for(i=0 ; i < k;i++){
    ifs.get(ch);
    buffer[i] = ch;
  }
  

  std::string word;
  double pb;
  double nbits = 0.0;
  int index;
  while(ifs.get(ch)){ 
    word = this->fcm.get_word_from_buffer(buffer);
    if (this->fcm.matrix[word.c_str()].size() != 0){
      index = this->fcm.char_to_index(ch);
      if (index == -1) continue;
      pb = this->fcm.matrix[word][index];
      nbits += -1.0*LOG2(pb);
    }
    for(j = 0; j < this->k - 1; j++)
      buffer[j] = buffer[j+1];
    buffer[this->k-1] = ch;
  }
  
  std::cout << "Number of bits: " << nbits << "\n";
  ifs.close(); 
  return nbits;
}
