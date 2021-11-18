#include <iostream>
#include <iostream>
#include <sndfile.hh>
#include <vector>
#include <sndfile.hh>

constexpr size_t FRAMES_BUFFER_SIZE = 1; // Buffer for reading/writing frames

int main(int argc, char* argv[]){
/*
*   This program reads an audio file and stores its content in a new audio file
*/
  SndfileHandle sndFileIn ( argv[1] );
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

  std::cout << '\t' << sndFileIn.frames() << " frames" << std::endl;
  std::cout << '\t' << sndFileIn.samplerate() << " samples per second" << std::endl;
  std::cout << '\t' << sndFileIn.channels() << " channels" << std::endl;
  
  SndfileHandle sndFileOut ( argv[2], SFM_WRITE, sndFileIn.format(),
	  sndFileIn.channels(), sndFileIn.samplerate() );
	  
  if(sndFileOut.error()) {
    std::cerr << "Error: invalid output file" << std::endl;
		return 1;
  }

/*
*  Read a audio file sndFileIn and store it in sndFileOut
*/
  size_t nFrames;
  std::vector<short> samples(FRAMES_BUFFER_SIZE * sndFileIn.channels());
  while((nFrames = sndFileIn.readf(samples.data(), 1))){
    sndFileOut.writef(samples.data(), nFrames);
  } 

  return 0;
}
