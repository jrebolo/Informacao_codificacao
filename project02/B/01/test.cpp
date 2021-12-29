#include "audioCodec.h"
#include <fstream>
int main(int argc, char* argv[]){
  

  AudioCodec ac(1000);
  
  if(ac.open(argv[1])){
    std::cout << "Error Opening audio file" << std::endl;
    return 1;
  }
  ac.read2Buffer();
  ac.encodePredictive("sample03_encoded.bin");

  
  ac.histogram("hist.data");
  
  AudioCodec ac2;
  ac2.format = ac.format;
  ac2.samples= ac.samples;
  ac2.channels = ac.channels;
  ac2.frames= ac.frames;

  ac2.m = ac.m;
  
  ac2.decodePredictive("sample03_encoded.bin","decoded_sample03");
  
  ac2.writeSnd("sample03_2.wav");

  
  return 0;
}
