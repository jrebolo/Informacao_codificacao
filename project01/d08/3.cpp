/**
 * \file 3.cpp
 *
 * \brief This program reads an audio file sample by sample and writes it to a new audio file.
 *        To use the program, the user must pass two arguments: the input file path and the output file path
 *
 *        Usage: 3 <input file> <output file>
 *
 *
 * \author Daniel Canedo
 */


#include <iostream>
#include <vector>
#include <sndfile.hh>

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 1; // Buffer for reading/writing frames

int main(int argc, char *argv[]) {

	if(argc != 2) {
		cerr << "Usage: wavcp <input file> <output file>" << endl;
		return 1;
	}

	SndfileHandle sndFileIn ( argv[1] );
	if(sndFileIn.error()) {
		cerr << "Error: invalid input file" << endl;
		return 1;
    }

	if((sndFileIn.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
		cerr << "Error: file is not in WAV format" << endl;
		return 1;
	}

	if((sndFileIn.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
		cerr << "Error: file is not in PCM_16 format" << endl;
		return 1;
	}

	cout << "Input file has:" << endl;
	cout << '\t' << sndFileIn.frames() << " frames" << endl;
	cout << '\t' << sndFileIn.samplerate() << " samples per second" << endl;
	cout << '\t' << sndFileIn.channels() << " channels" << endl;
  /*
	SndfileHandle sndFileOut ( argv[2], SFM_WRITE, sndFileIn.format(),
	  sndFileIn.channels(), sndFileIn.samplerate() );
	if(sndFileOut.error()) {
		cerr << "Error: invalid output file" << endl;
		return 1;
    }

	size_t nFrames;
	vector<short> samples(FRAMES_BUFFER_SIZE * sndFileIn.channels());
	// reads nFrames from source audio file to destination file
	while((nFrames = sndFileIn.readf(samples.data(), 1))){
		cout << "Channel 1: " << samples[0] << "    " << "Channel 2: " << samples[1] << endl;
		sndFileOut.writef(samples.data(), nFrames);
	}
  */
	return 0;
}
