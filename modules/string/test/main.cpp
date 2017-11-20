#include <string/compil.hpp>
#include <string/simple.hpp>
#include <string/sized.hpp>
#include <string/concat.hpp>

#include <iostream>

using namespace std;
using namespace Aversive::String;

CompilString<'h', 'e', 'l', 'l', 'o'> mystring;
SimpleString mystring2("world");
SizedString mystring3("/test/miew/lol"+5, 5);

template<class Derived>
ostream& operator<<(ostream& stream, const Interface<String, Derived>& str) {
  for(unsigned int i = 0 ; i < str.len() ; i++) {
    stream << str[i];
  }
  return stream;
}

int main(int, char**) {
  cout << mystring << " " << mystring2 << endl;
  cout << mystring3 << endl;
  cout << concat(mystring, mystring3) << endl;
  return 0;
}
