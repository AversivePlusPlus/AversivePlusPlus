#ifndef CAS_FUNCTION_HPP
#define CAS_FUNCTION_HPP

#include <base/integer.hpp>
#include <base/type_traits.hpp>
#include <base/dummy.hpp>
#include <base/matrix.hpp>

#include <cas/return_rule.hpp>

namespace CAS {

  template<typename _ReturnType, typename _ParamType, typename _Derived>
  struct Function {
    using ReturnType = _ReturnType;
    using ParamType = _ParamType;
    using Value = _Derived;

    static constexpr inline ReturnType apply(ParamType val) {
      return _Derived::apply(val);
    }
  };

  template<typename Ret, typename Param>
  struct Cos : public Function<Ret, Param, Cos<Ret, Param>> {
    static constexpr inline Ret apply(Param val) {
      return (Ret)cos((double)val);
    }
  };

  template<typename Ret, typename Param>
  struct Sin : public Function<Ret, Param, Sin<Ret, Param>> {
    static constexpr inline Ret apply(Param val) {
      return (Ret)sin((double)val);
    }
  };

  template<typename Ret, typename Param>
  struct Identity : public Function<Ret, Param, Identity<Ret, Param>> {
    static constexpr inline Ret apply(Param val) {
      return (Ret)val;
    }
  };

  template<typename Ret, typename Param, s32 VALUE>
  struct IntegerConst : public Function<Ret, Param, IntegerConst<Ret, Param, VALUE>> {
    static constexpr inline Ret apply(Param) {
      return (Ret)VALUE;
    }
  };

  template<typename Ret, typename Param, s32 NUMERATOR, u32 DENOMINATOR>
  struct RationalConst : public Function<Ret, Param, RationalConst<Ret, Param, NUMERATOR, DENOMINATOR>> {
    static constexpr inline Ret apply(Param) {
      return ((Ret)NUMERATOR)/((Ret)DENOMINATOR);
    }
  };

  template<typename Ret, typename Param, array_t ROW, array_t COL>
  struct Binder : public Function<Ret, Param, Binder<Ret, Param, ROW, COL>> {
    static_assert(sizeof(Param) && !sizeof(Param), "ERROR : Cannot bind non-matrix type");
  };

  template<typename Ret, typename T, array_t ROWS, array_t COLS, array_t ROW, array_t COL>
  struct Binder<Ret, ::Matrix<T, ROWS, COLS>, ROW, COL> : public Function<Ret, ::Matrix<T, ROWS, COLS>, Binder<Ret, ::Matrix<T, ROWS, COLS>, ROW, COL>> {
    static constexpr inline Ret apply(::Matrix<T, ROWS, COLS> val) {
      return (Ret)val(ROW, COL);
    }
  };

  template<typename Ret, typename Param, array_t ROWS, array_t COLS, typename ...Funcs>
  struct Matrix : public Function< ::Matrix<Ret, ROWS, COLS>, Param, Matrix<Ret, Param, ROWS, COLS, Funcs...>> {
    static_assert(TypeEqual<typename Funcs::ReturnType...>::VALUE, "ERROR : Matrix ReturnType not uniform");
    static_assert(TypeEqual<typename Funcs::ParamType...>::VALUE, "ERROR : Matrix ParamType not uniform");

    static constexpr inline ::Matrix<Ret, ROWS, COLS> apply(Param val) {
      return ::Matrix<Ret, ROWS, COLS>(Funcs::apply(val)...);
    }
  };

  template<typename Ret, typename Param, s32 VAL>
  class Pow : public Function<typename ReturnRule::OperationReturnRule< ReturnRule::Operation::MULTIPLY, Ret, Ret>::Type, Param, Pow<Ret, Param, VAL>> {
    using MyRet = typename ReturnRule::OperationReturnRule< ReturnRule::Operation::MULTIPLY, Ret, Ret>::Type;
    using MyParam = Param;

    template<bool COND, DummyType DUMMY = DUMMY_VALUE>
    struct Helper {
      static constexpr inline MyRet apply(MyParam val) {
        return val * Pow<MyRet, MyParam, VAL-1>::apply(val);
      }
    };

    template<DummyType DUMMY>
    struct Helper<false, DUMMY> {
      static constexpr inline MyRet apply(MyParam val) {
        return Pow<MyRet, MyParam, VAL/2>::apply(val) * Pow<MyRet, MyParam, VAL/2>::apply(val);
      }
    };

  public:
    static constexpr inline MyRet apply(MyParam val) {
      return Helper<VAL%2>::apply(val);
    }
  };

  template<typename Ret, typename Param>
  struct Pow<Ret, Param, 1> : public Function<Ret, Param, Identity<Ret, Param>> {};

  template<typename Ret, typename Param>
  struct Pow<Ret, Param, 0> : public Function<Ret, Param, IntegerConst<Ret, Param, 1>> {};

  template<typename First, typename Second>
  struct Compose : public Function<typename First::ReturnType, typename Second::ParamType, Compose<First, Second>> {
    static_assert(TypeEqual<typename First::ParamType, typename Second::ReturnType>::VALUE, "ERROR : Second::ReturnType different First::ParamType");
    static constexpr inline typename First::ReturnType apply(typename Second::ParamType val) {
      return First::apply(Second::apply(val));
    }
  };

  template<typename First, typename Second>
  struct Multiply : public Function<typename ReturnRule::OperationReturnRule< ReturnRule::Operation::MULTIPLY, typename First::ReturnType, typename Second::ReturnType>::Type, typename First::ParamType, Multiply<First, Second>> {
    static_assert(TypeEqual<typename First::ParamType, typename Second::ParamType>::VALUE, "ERROR : Different parameter types");
    static constexpr inline typename ReturnRule::OperationReturnRule< ReturnRule::Operation::MULTIPLY, typename First::ReturnType, typename Second::ReturnType>::Type apply(typename First::ParamType val) {
      return First::apply(val)*Second::apply(val);
    }
  };

