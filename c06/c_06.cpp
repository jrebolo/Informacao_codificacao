#include <iostream>
#include <sndfile.hh>
#include <map>
#include <iterator>
#include <fstream>
#include <cmath>
#include <vector>

constexpr size_t FRAMES_BUFFER_SIZE = 1; // Buffer for reading/writing frames

int main(int argc, char* argv[]){

  // open sound file  
  SndfileHandle sndFile ( argv[1] );
  if(sndFile.error()) {
    std::cerr << "Error: invalid input file" << std::endl;
		return 1;
  }

  if((sndFile.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
    std::cerr << "Error: file is not in WAV format" << std::endl;
		return 1;
	}

	if((sndFile.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
    std::cerr << "Error: file is not in PCM_16 format" << std::endl;
		return 1;
	}

  size_t nFrames;
  std::vector<short> samples(FRAMES_BUFFER_SIZE * sndFile.channels());
  int cnt=0;
  int mean=0;
  int i;
  int sample_mean[65536]; // mean samples value between right and left channel
  int sample0[65536]; // samples from channel 0
  int sample1[65536]; // samples from channel 1
  
  for (i=0; i < 65536;i++){
    sample_mean[i] = 0;
    sample0[i] = 0;
    sample1[i] = 0;
  }


  //-32,768 to 32,767
  //65536
  while((nFrames = sndFile.readf(samples.data(), 1))){  
    mean = (samples[0]+samples[1])/2;

    sample_mean[mean+32767]++;
    sample0[samples[0]+32767]++;
    sample1[samples[1]+32767]++;

    cnt++;
  } 
  std::cout << cnt << std::endl; 
  
  double prob_mean[65536]; // probability of mean samples value between right and left channel
  double prob0[65536]; // probability of samples from channel 0
  double prob1[65536]; // probability of samples from channel 1

  for (i=0; i < 65536;i++){
    if (sample_mean[i] != 0)
      prob_mean[i] = sample_mean[i]*1.0/cnt;
    else
      prob_mean[i] = 0;
    if (sample0[i] != 0)
      prob0[i] = sample0[i]*1.0/cnt;
    else
      prob0[i] = 0;
    if (sample1[i] != 0)
      prob1[i] = sample1[i]*1.0/cnt;
    else
      prob1[i] = 0;
  }

  double entropy0 = 0;
  double entropy1 = 0;
  double entropy_mean = 0;

  std::ofstream ofs(argv[2]);
  for (i=0;i<65536;i++){
    if (prob_mean[i] != 0)
      entropy_mean = entropy_mean + (prob_mean[i]*std::log(prob_mean[i]/std::log(2)));
    if (prob0[i] != 0)
      entropy0 = entropy0 + (prob0[i] * std::log(prob0[i])/std::log(2)); 
    if (prob1[i] != 0)
      entropy1 = entropy1 + (prob1[i] * std::log(prob1[i])/std::log(2););
    ofs << (i-32768) << " " << sample_mean[i] << " " << sample0[i] << " " << sample1[i] << std::endl;
  }
  
  entropy0 = -entropy0;
  entropy1 = -entropy1;
  entropy_mean = -entropy_mean;
  
  std::cout << entropy0 << " " << entropy1 << " " << entropy_mean << std::endl;

  ofs.close();

  return 0;
}
