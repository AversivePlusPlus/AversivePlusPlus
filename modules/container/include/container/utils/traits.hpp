#ifndef AVERSIVE_CONTAINER_TRAITS_HPP
#define AVERSIVE_CONTAINER_TRAITS_HPP

namespace Aversive {
namespace Container {
namespace Traits {

template<
    typename _Element,
    typename _ElementRef = _Element&, typename _ConstElementRef = const _Element&,
    typename _Iterator = _Element*, typename _ConstIterator = const _Element*
    >
struct Custom {
  using Element = _Element;
  using ElementRef = _ElementRef;
  using ConstElementRef = _ConstElementRef;
  using Iterator = _Iterator;
  using ConstIterator = _ConstIterator;
};

template<typename T>
using Default = Custom<T>;

}
}
}

#endif//AVERSIVE_CONTAINER_TRAITS_HPP
