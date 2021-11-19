#include <iostream>
#include <sndfile.hh>
#include <vector>
#include <sndfile.hh>
#include <cmath>
#include <map>

#define MAXVAL 65535

constexpr size_t FRAMES_BUFFER_SIZE = 1; // Buffer for reading/writing frames

int main(int argc, char* argv[]){
/*
*     This program calculates the psnr of an audio file
*/
  // open first image
  SndfileHandle sndFile1 ( argv[1] );
  if(sndFile1.error()) {
    std::cerr << "Error: invalid input file" << std::endl;
		return 1;
  }

  if((sndFile1.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    std::cerr << "Error: file is not in WAV format" << std::endl;
		return 1;
	}

	if((sndFile1.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    std::cerr << "Error: file is not in PCM_16 format" << std::endl;
		return 1;
	}
  // Open second image
  SndfileHandle sndFile2 ( argv[2] );
  if(sndFile2.error()) {
    std::cerr << "Error: invalid input file" << std::endl;
		return 1;
  }

  if((sndFile2.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    std::cerr << "Error: file is not in WAV format" << std::endl;
		return 1;
	}

	if((sndFile2.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    std::cerr << "Error: file is not in PCM_16 format" << std::endl;
		return 1;
	}

  size_t nFrames;
  std::vector<short> samples1(FRAMES_BUFFER_SIZE * sndFile1.channels());
  std::vector<short> samples2(FRAMES_BUFFER_SIZE * sndFile2.channels());
  
  double e = 0;
  int cnt = 0;

  while((nFrames = sndFile1.readf(samples1.data(), 1))){
    sndFile2.readf(samples2.data(), 1);
    e = e + pow(((samples1[0]+samples1[1])/2) - ((samples2[0]+samples2[1])/2),2);
    cnt++;
  } 
  double psnr = 10*std::log((pow(MAXVAL,2)/e))/std::log(10); 
  std::cout << "psnr1: " << psnr << std::endl;
  return 0;
}
