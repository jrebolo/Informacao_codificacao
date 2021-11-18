#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>

int main(int argc, char *argv[]){
/*
*   This program reads a text file and copy it's content to a new file
*/
  if (argc < 3){
    std::cout << "WRONG ARGUMENTS" << std::endl;
    return 0;
  }
  
  std::ifstream ifs(argv[1]);
  if (ifs.fail()){
    std::cout << "CANT OPEN ORIGEN FILE" << std::endl;
    return 0;
  }

  std::ofstream ofs (argv[2]);
  if (ofs.fail()){
    std::cout << "CANT OPEN DESTINATION FILE" << std::endl;
    return 0;
  }
  
  std::string s;
/*
*   Read each line of the input text file and iterates over each string of the file lines storing in a new file caracter by caracter
*/
  while (std::getline(ifs, s)) {
    for (int i=0; i < s.size();i++){
      ofs << s[i];
    }
  }

  ifs.close();
  ofs.close();

  return 0;
}
