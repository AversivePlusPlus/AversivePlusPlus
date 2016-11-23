#ifndef CAS_SIMPLIFY_HPP
#define CAS_SIMPLIFY_HPP

#include <cas/function.hpp>
#include <cas/matrix_simplify.hpp>

#include <base/dummy.hpp>

namespace CAS {

  namespace PrivateSimplify {

    template<typename Func>
    struct IdSimplify {
      using Value = Func;
    };

    template<typename Func, template<typename, typename> class R1, template<typename, typename> class ...Rules>
    struct SimplifyRuleList {
      using Value = typename R1<Func, SimplifyRuleList<Func, Rules...>>::Value;
    };

    template<typename Func, template<typename, typename> class R1>
    struct SimplifyRuleList<Func, R1> {
      using Value = typename R1<Func, IdSimplify<Func>>::Value;
    };

    template<typename Func, typename Next>
    struct BaseSimplifyRule {
      using Value = typename Next::Value;
    };

    ////////////////
    //Rules Decl

    template<typename Func, typename Next>
    struct MultConstZeroSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct AddConstZeroSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct MultConstOneSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct OpConstSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct OpOrderSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct OpFactorizeSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct MultMatrixSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct MatrixSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct BinderSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func, typename Next>
    struct ResimplifyOperationSimplifyRule : BaseSimplifyRule<Func, Next> {};

    template<typename Func>
    struct Simplify {
      using Value = typename SimplifyRuleList<Func,
      MultMatrixSimplifyRule,
      MatrixSimplifyRule,
      MultConstZeroSimplifyRule,
      AddConstZeroSimplifyRule,
      MultConstOneSimplifyRule,
      OpConstSimplifyRule,
      OpOrderSimplifyRule,
      BinderSimplifyRule,
      OpFactorizeSimplifyRule,
      ResimplifyOperationSimplifyRule
      >::Value;
    };

    /////////////////
    //MultConstZeroSimplifyRule

    template<typename Ret, typename Param, typename Func, typename Next>
    struct MultConstZeroSimplifyRule<Multiply<IntegerConst<Ret, Param, 0>, Func>, Next> {
      using Value = IntegerConst<Ret, Param, 0>;
    };

    template<typename Ret, typename Param, typename Func, typename Next>
    struct MultConstZeroSimplifyRule<Multiply<Func, IntegerConst<Ret, Param, 0>>, Next> {
      using Value = IntegerConst<Ret, Param, 0>;
    };

    template<typename Ret, typename Param, typename Next>
    struct MultConstZeroSimplifyRule<Multiply<IntegerConst<Ret, Param, 0>, IntegerConst<Ret, Param, 0>>, Next> {
      using Value = IntegerConst<Ret, Param, 0>;
    };

    /////////////////
    //AddConstZeroSimplifyRule

    template<typename Ret, typename Param, typename Func, typename Next>
    struct AddConstZeroSimplifyRule<Add<IntegerConst<Ret, Param, 0>, Func>, Next> {
      using Value = typename Simplify<Func>::Value;
    };

    template<typename Ret, typename Param, typename Func, typename Next>
    struct AddConstZeroSimplifyRule<Add<Func, IntegerConst<Ret, Param, 0>>, Next> {
      using Value = typename Simplify<Func>::Value;
    };

    template<typename Ret, typename Param, typename Next>
    struct AddConstZeroSimplifyRule<Add<IntegerConst<Ret, Param, 0>, IntegerConst<Ret, Param, 0>>, Next> {
      using Value = IntegerConst<Ret, Param, 0>;
    };


    /////////////////
    //MultConstOneSimplifyRule

    template<typename Ret, typename Param, typename Func, typename Next>
    struct MultConstOneSimplifyRule<Multiply<IntegerConst<Ret, Param, 1>, Func>, Next> {
      using Value = typename Simplify<Func>::Value;
    };

    template<typename Ret, typename Param, typename Func, typename Next>
    struct MultConstOneSimplifyRule<Multiply<Func, IntegerConst<Ret, Param, 1>>, Next> {
      using Value = typename Simplify<Func>::Value;
    };

    template<typename Ret, typename Param, typename Next>
    struct MultConstOneSimplifyRule<Multiply<IntegerConst<Ret, Param, 1>, IntegerConst<Ret, Param, 1>>, Next> {
      using Value = IntegerConst<Ret, Param, 1>;
    };

    /////////////////
    // MultMatrixSimplifyRule

    template<typename Ret, typename Param, array_t ROWS1, array_t COLS1, array_t COLS2, typename Next, typename ...Funcs1, typename ...Funcs2>
    struct MultMatrixSimplifyRule<Multiply<Matrix<Ret, Param, ROWS1, COLS1, Funcs1...>, Matrix<Ret, Param, COLS1, COLS2, Funcs2...>>, Next> {
      using Value = typename Simplify<typename MatrixUtils::MatrixMultiplier<Multiply<Matrix<Ret, Param, ROWS1, COLS1, Funcs1...>, Matrix<Ret, Param, COLS1, COLS2, Funcs2...>>>::Value>::Value;
    };

