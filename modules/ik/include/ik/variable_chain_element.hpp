#ifndef IK_VARIABLE_CHAIN_ELEMENT_HPP
#define IK_VARIABLE_CHAIN_ELEMENT_HPP

#include <ik/chain_element.hpp>

namespace IK {

  template<typename Func, typename Next>
  class VariableChainElement {
  public:
    using LocalTransformation = CAS::Simplify<Func>;

  public:
    static constexpr u16 NUM_VAR = Next::NUM_VAR+1;

    template<u16 GLOBAL_NUM_VAR>
    class Globalized {
    private:
      using M =
        CAS::Simplify<CAS::Compose<
          LocalTransformation,
          CAS::Binder<typename LocalTransformation::ParamType,
                      Matrix<typename LocalTransformation::ParamType, GLOBAL_NUM_VAR,1>,
                      NUM_VAR-1,
                      0>
        >>;

      using dM =
        CAS::Simplify<CAS::Compose<
          CAS::Simplify<CAS::Derivate<LocalTransformation>>,
          CAS::Binder<typename LocalTransformation::ParamType,
                      Matrix<typename LocalTransformation::ParamType, GLOBAL_NUM_VAR,1>,
                      NUM_VAR-1,
                      0>
        >>;

      template<u16 VAR, u8 DUMMY=0>
      struct PartialDerivateTransformationCase {
        using Value = CAS::Multiply<typename Next::template Globalized<GLOBAL_NUM_VAR>::template PartialDerivateTransformation<VAR>, M>;
      };

      template<u8 DUMMY>
      struct PartialDerivateTransformationCase<NUM_VAR-1, DUMMY> {
        using Value = CAS::Multiply<typename Next::template Globalized<GLOBAL_NUM_VAR>::template PartialDerivateTransformation<NUM_VAR-1>, dM>;
      };

    public:
      using Transformation = CAS::Multiply<typename Next::template Globalized<GLOBAL_NUM_VAR>::Transformation, M>;

      template<u16 VAR>
      using PartialDerivateTransformation = typename PartialDerivateTransformationCase<VAR>::Value;
    };
  };

}

#endif//IK_VARIABLE_CHAIN_ELEMENT_HPP
