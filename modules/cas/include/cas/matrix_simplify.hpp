#ifndef CAS_MATRIX_SIMPLIFY_HPP
#define CAS_MATRIX_SIMPLIFY_HPP

#include <cas/function.hpp>

namespace CAS {
  namespace PrivateSimplify {
    namespace MatrixUtils {

      template<template<int ...A> class List, array_t N, int ...ARGS>
      struct ListBuilder {
        using Value = typename ListBuilder<List, N-1, N-1, ARGS...>::Value;
      };

      template<template<int ...A> class List, int ...ARGS>
      struct ListBuilder<List, 0, ARGS...> {
        using Value = List<ARGS...>;
      };

      template<typename MFunc, array_t ROW, array_t COL>
      struct MatrixFunctionGetter {
        static_assert(sizeof(MFunc) && !sizeof(MFunc), "ERROR");
        using Value = void;
      };

      template<typename Ret, typename Param, array_t ROW, array_t COL, array_t ROWS, array_t COLS, typename ...Args>
      class MatrixFunctionGetter<Matrix<Ret, Param, ROWS, COLS, Args...>, ROW, COL> {
        static_assert(ROW < ROWS, "ERROR : invalid matrix index");
        static_assert(COL < COLS, "ERROR : invalid matrix index");

        template<array_t INDEX, array_t CUR, typename ...SubArgs>
        struct Helper {};

        template<array_t INDEX, array_t CUR, typename SubArg1, typename ...SubArgs>
        struct Helper<INDEX, CUR, SubArg1, SubArgs...> { using Value = typename Helper<INDEX, CUR+1, SubArgs...>::Value; };

        template<array_t INDEX, array_t CUR>
        struct Helper<INDEX, CUR> { using Value = IntegerConst<Ret, Param, 0>; };

        template<array_t INDEX, typename SubArg1, typename ...SubArgs>
        struct Helper<INDEX, INDEX, SubArg1, SubArgs...> { using Value = SubArg1; };

      public:
        using Value = typename Helper<ROW*COLS+COL, 0, Args...>::Value;
      };


      template<typename M1, typename M2, array_t ROW, array_t COL>
      class MatrixCaseMultiplier {
      public:
        static_assert(sizeof(M1) && !sizeof(M1), "ERROR");
        using Value = void;
      };

      template<template<typename, typename> class CFunc, typename Arg1, typename ...Args>
      class Chained {
      public:
        using Value = CFunc<Arg1, typename Chained<CFunc, Args...>::Value>;
      };

      template<template<typename, typename> class CFunc, typename Arg1>
      class Chained<CFunc, Arg1> {
      public:
        using Value = Arg1;
      };

      template<typename Ret, typename Param, array_t ROW, array_t COL, array_t ROWS1, array_t COLS1, array_t MROWS, array_t COLS2, typename ...Args1, typename ...Args2>
      class MatrixCaseMultiplier<Matrix<Ret, Param, ROWS1, COLS1, Args1...>, Matrix<Ret, Param, MROWS, COLS2, Args2...>, ROW, COL> {
        using M1 = Matrix<Ret, Param, ROWS1, COLS1, Args1...>;
        using M2 = Matrix<Ret, Param, MROWS, COLS2, Args2...>;
        template<int ARG> using MyMult = Multiply<typename MatrixFunctionGetter<M1, ROW, ARG>::Value, typename MatrixFunctionGetter<M2, ARG, COL>::Value>;
        template<typename F1, typename F2> using MyAdd = Add<F1, F2>;
        template<int ...ARGS> using MyCase = typename Chained<MyAdd,MyMult<ARGS>...>::Value;
      public:
        using Value = typename ListBuilder<MyCase, COLS1>::Value;
      };


      template<typename Func>
      class MatrixMultiplier {};

      template<typename Ret, typename Param, array_t ROWS1, array_t COLS1, array_t COLS2, typename ...Args1, typename ...Args2>
      class MatrixMultiplier<Multiply<Matrix<Ret, Param, ROWS1, COLS1, Args1...>, Matrix<Ret, Param, COLS1, COLS2, Args2...>>> {
        using M1 = Matrix<Ret, Param, ROWS1, COLS1, Args1...>;
        using M2 = Matrix<Ret, Param, COLS1, COLS2, Args2...>;
        template<int ARGS> using MatrixIdToRC = typename MatrixCaseMultiplier<M1, M2, ARGS/COLS2, ARGS%COLS2>::Value;
        template<int ...ARGS> using MatrixF = Matrix<Ret, Param, ROWS1, COLS2, MatrixIdToRC<ARGS>...>;
      public:
        using Value = typename ListBuilder<MatrixF, ROWS1*COLS2>::Value;
      };

    }
  }
}

#endif//CAS_MATRIX_SIMPLIFY_HPP
