#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <cmath>
int main(int argc, char* argv[]){
/*
*   This program counts the number of ocurrences of each character in a text file.
*/
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
  std::map<char, int> m;  /**< map of the ocurrence of each caracter> */

/*
*   loop through each line of the input text file and iterate over each character aving in a map 
*/
  int cnt=0;
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
      cnt++;
    }
  }
  // save to file
  double entropy = 0.0;
  double prob = 0.0;
  for(std::map<char,int>::iterator it = m.begin(); it != m.end(); ++it) {
    ofs << it->first << " " << it->second << std::endl;
    prob = ((it->second)*1.0)/cnt;
    entropy = entropy + prob*std::log(prob)/std::log(2);
  }
  
  // calculate entropy
  entropy = -entropy;
  
  std::cout << entropy << std::endl;

  ifs.close();
  ofs.close();
  return 0;
}
