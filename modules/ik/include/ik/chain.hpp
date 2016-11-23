#ifndef IK_CHAIN_HPP
#define IK_CHAIN_HPP

#include <ik/chain_element.hpp>
#include <ik/constant_chain_element.hpp>
#include <ik/variable_chain_element.hpp>
#include <ik/initial_chain_element.hpp>

namespace IK {

  namespace PrivateChainBuilder {
    template<typename Element>
    class ChainBuilder {
    public:
      using Chain = ChainElement<Element>;
      template<typename Func> using BuildConstant = ChainBuilder<ConstantChainElement<Func, Element>>;
      template<typename Func> using BuildVariable = ChainBuilder<VariableChainElement<Func, Element>>;
    };

    template<typename Func>
    class ChainBuilder<InitialChainElement<Func>> {
    public:
      template<typename F> using BuildConstant = ChainBuilder<ConstantChainElement<F, InitialChainElement<Func>>>;
      template<typename F> using BuildVariable = ChainBuilder<VariableChainElement<F, InitialChainElement<Func>>>;
    };
  }

  template<typename Func> using ChainBuilder = PrivateChainBuilder::ChainBuilder<InitialChainElement<Func>>;

}

#endif//IK_CHAIN_HPP
