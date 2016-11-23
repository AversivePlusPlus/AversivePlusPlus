#ifndef IK_UTILS_HPP
#define IK_UTILS_HPP

#include <cas/function.hpp>
#include <cas/simplify.hpp>

namespace IK {

  namespace utils {

    namespace PrivateHomogeneousZeroVerctor {
      template<typename Ret, typename Param, int ROWS>
      class Vector {
      private:
        using G = CAS::General<Ret, Param>;
        template<s32 VAL> using C = typename G::Const::template Integer<VAL>;
        template<int VAL> using C0 = typename G::Const::template Integer<0>;
        template<int ...ARGS> using OneEndingVector = typename G::template Matrix<ROWS,1>::template Any<C0<ARGS>..., C<1>>;

      public:
        using Value = typename CAS::PrivateSimplify::MatrixUtils::ListBuilder<OneEndingVector, ROWS-1>::Value;
      };
    }

    template<typename Ret, typename Param, array_t ROWS> using HomogeneousZeroVector = typename PrivateHomogeneousZeroVerctor::Vector<Ret, Param, (int)ROWS>::Value;

  }

  namespace utils {

    template<typename T>
    struct GetMatrixRows {
      static_assert(sizeof(T)&&!sizeof(T), "ERROR!!!");
    };

    template<typename T, array_t ROWS, array_t COLS>
    struct GetMatrixRows<Matrix<T, ROWS, COLS>> {
      static constexpr array_t VALUE = ROWS;
    };

  }

  namespace utils {

    namespace PrivateMatrixTransposer {
      template<typename Func>
      struct MatrixTransposer {
        static_assert(sizeof(Func)&&!sizeof(Func), "ERROR!!!");
      };

      template<typename Ret, typename Param, array_t ROWS, array_t COLS, typename ...Args>
      struct MatrixTransposer<CAS::Matrix<Ret, Param, ROWS, COLS, Args...>> {
        using M = CAS::Matrix<Ret, Param, ROWS, COLS, Args...>;

        template<array_t ROW, array_t COL>
        using TransposedGetter = CAS::PrivateSimplify::MatrixUtils::MatrixFunctionGetter<M, COL, ROW>;


        template<int ARGS>
        using MyMatrixCase = typename TransposedGetter<ARGS/ROWS, ARGS%ROWS>::Value;

        template<int ...ARGS>
        using MatrixFunc = CAS::Matrix<Ret, Param, COLS, ROWS, MyMatrixCase<ARGS>...>;

        using Value = typename CAS::PrivateSimplify::MatrixUtils::ListBuilder<MatrixFunc, ROWS*COLS>::Value;
      };
    }

    template<typename Func>
    using MatrixTransposer = typename PrivateMatrixTransposer::MatrixTransposer<Func>::Value;

  }

  namespace utils {

    namespace PrivateMatrixFromRowBuilder {
      template<typename ...Args>
      struct _MatrixFromRowBuilder {};

      template<typename Ret, typename Param, array_t COLS, typename ...Args, typename ...Nexts>
      struct _MatrixFromRowBuilder<CAS::Matrix<Ret, Param, 1, COLS, Args...>, Nexts...> {
        using Next = _MatrixFromRowBuilder<Nexts...>;

        template<template<typename ...> class List, typename ...MyArgs>
        using MyListBuilder = typename Next::template MyListBuilder<List, MyArgs..., Args...>;

        static constexpr array_t ROWS = Next::ROWS+1;
        template<typename ...Funcs>
        using MyMatrix = CAS::Matrix<Ret, Param, ROWS, COLS, Funcs...>;

        using Value = MyListBuilder<MyMatrix>;
      };

      template<typename Ret, typename Param, array_t COLS, typename ...Args>
      struct _MatrixFromRowBuilder<CAS::Matrix<Ret, Param, 1, COLS, Args...>> {
        template<template<typename ...> class List, typename ...MyArgs>
        using MyListBuilder = List<MyArgs..., Args...>;

        static constexpr array_t ROWS = 1;
        using Value = CAS::Matrix<Ret, Param, ROWS, COLS, Args...>;
      };
    }

    template<typename ...Args>
    using MatrixFromRowBuilder = typename PrivateMatrixFromRowBuilder::_MatrixFromRowBuilder<Args...>::Value;

  }

  namespace utils {

    template<typename Func>
    struct MatrixElementType {};

    template<typename T, array_t ROWS, array_t COLS>
    struct MatrixElementType<Matrix<T, ROWS, COLS>> {
      using Value = T;
    };

  }
}

#endif//IK_UTILS_HPP
