#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "golomb.h"
#include <sndfile.hh>
#include <string>
#include <sstream>
class AudioCodec{

  public:

    std::vector<int> res1;
    std::vector<int> res2;
    int format;
    int samples;
    int channels;
    int frames;
    std::string filename;
    SndfileHandle sndFileIn;
    short mid = 0;
    short side  = 0;
    short res_mid = 0;
    short res_side = 0;
    int m = 0;
    std::vector<short> buffer;
    AudioCodec(){}
    AudioCodec(int m){
      this->m = m;
    }

    int open(std::string filename);
    void read2Buffer();
    void encodePredictive(std::string filename);
    void getMidAndSide(short ch1, short ch2);
    int decodePredictive(std::string filename_in,std::string filename_out);
    int writeSnd(std::string filename);
    void histogram(std::string filename);
};  

int AudioCodec::open(std::string filename){
  this->filename = filename;
  SndfileHandle sndFileIn(filename);
  if(sndFileIn.error()) {
    std::cerr << "Error: invalid input file" << std::endl;
		return 1;
  }

  if((sndFileIn.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    std::cerr << "Error: file is not in WAV format" << std::endl;
		return 1;
	}

	if((sndFileIn.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    std::cerr << "Error: file is not in PCM_16 format" << std::endl;
		return 1;
	}
  
  // guardar alguns parâmetros
  this->sndFileIn = sndFileIn;
  this->format = sndFileIn.format();
  this->samples = sndFileIn.samplerate();
  this->channels = sndFileIn.channels();
  this->frames = sndFileIn.frames();
  return 0;
}

void AudioCodec::read2Buffer(){

  size_t nFrames;
  std::vector<short> samples(this->sndFileIn.channels());
  int i = 0;
  while((nFrames = this->sndFileIn.readf(samples.data(), 1))){
    this->buffer.push_back(samples[0]);
    this->buffer.push_back(samples[1]);
    i += 2;
  }
  printf("size: %d\n",i);
}

void AudioCodec::encodePredictive(std::string filename){
  Golomb gb(this->m);    
  int i = 0;
  int size = this->buffer.size();
  short mid = 0;
  short side = 0;
  short r1 = 0;
  short r2 = 0;

  short ch1 = 0;
  short ch2 = 0;

  for(i = 0; i < this->buffer.size(); i+=2){
    
  // get mid and side
    this->getMidAndSide(this->buffer[i],this->buffer[i+1]);
  // fazer metodo predictivo
    r1 = this->mid - mid;
    r2 = this->side - side;
    mid = this->mid;
    side = this->side;
    
    this->res1.push_back(r1);
    this->res2.push_back(r2);

  // encode mid and side with predictive method
    
    gb.encode(r1);
    gb.encode(r2);
  }
  gb.write(filename,'e');
}

void AudioCodec::histogram(std::string filename){
  int i;
  std::ofstream ofs(filename);
  for(i=0;i < this->res1.size();i++){
    ofs << this->res1[i] << " " << this->res2[i] << std::endl;
  }
  ofs.close();
}


void AudioCodec::getMidAndSide(short ch1, short ch2){ 
  this->mid = ch1 + ch2;
  this->side = ch1 - ch2;
}

int AudioCodec::decodePredictive(std::string filename_in,std::string filename_out){
  Golomb gb(this->m);
  
  int i = 0;
  short r1 = 0;
  short r1_def = 0;
  short r2 = 0;
  short r2_def = 0;
  short ch1 = 0;
  short ch2 = 0;

  std::vector<short> ch;
  
  gb.decode(filename_in);
  gb.write(filename_out,'d');
  
  std::ifstream ifs(filename_out);
  // decode mid and side to left and right
  while (ifs >> r1){

    this->mid = r1 + r1_def;
    r1_def = r1;

    ifs >> r2;
    this->side = r2 + r2_def;
    r2_def = r2;

    ch1 = (this->mid + this->side)/2;
    ch2 =  (this->mid - this->side)/2;

    ch.push_back(ch1);
    ch.push_back(ch2);
  }
  ifs.close();

  std::ofstream ofs("final_decoded");
  for(i=0;i<ch.size();i++){
    ofs << ch[i] << std::endl;
  }
  ofs.close();
  
  return 0;
}


int AudioCodec::writeSnd(std::string filename){
  SndfileHandle sndFileOut(filename, SFM_WRITE, this->format,
      this->channels, this->samples);
    if(sndFileOut.error()) {
      std::cerr << "Error: invalid output file" << std::endl;
      return 1;
  }

  std::vector<short> samples(2);
  int i;
  short val;
  std::ifstream ifs("final_decoded");
  while(ifs >> val){
    samples[0] = val;
    ifs >> val;
    samples[1] = val;
    sndFileOut.writef(samples.data(),1); 
  }

  ifs.close();
  return 0;
}
