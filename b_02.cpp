#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>

int main(int argc, char *argv[]){
  
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

  while (std::getline(ifs, s)) {
    for (int i=0; i < s.size();i++){
      ofs << s[i];
    }
  }

  ifs.close();
  ofs.close();

  return 0;
}
