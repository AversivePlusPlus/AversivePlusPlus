#ifndef CAS_DERIVATE_HPP
#define CAS_DERIVATE_HPP

#include <cas/function.hpp>
#include <cas/simplify.hpp>

namespace CAS {

namespace PrivateDerivate {

  template<typename Func>
  struct Derivate {
    static_assert(sizeof(Func)&&!sizeof(Func), "ERROR:Undefined Derivate for this function");
    using Value = void;
  };

  template<typename Ret, typename Param, s32 VAL>
  struct Derivate<IntegerConst<Ret, Param, VAL>> {
    using Value = IntegerConst<Ret, Param, 0>;
  };

  template<typename Ret, typename Param>
  struct Derivate<Identity<Ret, Param>> {
    using Value = IntegerConst<Ret, Param, 1>;
  };

  template<typename Ret, typename Param, array_t ROW, array_t COL>
  struct Derivate<Binder<Ret, Param, ROW, COL>> {
    using Value = IntegerConst<Ret, Param, 1>;
  };

  template<typename Ret, typename Param>
  struct Derivate<Cos<Ret, Param>> {
    using Value = Multiply<IntegerConst<Ret, Param, -1>, Sin<Ret, Param>>;
  };

  template<typename Ret, typename Param>
  struct Derivate<Sin<Ret, Param>> {
    using Value = Cos<Ret, Param>;
  };

  template<typename Func, typename Ret, typename Param, s32 VAL>
  struct Derivate<Multiply<IntegerConst<Ret, Param, VAL>, Func>> {
    using Value = Multiply<IntegerConst<Ret, Param, VAL>, typename Derivate<Func>::Value>;
  };

  template<typename Func1, typename Func2>
  struct Derivate<Multiply<Func1, Func2>> {
    using Value = Add<
        Multiply<typename Derivate<Func1>::Value, Func2>,
        Multiply<Func1, typename Derivate<Func2>::Value>
    >;
  };

  template<typename Func1, typename Func2>
  struct Derivate<Compose<Func1, Func2>> {
    using Value = Multiply<
        Compose<typename Derivate<Func1>::Value, Func2>,
        typename Derivate<Func2>::Value
    >;
  };

  template<typename Func1, typename Func2>
  struct Derivate<Add<Func1, Func2>> {
    using Value = Add<
        typename Derivate<Func1>::Value,
        typename Derivate<Func2>::Value
    >;
  };

  template<typename Ret, typename Param, array_t ROWS, array_t COLS, typename ...Funcs>
  struct Derivate<Matrix<Ret, Param, ROWS,COLS,Funcs...>> {
    using Value = Matrix<Ret, Param, ROWS,COLS,typename Derivate<Funcs>::Value...>;
  };


}

template<typename Func> using Derivate = typename PrivateDerivate::Derivate<Func>::Value;

}

#endif//CAS_DERIVATE_HPP
