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
    int mid;
    int side;
    
    std::vector<short> buffer;

    AudioCodec(){
    }
    int open(std::string filename);
    void read2Buffer();
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
  std::vector<short> samples(FRAMES_BUFFER_SIZE * sndFileIn.channels());
  while((nFrames = sndFileIn.readf(samples.data(), 1))){
    buffer.push_back(samples[0]);
    buffer.push_back(samples[1]);
  } 
}


