#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

template <class T>
void f(T x)
{
  std::cout << sizeof(x) << "  " << x << std::endl;
}


int main(){
  f(1);
  f(1.1);
  f("E");
  f('E');
  f("EU");
  /*
  std::ifstream ifs("num.txt");
  std::ofstream ofs("num2.txt");
  std::string x;
  while (std::getline(ifs, x)) {
    std::cout << x << std::endl;
    ofs << x << std::endl;
  }

  ifs.close();
  ofs.close();
  */
  
  auto start = std::high_resolution_clock::now();
  
  std::vector<int> v1;
  v1.push_back(10);
  v1.push_back(20);
  v1.push_back(30);
  
  auto stop = std::high_resolution_clock::now();
  auto duration = std::duration_cast<microseconds>(stop - start);

  std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

  for (int i=0; i < v1.size(); i++){
    std::cout << "1: " << v1[i] << std::endl;
  }

  for (auto i : v1){
    std::cout << "2: " << i << std::endl;
  }
  
  
  std::vector<int>::iterator it = v1.begin();
  while(it != v1.end()){
    std::cout << "3: " << *it << std::endl;
    it++;
  }
/*
  std::map<char, int> m;
  m['a'] = 5;
  m['b'] = 10;
*/
  return 0;
}
