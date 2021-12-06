#include <iostream>
#include <fstream>
#include <sndfile.hh>
#include <vector>
#include <math.h>
constexpr size_t FRAMES_BUFFER_SIZE = 1; 

void PRINT(std::vector<uint8_t> bytes){
  int i,ii;
  for (i=0;i < bytes.size();i++){
    for(ii=7;ii > 0;ii--){
      if ((bytes[i] >> ii ) & 1U)
        printf("1");
      else
        printf("0");
    }
    printf("\n");
  }
}

void encode(short v,int m,int *i_,int *index_,std::vector<uint8_t> *bytes){
  int q = v/m;
  int r = v%m;
  int signal = 0;
  int i = *i_;
  int index = *index_;
  int cnt;
  int ii;
  q = q < 0 ? q*(-1) : q;
  if (r < 0){
    signal = 1;
    r = -1*r;
  }else{
    signal = 0;
  }
  // defenir q com um codigo unario
  cnt = 0;
  for (;cnt < q ;i--){
    if (i < 0){ 
      (*bytes).push_back(0);
      index += 1;
      i = 7;
    }
    // set the amount of 1's in bytes equal to the number of q
    // q = 0 set 0 bits; q = 1 set 1 bit; ... q = n set n bits to 1
    (*bytes)[index] |= (1UL << i);
    cnt += 1;
  }
  i -= 1; // increment so ther is 1 bit to zero to end the unary code
  if (signal){
    if (i < 0){
      (*bytes).push_back(0);
      index += 1;
      i = 7;
    }
    (*bytes)[index] |= (1 << i);
    i -= 1;
  }
  cnt = 0;
  // defenir um codigo binario
  for (ii=7;ii > 0;i--,ii--){
    if (i < 0){
      (*bytes).push_back(0);
      index += 1;
      i = 7;
    }
    if (r & (1 << ii))
      (*bytes)[index] |= (1UL << i);
  }
  *i_ = i;
  *index_ = index;

}

int main(int argc, char* argv[]){
  
  if (argv[1][0] == 'e'){
    SndfileHandle sndFileIn (argv[2]);
    std::ofstream ofs(argv[3],std::ios::out | std::ios::binary);
    size_t nFrames;
    std::vector<short> samples(FRAMES_BUFFER_SIZE * sndFileIn.channels());
    int m = 255;
    int q;
    int r;
    int i;
    int cnt;
    int index0 = 0;
    int i0 = 7;
    int index1 = 0;
    int i1 = 7;
    std::vector<uint8_t> bytes0;
    std::vector<uint8_t> bytes1;
    bytes0.push_back(0);
    bytes1.push_back(0);
    bool signal = 0;
    while((nFrames = sndFileIn.readf(samples.data(), 1))){
      encode(samples[0],255,&i0,&index0,&bytes0);
      encode(samples[1],255,&i1,&index1,&bytes1);
      /*
      // short 16 bits 2 bytes pos e neg [−32,767, +32,767]
      // calculate q and r
      q = samples[0]/m;
      r = samples[0]%m;
      // set q value to be absolute
      q = q < 0 ? q*(-1) : q;
      if (r < 0){
        signal = 1;
        r = -1*r;
      }else{
        signal = 0;
      }
      //if (r>255)
        //printf("V: %d Q: %d R: %d\n",samples[0],q,r);
      
      // defenir q com um codigo unario
      cnt = 0;
      for (;cnt < q ;i--){
        if (i < 0){ 
          bytes.push_back(0);
          index += 1;
          i = 7;
        }
        // set the amount of 1's in bytes equal to the number of q
        // q = 0 set 0 bits; q = 1 set 1 bit; ... q = n set n bits to 1
        bytes[index] |= (1UL << i);
        cnt += 1;
      }
      i -= 1; // increment so ther is 1 bit to zero to end the unary code
      if (signal){
        if (i < 0){
          bytes.push_back(0);
          index += 1;
          i = 7;
        }
        bytes[index] |= (1 << i);
        i -= 1;
      }
      cnt = 0;
      // defenir um codigo binario
      for (ii=7;ii > 0;i--,ii--){
        if (i < 0){
          bytes.push_back(0);
          index += 1;
          i = 7;
        }
        if (r & (1 << ii))
          bytes[index] |= (1UL << i);
      }
      //printf("v: %d byte: %d q: %d r: %d\n",samples[0],byte,q,r);
      */
    } 
    for (i=0;i < bytes0.size();i++){
      ofs << bytes0[i];
      //ofs.write((char *)bytes[i],sizeof(uint8_t));  
    }
    for (i=0;i < bytes1.size();i++){
      ofs << bytes1[i];
      //ofs.write((char *)bytes[i],sizeof(uint8_t));  
    }
   // PRINT(bytes);
  }
  
  }else if(argv[1][0] == 'd'){
   
    char c;
    int cnt;
    int cnt2 = 0;
    int i=7;
    int unary=1;
    int signal=1;
    int r;
    int q;
    unsigned int ii; 
    std::ifstream ifs(argv[2],std::ios::in | std::ios::binary);
    while(ifs.read(&c, sizeof(c))){ 
      for (;i > 0;i--){
        //get unary value
        if (unary){
          if !(c & (1 << ii)){
            unary=0;
            q = cnt;
          }
          else{ cnt += 1;}
        }
        else{
          if (signal==1){
            signal=-1;
            i -= 1;
          }
          if (i < 0) break;
          
          
        }
      }
      
    }
  }
  
  return 0;
}