  template<typename First, typename Second>
  struct Divide : public Function<typename ReturnRule::OperationReturnRule< ReturnRule::Operation::DIVIDE, typename First::ReturnType, typename Second::ReturnType>::Type, typename First::ParamType, Divide<First, Second>> {
    static_assert(TypeEqual<typename First::ParamType, typename Second::ParamType>::VALUE, "ERROR : Different parameter types");
    static constexpr inline typename ReturnRule::OperationReturnRule< ReturnRule::Operation::DIVIDE, typename First::ReturnType, typename Second::ReturnType>::Type apply(typename First::ParamType val) {
      return First::apply(val)/Second::apply(val);
    }
  };

  template<typename First, typename Second>
  struct Add : public Function<typename ReturnRule::OperationReturnRule< ReturnRule::Operation::ADD, typename First::ReturnType, typename Second::ReturnType>::Type, typename First::ParamType, Add<First, Second>> {
    static_assert(TypeEqual<typename First::ParamType, typename Second::ParamType>::VALUE, "ERROR : Different parameter types");
    static constexpr inline typename ReturnRule::OperationReturnRule< ReturnRule::Operation::ADD, typename First::ReturnType, typename Second::ReturnType>::Type apply(typename First::ParamType val) {
      return First::apply(val)+Second::apply(val);
    }
  };

  template<typename First, typename Second>
  struct Substract : public Function<typename ReturnRule::OperationReturnRule< ReturnRule::Operation::SUBSTRACT, typename First::ReturnType, typename Second::ReturnType>::Type, typename First::ParamType, Substract<First, Second>> {
    static_assert(TypeEqual<typename First::ParamType, typename Second::ParamType>::VALUE, "ERROR : Different parameter types");
    static constexpr inline typename ReturnRule::OperationReturnRule< ReturnRule::Operation::SUBSTRACT, typename First::ReturnType, typename Second::ReturnType>::Type apply(typename First::ParamType val) {
      return First::apply(val)-Second::apply(val);
    }
  };

  // Grouping
  template<typename First, typename Second>
  struct Operation {
    using Compose = CAS::Compose<First, Second>;
    struct Arithmetic {
      using Multiply = CAS::Multiply<First, Second>;
      using Divide = CAS::Divide<First, Second>;
      using Add = CAS::Add<First, Second>;
      using Substract = CAS::Substract<First, Second>;
    };
  };

  template<typename Ret, typename Param>
  struct General {
    using Identity = CAS::Identity<Ret, Param>;
    struct Const {
      template<s32 VAL> using Integer = IntegerConst<Ret, Param, VAL>;
      template<s32 NUMERATOR, u32 DENOMINATOR> using Rational = RationalConst<Ret, Param, NUMERATOR, DENOMINATOR>;
    };
    template<array_t ROWS, array_t COLS>
    struct Matrix {
      template<typename ...Funcs> using Any = CAS::Matrix<Ret, Param, ROWS, COLS, Funcs...>;
    };
    struct Trigo {
      using Cos = CAS::Cos<Ret, Param>;
      using Sin = CAS::Sin<Ret, Param>;
    };

    using Cos  = typename Trigo::Cos;
    using Sin  = typename Trigo::Sin;
    using C0   = typename Const::template Integer<0>;
    using C1   = typename Const::template Integer<1>;
    using mC1  = typename Const::template Integer<-1>;
    using mSin = typename Operation<mC1, Sin>::Arithmetic::Multiply;

    struct Space2D {
      using Rotation = typename Matrix<3,3>::template Any<
      Cos, mSin, C0,
      Sin, Cos , C0,
      C0 , C0  , C1
      >;

      template<typename FuncX = C0, typename FuncY = C0>
      using Translation = typename Matrix<3,3>::template Any<
      C1 , C0  , FuncX,
      C0 , C1  , FuncY,
      C0 , C0  , C1
      >;

      using Identity = typename Matrix<3,3>::template Any<
      C1 , C0  , C0,
      C0 , C1  , C0,
      C0 , C0  , C1
      >;
    };

    struct Space3D {
      using RotationX = typename Matrix<4,4>::template Any<
      C1, C0 , C0  , C0,
      C0, Cos, mSin, C0,
      C0, Sin, Cos , C0,
      C0, C0 , C0  , C1
      >;

      using RotationY = typename Matrix<4,4>::template Any<
      Cos, C0, mSin, C0,
      C0 , C1, C0  , C0,
      Sin, C0, Cos , C0,
      C0, C0 , C0  , C1
      >;

      using RotationZ = typename Matrix<4,4>::template Any<
      Cos, mSin, C0, C0,
      Sin, Cos , C0, C0,
      C0 , C0  , C1, C0,
      C0 , C0  , C0, C1
      >;

      template<typename FuncX = C0, typename FuncY = C0, typename FuncZ = C0>
      using Translation = typename Matrix<4,4>::template Any<
      C1, C0, C0, FuncX,
      C0, C1, C0, FuncY,
      C0, C0, C1, FuncZ,
      C0, C0, C0, C1
      >;

      using Identity = typename Matrix<4,4>::template Any<
      C1, C0, C0, C0,
      C0, C1, C0, C0,
      C0, C0, C1, C0,
      C0, C0, C0, C1
      >;
    };

  };

}

#endif//CAS_FUNCTION_HPP