    /////////////////
    // MatrixSimplifyRule

    template<typename Ret, typename Param, array_t ROWS, array_t COLS, typename Next, typename ...Funcs>
    struct MatrixSimplifyRule<Matrix<Ret, Param, ROWS, COLS, Funcs...>, Next> {
      using Value = Matrix<Ret, Param, ROWS, COLS, typename Simplify<Funcs>::Value...>;
    };

    /////////////////
    //ResimplifyOperationSimplifyRule

    template<template<typename, typename> class Op, typename Func1, typename Func2, typename Next>
    class ResimplifyOperationSimplifyRule<Op<Func1, Func2>, Next> {
      using SF1 = typename Simplify<Func1>::Value;
      using SF2 = typename Simplify<Func2>::Value;

      template<bool COND, DummyType DUMMY = DUMMY_VALUE>
      struct Helper {
        using Value = Op<SF1, SF2>;
      };

      template<DummyType DUMMY>
      struct Helper<true, DUMMY> {
        using Value = typename Simplify<Op<SF1, SF2>>::Value;
      };

      static constexpr bool SIMPLIFIABLE =
          (!TypeEqual<SF1, Func1>::VALUE) ||
          (!TypeEqual<SF2, Func2>::VALUE);

    public:
      using Value = typename Helper<SIMPLIFIABLE>::Value;
    };

    /////////////////
    //OpConstSimplifyRule

    template<typename Ret, typename Param, s32 VAL1, typename Func, typename Next>
    struct OpConstSimplifyRule<Compose<IntegerConst<Ret, Param, VAL1>, Func>, Next> {
      static_assert(TypeEqual<Param, typename Func::ReturnType>::VALUE, "Error : Can't compose");
      using Value = IntegerConst<Ret, typename Func::ParamType, VAL1>;
    };

    template<typename Ret, typename Param, s32 VAL1, s32 VAL2, typename Next>
    struct OpConstSimplifyRule<Multiply<IntegerConst<Ret, Param, VAL1>, IntegerConst<Ret, Param, VAL2>>, Next> {
      using Value = IntegerConst<Ret, Param, VAL1*VAL2>;
    };

    template<typename Ret, typename Param, s32 VAL1, s32 VAL2, typename Next>
    struct OpConstSimplifyRule<Divide<IntegerConst<Ret, Param, VAL1>, IntegerConst<Ret, Param, VAL2>>, Next> {
      using Value = IntegerConst<Ret, Param, VAL1/VAL2>;
    };

    template<typename Ret, typename Param, s32 VAL1, s32 VAL2, typename Next>
    struct OpConstSimplifyRule<Add<IntegerConst<Ret, Param, VAL1>, IntegerConst<Ret, Param, VAL2>>, Next> {
      using Value = IntegerConst<Ret, Param, VAL1+VAL2>;
    };

    template<typename Ret, typename Param, s32 VAL1, s32 VAL2, typename Next>
    struct OpConstSimplifyRule<Substract<IntegerConst<Ret, Param, VAL1>, IntegerConst<Ret, Param, VAL2>>, Next> {
      using Value = IntegerConst<Ret, Param, VAL1-VAL2>;
    };

    /////////////////
    //OpOrderSimplifyRule

    template<typename Ret, typename Param, typename Next>
    struct OpOrderSimplifyRule<Multiply<Sin<Ret, Param>, Cos<Ret, Param>>, Next> {
      using Value = Multiply<Cos<Ret, Param>, Sin<Ret, Param>>;
    };

    template<typename Ret, typename Param, s32 VAL, typename Func, typename Next>
    struct OpOrderSimplifyRule<Multiply<Func, IntegerConst<Ret, Param, VAL>>, Next> {
      using Value = typename Simplify<Multiply<IntegerConst<Ret, Param, VAL>, typename Simplify<Func>::Value>>::Value;
    };

    template<typename Ret, typename Param, s32 VAL, typename Func, typename Next>
    struct OpOrderSimplifyRule<Multiply<Multiply<IntegerConst<Ret, Param, VAL>, Func>, Func>, Next> {
      using Value = typename Simplify<Multiply<IntegerConst<Ret, Param, VAL>, typename Simplify<Multiply<typename Simplify<Func>::Value, typename Simplify<Func>::Value>>::Value>>::Value;
    };

    template<typename Ret, typename Param, s32 VAL, typename Func, typename Next>
    struct OpOrderSimplifyRule<Multiply<Func, Multiply<IntegerConst<Ret, Param, VAL>, Func>>, Next> {
      using Value = typename Simplify<Multiply<IntegerConst<Ret, Param, VAL>, typename Simplify<Multiply<typename Simplify<Func>::Value, typename Simplify<Func>::Value>>::Value>>::Value;
    };

