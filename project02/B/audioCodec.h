#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "golomb.h"
#include <sndfile.hh>
#include <string>

class AudioCodec{

  public:
    int frames;
    int samples;
    int channels;
    std::string filename;
    SndfileHandle sndFileIn;
    int mid = 0;
    int side  = 0;
    int res_mid = 0;
    int res_side = 0;
    std::vector<short> buffer;
    AudioCodec(){
    }
    int open(std::string filename);
    void read2Buffer();
    void encodePredictive(std::string filename);
    void getMidAndSide(short ch1, short ch2)
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
  this->sndFileIn = sndFileIn;
}

void AudioCodec::read2Buffer(){

  size_t nFrames;
  std::vector<short> samples(this->sndFileIn.channels());
  while((nFrames = this->sndFileIn.readf(samples.data(), 1))){
    buffer.push_back(samples[0]);
    buffer.push_back(samples[1]);
  }
  
}

void AudioCodec::encodePredictive(std::string filename){
  Golomb gb(2);    
  int i = 0;
  int size = this->buffer.size()/2;
  int mid = 0;
  int size = 0;
  int r1 = 0;
  int r2 = 0;
  // enquanto houver valores no buffer to encode

    while(i < size){
    // get mid and side
      this->getMidAndSide(this->buffer[i],this->buffer[i+1]);
      i += 2;
    // fazer metodo predictivo
      r1 = this->mid - mid;
      r2 = this->side - side;

      mid = this->mid;
      side = this->side;

    // encode mid and side with predictive method
      gb.encode(r1);
      gb.encode(r2);
    }
    gb.write(filename);
}

void AudioCode::GetMidAndSide(short ch1, short ch2){ 
  this->mid = ch1 + ch2;
  this->side = ch1 - ch2;
}

void AudioCodec::decodePredictive(std::string filename_in, std::string filename_out,std::string filename_out_2){

  Golomb gb(2);
  int i = 0;
  int size = this->buffer.size()/2;
  int r1_1 = 0;
  int r1_2= 0;
  int r2_1 = 0;
  int r2_2 = 0;
  int right = 0;
  int left = 0;
  
  std::vector<short> channels(this->buffer.size());
  
  gb.decode(filename_in, filename_out);
  
  std::ifstream ifs(filename_out);
  std::ifstream ofs(filename_out_2);
  

  while (!ifs.eof()){
    ifs >> r1_2;
    ifs >> r2_2;
    this->mid = r1_1 + r1_2;
    this->side = r2_1 + r2_2;
    r1_1 = r1_2;
    r2_1 = r2_2;

    left = this->mid + this->side;
    right =  this->mid - this->side;
    
    channels[i] = left;
    channels[i+1] = right;
    i += 2;
  }

}


void AudioCodec::writeSnd(std::vector<short> channels, std::string filename){
  
  SndfileHandle sndFileOut(filename, SFM_WRITE, this->sndFileIn.format(),
	  this->sndFileIn.channels(), this->sndFileIn.samplerate());
  size_t nFrames;
  std::vector<short> samples(this->sndFileIn.channels());
  for(i = 0; i < channels.size(); i += 2){
    samples[0] = channels[i];
    samples[1] = channels[i+1];
    sndFileOut.writef(samples.data(), nFrames);
  } 

}
