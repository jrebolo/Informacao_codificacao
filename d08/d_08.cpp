#include <iostream>
#include "AudioFile.h"
#include <map>
#include <iterator>
#include <fstream>
#include <cmath>
int main(int argc, char* argv[]){

  AudioFile<double> audioFile;
  audioFile.load(argv[1]);
  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();
  
  std::map<double, int> m1;
  std::map<double, int> m2;

  double d1;
  double d2;

  for (int i = 0; i < numSamples; i++){
    d1 = audioFile.samples[0][i];
    d2 = audioFile.samples[1][i];
  }
  
  std::cout << d1 << " " << d2 <<  std::endl;

  return 0;
}
