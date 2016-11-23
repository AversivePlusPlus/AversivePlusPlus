#ifndef IK_INITIAL_CHAIN_ELEMENT_HPP
#define IK_INITIAL_CHAIN_ELEMENT_HPP

#include <ik/chain_element.hpp>

namespace IK {

  template<typename Func>
  class InitialChainElement {
  public:
    using LocalTransformation = CAS::Simplify<Func>;

  public:
    static constexpr u16 NUM_VAR = 0;

    template<u16 GLOBAL_NUM_VAR>
    struct Globalized {
      using Transformation =
        CAS::Simplify<CAS::Compose<
          LocalTransformation,
          CAS::IntegerConst<typename LocalTransformation::ParamType, Matrix<typename LocalTransformation::ParamType, GLOBAL_NUM_VAR,1>, 0>
        >>;

      template<u16 VAR>
      using PartialDerivateTransformation = Transformation;
    };
  };

}

#endif//IK_INITIAL_CHAIN_ELEMENT_HPP