    template<typename Ret, typename Param, s32 VAL1, s32 VAL2, typename Func, typename Next>
    struct OpOrderSimplifyRule<Multiply<IntegerConst<Ret, Param, VAL1>, Multiply<IntegerConst<Ret, Param, VAL2>, Func>>, Next> {
      using Value = typename Simplify<Multiply<typename Simplify<Multiply<IntegerConst<Ret, Param, VAL1>, IntegerConst<Ret, Param, VAL2>>>::Value, typename Simplify<Func>::Value>>::Value;
    };


    /////////////////
    //OpFactorizeSimplifyRule

    template<typename Func, typename Next>
    struct OpFactorizeSimplifyRule<Add<Func, Func>, Next> {
      using Value = Multiply<IntegerConst<typename Func::ReturnType, typename Func::ParamType, 2>, Func>;
    };

    template<typename Func, s32 VAL, typename Next>
    struct OpFactorizeSimplifyRule<Add<Multiply<IntegerConst<typename Func::ReturnType, typename Func::ParamType, VAL>, Func>, Func>, Next> {
      using Value = Multiply<IntegerConst<typename Func::ReturnType, typename Func::ParamType, VAL+1>, Func>;
    };

    template<typename Func, typename Next>
    struct OpFactorizeSimplifyRule<Multiply<Func, Func>, Next> {
      using Value = Compose<Pow<typename Func::ReturnType, typename Func::ReturnType, 2>, Func>;
    };

    template<typename Func, s32 VAL, typename Next>
    struct OpFactorizeSimplifyRule<Multiply<Multiply<Pow<typename Func::ReturnType, typename Func::ParamType, VAL>, Func>, Func>, Next> {
      using Value = Compose<Pow<typename Func::ReturnType, typename Func::ReturnType, VAL+1>, Func>;
    };

    /////////////////
    //BinderSimplifyRule

    template<typename Ret, typename Param, array_t ROWS, array_t COLS, typename ...Funcs, typename Func, typename Next>
    struct BinderSimplifyRule<Compose<Matrix<Ret, Param, ROWS, COLS, Funcs...>, Func>, Next> {
      using Value = typename Simplify<
      Matrix<Ret, typename Func::ParamType, ROWS, COLS,
      Compose<Funcs, Func>...>
      >::Value;
    };

    template<typename Func1, typename Func2, typename Ret, typename Param, array_t ROW, array_t COL, typename Next>
    struct BinderSimplifyRule<Compose<Multiply<Func1, Func2>, Binder<Ret, Param, ROW, COL>>, Next> {
      using Value = typename Simplify<
      Multiply<
      typename Simplify<Compose<Func1, Binder<Ret, Param, ROW, COL>>>::Value,
      typename Simplify<Compose<Func2, Binder<Ret, Param, ROW, COL>>>::Value
      >
      >::Value;
    };

    template<typename Func1, typename Func2, typename Ret, typename Param, array_t ROW, array_t COL, typename Next>
    struct BinderSimplifyRule<Compose<Divide<Func1, Func2>, Binder<Ret, Param, ROW, COL>>, Next> {
      using Value = typename Simplify<
      Divide<
      typename Simplify<Compose<Func1, Binder<Ret, Param, ROW, COL>>>::Value,
      typename Simplify<Compose<Func2, Binder<Ret, Param, ROW, COL>>>::Value
      >
      >::Value;
    };

    template<typename Func1, typename Func2, typename Ret, typename Param, array_t ROW, array_t COL, typename Next>
    struct BinderSimplifyRule<Compose<Add<Func1, Func2>, Binder<Ret, Param, ROW, COL>>, Next> {
      using Value = typename Simplify<
      Add<
      typename Simplify<Compose<Func1, Binder<Ret, Param, ROW, COL>>>::Value,
      typename Simplify<Compose<Func2, Binder<Ret, Param, ROW, COL>>>::Value
      >
      >::Value;
    };

    template<typename Func1, typename Func2, typename Ret, typename Param, array_t ROW, array_t COL, typename Next>
    struct BinderSimplifyRule<Compose<Substract<Func1, Func2>, Binder<Ret, Param, ROW, COL>>, Next> {
      using Value = typename Simplify<
      Substract<
      typename Simplify<Compose<Func1, Binder<Ret, Param, ROW, COL>>>::Value,
      typename Simplify<Compose<Func2, Binder<Ret, Param, ROW, COL>>>::Value
      >
      >::Value;
    };

    template<typename Ret1, typename Param1, s32 VAL1, typename Ret2, typename Param2, array_t ROW, array_t COL, typename Next>
    struct BinderSimplifyRule<Compose<IntegerConst<Ret1, Param1, VAL1>, Binder<Ret2, Param2, ROW, COL>>, Next> {
      static_assert(TypeEqual<Param1, Ret2>::VALUE, "Invalid binding type");
      using Value = IntegerConst<Ret1, Param2, VAL1>;
    };

  }

template<typename Func> using Simplify = typename PrivateSimplify::Simplify<Func>::Value;

}

#endif//CAS_SIMPLIFY_HPP
