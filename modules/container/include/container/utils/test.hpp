#ifndef AVERSIVE_CONTAINER_TEST_HPP
#define AVERSIVE_CONTAINER_TEST_HPP

#include "../array.hpp"
#include "../container.hpp"
#include "../flushable.hpp"
#include "../headed.hpp"
#include "../iterable.hpp"
#include "../iterator.hpp"
#include "../limited.hpp"
#include "../list.hpp"
#include "../queue.hpp"
#include "../set.hpp"
#include "../stack.hpp"

namespace Aversive {
namespace Container {
namespace Test {

template<typename T, typename Func>
struct Func2Member {};

template<typename T, typename Ret, typename... Args>
struct Func2Member<T, Ret(Args...)> {
  typedef Ret (T::*Member)(Args...);
};

template<typename T, typename Ret, typename... Args>
struct Func2Member<T, Ret(Args...) const> {
  typedef Ret (T::*Member)(Args...) const;
};

template<template<typename...> class Base, class Derived>
class test_interface;

#define AVERSIVE_DEFINE_MEMBER_CHECKER(name, member, signature) \
  template<class T> \
  class name { \
  template<typename U, typename Func2Member<U, signature>::Member> struct SFINAE {}; \
  template<typename U> static constexpr inline bool _test(SFINAE<U, &U::member>*) { return true; } \
  template<typename U> static constexpr inline bool _test(...) { return false; } \
  public: \
  constexpr inline operator bool(void) const { return _test<Derived>(0); } \
};

template<class Derived>
class test_interface<Array, Derived> {
  using Base = typename Derived::BaseArray;

  using ElementRef = typename Base::ElementRef;
  using ConstElementRef = typename Base::ConstElementRef;
  using Index = typename Base::Index;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_get_operator, operator[], ElementRef(Index));
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_get_operator_const, operator[], ConstElementRef(Index) const);
public:
  constexpr operator bool (void) const {
    return test_get_operator<Derived>() && test_get_operator_const<Derived>();
  }
};

template<class Derived>
class test_interface<Container, Derived> {
  using Base = typename Derived::BaseContainer;
  using Index = typename Base::Index;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_empty, empty, bool(void) const);
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_size, size, Index(void) const);
public:
  constexpr operator bool (void) const {
    return test_empty<Derived>() && test_size<Derived>();
  }
};

template<class Derived>
class test_interface<Limited, Derived> {
  using Base = typename Derived::BaseLimited;
  using Index = typename Base::Index;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_full, full, bool(void) const);
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_limit, limit, Index(void) const);
public:
  constexpr operator bool (void) const {
    return test_full<Derived>() && test_limit<Derived>();
  }
};

template<class Derived>
class test_interface<Iterable, Derived> {
  using Base = typename Derived::BaseIterable;
  using Iterator = typename Base::Iterator;
  using ConstIterator = typename Base::ConstIterator;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_begin, begin, Iterator(void));
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_begin_const, begin, ConstIterator(void) const);
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_end, end, Iterator(void));
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_end_const, end, ConstIterator(void) const);
public:
  constexpr operator bool (void) const {
    return
        test_begin<Derived>() && test_begin_const<Derived>() &&
        test_end<Derived>() && test_end_const<Derived>();
  }
};

template<class Derived>
class test_interface<Flushable, Derived> {
  using Base = typename Derived::BaseFlushable;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_flush, flush, void(void));
public:
  constexpr operator bool (void) const {
    return test_flush<Derived>();
  }
};

template<class Derived>
class test_interface<Queue, Derived> {
  using Base = typename Derived::BaseQueue;
  using ConstElementRef = typename Base::ConstElementRef;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_enqueue, enqueue, void(ConstElementRef));
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_dequeue, dequeue, void(void));
public:
  constexpr operator bool (void) const {
    return test_enqueue<Derived>() && test_dequeue<Derived>();
  }
};

template<class Derived>
class test_interface<Stack, Derived> {
  using Base = typename Derived::BaseStack;
  using ConstElementRef = typename Base::ConstElementRef;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_push, push, void(ConstElementRef));
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_pop, pop, void(void));
public:
  constexpr operator bool (void) const {
    return test_push<Derived>() && test_pop<Derived>();
  }
};

template<class Derived>
class test_interface<Headed, Derived> {
  using Base = typename Derived::BaseHeaded;

  using ElementRef = typename Base::ElementRef;
  using ConstElementRef = typename Base::ConstElementRef;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_head, head, ElementRef(void));
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_head_const, head, ConstElementRef(void) const);
public:
  constexpr operator bool (void) const {
    return test_head<Derived>() && test_head_const<Derived>();
  }
};

template<class Derived>
class test_interface<List, Derived> {
  using Base = typename Derived::BaseList;
  using ConstElementRef = typename Base::ConstElementRef;
  using Index = typename Base::Index;

  AVERSIVE_DEFINE_MEMBER_CHECKER(test_insert, insert, void(Index, ConstElementRef));
  AVERSIVE_DEFINE_MEMBER_CHECKER(test_remove, remove, void(Index));
public:
  constexpr operator bool (void) const {
    return test_insert<Derived>() && test_remove<Derived>();
  }
};

#undef AVERSIVE_DEFINE_MEMBER_CHECKER

}
}
}

#endif//AVERSIVE_CONTAINER_TEST_HPP
