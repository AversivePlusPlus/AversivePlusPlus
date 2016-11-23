#ifndef IK_CHAIN_ELEMENT_HPP
#define IK_CHAIN_ELEMENT_HPP

#include <cas/simplify.hpp>
#include <cas/matrix_simplify.hpp>
#include <cas/derivate.hpp>
#include <ik/utils.hpp>

namespace IK {

  template<typename Derived>
  class ChainElement {
  protected:
    using LocalTransformation = typename Derived::LocalTransformation;

  protected:
    using ReturnType = typename utils::MatrixElementType<typename LocalTransformation::ReturnType>::Value;
    using ParamType = typename LocalTransformation::ParamType;
    static constexpr array_t RETURN_ROWS = utils::GetMatrixRows<typename LocalTransformation::ReturnType>::VALUE;

  protected:
    static constexpr u16 NUM_VAR = Derived::NUM_VAR;

    template<u16 GLOBAL_NUM_VAR>
    struct Globalized {
      using Transformation = typename Derived::template Globalized<GLOBAL_NUM_VAR>::Transformation;

      template<u16 VAR>
      using PartialDerivateTransformation =
        typename Derived::template Globalized<GLOBAL_NUM_VAR>::template PartialDerivateTransformation<VAR>;
    };

    using Global = Globalized<NUM_VAR>;

  private:
    using E = CAS::Simplify<CAS::Compose<
      utils::HomogeneousZeroVector<ReturnType, ParamType, RETURN_ROWS>,
      CAS::IntegerConst<ReturnType, Matrix<ParamType, NUM_VAR,1>, 0>
    >>;

    using Endpoint = CAS::Simplify<CAS::Multiply<typename Global::Transformation, E>>;

    template<u16 VAR>
    using PartialDerivateEndpoint =
      CAS::Simplify<CAS::Multiply<typename Global::template PartialDerivateTransformation<VAR>, E>>;

    template<int ...ARGS>
    using BuildFromRowsDerivate =
      utils::MatrixFromRowBuilder<utils::MatrixTransposer<PartialDerivateEndpoint<ARGS>>...>;

    using Jacobian = typename CAS::PrivateSimplify::MatrixUtils::ListBuilder<BuildFromRowsDerivate, NUM_VAR>::Value;

  public:
    static inline typename Global::Transformation::ReturnType matrix(Matrix<ParamType, NUM_VAR,1> values) {
      return Global::Transformation::apply(values);
    }

    static inline typename Endpoint::ReturnType forward(Matrix<ParamType, NUM_VAR,1> values) {
      return Endpoint::apply(values);
    }

    static inline Matrix<ParamType, NUM_VAR,1> inverseStep(typename Endpoint::ReturnType target, Matrix<ReturnType, NUM_VAR,1> init_values) {
      auto position = forward(init_values);
      auto J = Jacobian::apply(init_values);

      return (J * (target-position)).unit();
    }
  };

}

#endif//IK_CHAIN_ELEMENT_HPP
