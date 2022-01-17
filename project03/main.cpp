#include "fcm.h"

int main(int argc,char* argv[]){
  
  double entropy;

  Fcm fcm;
  if(fcm.open(argv[1])){
    printf("Could not open file\n");
    return -1;
  }
  
  fcm.save_text();
  fcm.count_depth(3,0.1);
  //fcm.count_depth(2);
  fcm.printMatrix();

  fcm.close(); 
  return 0;
}
