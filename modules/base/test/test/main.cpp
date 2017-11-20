#include<base/singleton.hpp>
#include<base/bool_ref.hpp>
#include<base/static_list.hpp>
#include<base/integer.hpp>
#include<base/array.hpp>
#include<base/literal_parser.hpp>
#include<base/pair.hpp>
#include<base/dummy.hpp>
#include<base/compil.hpp>
#include<base/type_traits.hpp>
#include<base/fixed_point.hpp>
#include<base/matrix.hpp>

#include <iostream>

using namespace Aversive::Base;

int main(int, char**) {
  static_assert(TypeEqual<int>::VALUE, "");
  static_assert(TypeEqual<int,int>::VALUE, "");
  static_assert(!TypeEqual<int,double>::VALUE, "");
  static_assert(TypeEqual<int,int,int>::VALUE, "");
  static_assert(!TypeEqual<int,int,double>::VALUE, "");
  static_assert(!TypeEqual<int,double,double>::VALUE, "");

  std::cout << "OK" << std::endl;
  return 0;
}
