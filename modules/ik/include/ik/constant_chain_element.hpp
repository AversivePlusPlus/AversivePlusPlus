#ifndef IK_CONSTANT_CHAIN_ELEMENT_HPP
#define IK_CONSTANT_CHAIN_ELEMENT_HPP

#include <ik/chain_element.hpp>

namespace IK {

  template<typename Func, typename Next>
  class ConstantChainElement {
  public:
    using LocalTransformation = CAS::Simplify<Func>;

  public:
    static constexpr u16 NUM_VAR = Next::NUM_VAR;

    template<u16 GLOBAL_NUM_VAR>
    struct Globalized {
    private:
      using M =
        CAS::Simplify<CAS::Compose<
          LocalTransformation,
          CAS::IntegerConst<typename LocalTransformation::ParamType, Matrix<typename LocalTransformation::ParamType, GLOBAL_NUM_VAR,1>, 0>
        >>;

    public:
      using Transformation = CAS::Multiply<typename Next::template Globalized<GLOBAL_NUM_VAR>::Transformation, M>;

      template<u16 VAR>
      using PartialDerivateTransformation = CAS::Multiply<
        typename Next::template Globalized<GLOBAL_NUM_VAR>::template PartialDerivateTransformation<VAR>,
        M
      >;
    };
  };

}

#endif//IK_CONSTANT_CHAIN_ELEMENT_HPP
