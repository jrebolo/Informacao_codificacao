#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <vector>
int main(int argc, char* argv[]){
  
  if (argc < 3){
    std::cout << "WRONG INPUT ARGUMENTS" << std::endl;
  }
  std::ifstream ifs(argv[1]);  
  if (ifs.fail()){
    std::cout << "Faild to Open Origin File" << std::endl;
  }

  std::ofstream ofs(argv[2]);  
  if (ofs.fail()){
    std::cout << "failed to Open Destination File" << std::endl;
  }
  
  std::string s;
  std::map<char, int> m;  
  // count letters occurrence
  while (std::getline(ifs,s)){
    for (int i = 0; i < s.size(); i++){
      if (!std::isalpha(s[i])){
        continue;
      }
      if ( m.find(s[i]) == m.end() ){
        m[s[i]] = 1; 
      }else{
        m[s[i]]++; 
      }
    }
  }
  // save to file
  for(std::map<char,int>::iterator it = m.begin(); it != m.end(); ++it) {
    ofs << it->first << " " << it->second << std::endl;
  }

  ifs.close();
  ofs.close();
  return 0;
}
