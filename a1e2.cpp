#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>


int main(){
  

  std::ifstream ifs("num.txt");
  std::string x;
  
  std::map <std::string, int> m;
  while (std::getline(ifs, x)) {
    if ( m.find(x) == m.end() ) {
      m[x] = 1;
    } else {
      m[x]++;
    }
  }
  for(std::map<std::string ,int>::iterator it = m.begin(); it != m.end(); ++it) {
    std::cout << "key: " << it->first << std::endl;
    std::cout << "Value: " << it->second << std::endl;
  }
  
  return 0;
}
