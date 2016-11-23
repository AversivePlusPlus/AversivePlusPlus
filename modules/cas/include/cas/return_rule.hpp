#ifndef CAS_RETURN_RULE_HPP
#define CAS_RETURN_RULE_HPP

#include <base/type_traits.hpp>
#include <base/matrix.hpp>

namespace CAS {

  namespace ReturnRule {

    enum class Operation { MULTIPLY, DIVIDE, ADD, SUBSTRACT };

    template<Operation OP, typename T1, typename T2, typename Next>
    struct BaseReturnRule {
      static_assert(
          sizeof(T1) && !sizeof(T1),
          "ERROR : Invalid operation"
          );

      using Type = void;
    };

    template<Operation OP, typename T, typename Next>
    struct BaseReturnRule<OP, T, T, Next> {
      using Type = T;
    };

    template<
        template<Operation, typename, typename, typename> class R1,
        template<Operation, typename, typename, typename> class ...Rules
        >
    struct ReturnRuleList {
      template<Operation OP, typename T1, typename T2>
      using Rule = R1<OP, T1, T2, typename ReturnRuleList<Rules...>::template Rule<OP, T1, T2>>;
    };

    template<
        template<Operation, typename, typename, typename> class R1
        >
    struct ReturnRuleList<R1> {
      template<Operation OP, typename T1, typename T2>
      using Rule = R1<OP, T1, T2, void>;
    };

    template<Operation OP, typename T1, typename T2, typename Next>
    struct MatrixReturnRule {
      using Type = typename Next::Type;
    };

    template<typename T, array_t ROWS1, array_t COLS1, array_t COLS2, typename Next>
    struct MatrixReturnRule<Operation::MULTIPLY, Matrix<T, ROWS1, COLS1>, Matrix<T, COLS1, COLS2>, Next> {
      using Type = Matrix<T, ROWS1, COLS2>;
    };

    template<typename T, array_t ROWS, array_t COLS, typename Next>
    struct MatrixReturnRule<Operation::MULTIPLY, T, Matrix<T, ROWS, COLS>, Next> {
      using Type = Matrix<T, ROWS, COLS>;
    };

    template<typename T, array_t ROWS, array_t COLS, typename Next>
    struct MatrixReturnRule<Operation::DIVIDE, Matrix<T, ROWS, COLS>, Matrix<T, ROWS, COLS>, Next> {
      static_assert(
          sizeof(T) && !sizeof(T),
          "ERROR : Can't divide two matrices"
          );

      using Type = void;
    };

    template<Operation OP, typename T1, typename T2>
    struct OperationReturnRule {
      using Type = typename ReturnRuleList<
      MatrixReturnRule,
      BaseReturnRule
      >::template Rule<OP, T1, T2>::Type;
    };

  }
}

#endif//CAS_RETURN_RULE_HPP
