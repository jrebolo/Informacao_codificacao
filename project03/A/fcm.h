#pragma once

#include <stdlib.h>
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

#define ALFABETO "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 "
#define ALFABETOSIZE 27 
#define LOG2(x) std::log(x)/std::log(2)


class Fcm{

  public:
    std::map<std::string, std::vector<double>> matrix;
    std::ifstream ifs;
    std::string alfabeto = ALFABETO;
    int alfabeto_size = ALFABETOSIZE;
    std::vector<char> text;
    uint32_t word_count = 0;
    std::vector<double> internal_vector;
    Fcm(){
    }    
    int char_to_index(char ch);
    double entropy();
    std::string get_word_from_buffer(std::vector<char> words);
    int open(std::string filename);
    void get_alphabet();
    int close();
    int count_depth(int k,double alpha);
    void printMatrix();
    int save_text();
};

double Fcm::entropy(){
  std::string word; 
  std::map<std::string, std::vector<double>>::iterator it = this->matrix.begin();
  double model_entropy = 0.0;
  while (it != this->matrix.end())
  {
    word = it->first;
    model_entropy += this->matrix[word][this->alfabeto_size+2];
    it++;
  }
  std::cout << "entropy of model: " << model_entropy << "\n";
  return model_entropy;
}

int Fcm::char_to_index(char ch){
  int i;
  char ch2;
  for(i=0; i < this->alfabeto_size; i++){
    ch2 = this->alfabeto[i];
    if (ch2 == ch) return i;
  }
  return -1;
}

std::string Fcm::get_word_from_buffer(std::vector<char> words){
  
  std::string word;
  int i;
  for(i = 0; i < words.size(); i++){
    word += words[i];
  }
  return word;
}

int Fcm::open(std::string filename){

  this->ifs.open(filename,std::ios::in);
      
  if(!this->ifs) return -1;
  return 0;
}

int Fcm::close(){

  this->ifs.close();
  return 0;
}

int Fcm::save_text(){
  std::string txt; 
  char ch; 
  int i;
  while (this->ifs.get(ch)) {
    if (ch < 32) continue;
    this->text.push_back(ch);
    this->word_count += 1;
  }
  this->get_alphabet();
  this->close();
  return 0;
}

void Fcm::get_alphabet(){

  // generate alphabet
  std::map<char,int> alpha;
  std::string alphabet = "";
  int i;
  char ch;
  for(i=0;i<this->word_count;i++){
    ch = this->text[i];
    if (alpha.count(ch) == 0){
      alphabet += ch;
      alpha[ch] = 1;
    }
  }
  this->alfabeto = alphabet;
  this->alfabeto_size = alphabet.size();

  for(i=0; i < this->alfabeto_size; i++){
    this->internal_vector.push_back(0.0);
  }
  this->internal_vector.push_back(0.0);
  this->internal_vector.push_back(0.0);
  this->internal_vector.push_back(0.0);
}

int Fcm::count_depth(int k,double alpha){

  if (this->text.size() == 0){
    std::cout << "NO TEXT TO READ" << "\n";
    return -1;
  } 

  if (this->text.size() < k+1){
    std::cout << "Not ENOUGH WORD FOR DIMENSION K" << "\n"; 
    return -1;
  }
  std::vector<char> buffer;
  int i,j;

  /// buffer the word until the kth char
  for(i=0 ; i < k;i++){
    buffer.push_back(this->text[i]);
  }

  char ch;
  int index;
  
  for(i=k; i < this->text.size(); i++){
    
    /// retrive one char from the text
    ch = this->text[i];

    /// find ch index in the alphabet
    index = this->char_to_index(ch);
  
    if (index == -1){ 
      std::cout << "CHAR NOT FOUND ch: " << ch << "\n";
      return -1;
    }
    /// take the word in the buffer and verify is it exist in the matrix and if so update its values else add a internal vector
    std::string word = get_word_from_buffer(buffer);
    if (this->matrix.count(word.c_str()) == 0){
      std::vector<double> tmp;
      std::copy(this->internal_vector.begin(), this->internal_vector.end(), std::back_inserter(tmp));
      tmp[index] += 1.0;
      tmp[this->alfabeto_size] += 1.0;
      this->matrix[word.c_str()] = tmp;
    }
    else{
      this->matrix[word.c_str()][index] += 1.0; 
      this->matrix[word.c_str()][this->alfabeto_size] += 1.0;
    }

    /// update buffer  [a,b,c,d] -> [b,c,d,e]
    for(j = 0; j < k-1; j++)
      buffer[j] = buffer[j+1];
    buffer[k-1] = ch;

  }
  
  /// after read all the text its time to update prob of each transition and entropy
  std::map<std::string, std::vector<double>>::iterator it = this->matrix.begin();
  std::string word;
  int cnt;
  while (it != this->matrix.end()){
    cnt = 0;
    word = it->first;
    // (occurrences + alpha) / (total + (ALPHABET_LENGTH*alpha)))
    for(i = 0; i < this->alfabeto_size; i++){
      this->matrix[word][i] = (this->matrix[word][i] + alpha) / (this->matrix[word][this->alfabeto_size] + (this->alfabeto_size*alpha)); // prob
      this->matrix[word][this->alfabeto_size+1] -= this->matrix[word][i] * LOG2(this->matrix[word][i]); // entropy
    }
    this->matrix[word][this->alfabeto_size+2] += ((double)this->matrix[word][this->alfabeto_size] / (double)this->word_count) * this->matrix[word][alfabeto_size+1]; // model entropy
    it++;
  }

  return 0;
}


void Fcm::printMatrix(){
  std::map<std::string, std::vector<double>>::iterator it = this->matrix.begin();
  std::string word;
  int i;

  for(i = 0; i < this->alfabeto_size; i++){
    printf("%5c ",this->alfabeto[i]);
  }
  printf("\n");
  while (it != this->matrix.end())
  {
    word = it->first;
    std::cout << word << "\t\t";
    for(i = 0; i < this->alfabeto_size + 3; i++){
      printf("%2.2f\t",this->matrix[word][i]);
    }
    printf("\n");
    it++;
  }
}





