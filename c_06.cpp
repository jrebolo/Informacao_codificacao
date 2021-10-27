#include <iostream>
#include "AudioFile/AudioFile.h"
#include <map>
#include <iterator>
#include <fstream>

int main(int argc, char* argv[]){

  AudioFile<double> audioFile;
  audioFile.load(argv[1]);
  int channels = audioFile.getNumChannels();
  int numSamples = audioFile.getNumSamplesPerChannel();
  
  std::map<double, int> m;
  double d;
  for (int c = 0; c < channels; c++){
    for (int i = 0; i < numSamples; i++){
      d = audioFile.samples[c][i];
      if (m.find(d) == m.end() )
        m[d] = 1;
      else
        m[d]++;
    }
  }
  std::ofstream ofs(argv[2]);
  for(std::map<double,int>::iterator it = m.begin(); it != m.end(); ++it) {
    ofs << it->first << " " << it->second << std::endl;
  }
  ofs.close();

  return 0;
}
