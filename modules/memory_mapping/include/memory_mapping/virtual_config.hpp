/*
Copyright (c) 2015, Xenomorphales
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Aversive++ nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#ifndef VIRTUAL_CONFIG_HPP
#define VIRTUAL_CONFIG_HPP

#include "memory_mapping.hpp"
#include <base/static_list.hpp>

namespace MemoryMapping {

  //! \brief This class is the equivalent of Config class associated with Field, but for VirtualField class
  /*!
   * Basically, it is a list of Config objects.
   */
  template<typename Config, typename ... Next>
  struct VirtualConfig {
  public:
    //! \brief The list of configs
    const StaticList<const Config, const Next...> CONFIGS;
    
  public:
    //! \brief Constructor
    //! \param config : The first Config of the list 
    //! \param next : The remaining configs of the list
    constexpr VirtualConfig(const Config config, const Next... next)
      : CONFIGS(config, next...) {
    }

#define MACRO_DEFINE_COMPAR(op)						\
    template<typename... Configs>					\
    inline bool operator op(const VirtualConfig<Configs...>& other) const { \
      Private::VirtualFieldIsEqualVisitor visitor;			\
      pair_static_list_foreach(CONFIGS, other.CONFIGS, visitor);	\
      return visitor.res op true;					\
    }									\
    template<typename... Fields>					\
    inline bool operator op(const VirtualField<Fields...>& field) const { \
      return field op *this;						\
    }									\
    
    MACRO_DEFINE_COMPAR(==);
    MACRO_DEFINE_COMPAR(!=);
    
#undef MACRO_DEFINE_COMPAR

  };
    
  //! \brief This is a helper function that enables the developper to use auto keyword
  /*!
   * VirtualConfig type can be long to write ! Why not use auto instead of loosing your time ?
   *
   * Example : 
   *        
   *        // Create groups
   *        struct G1;
   *        struct G2;   
   *        
   *        // Create registers
   *        static constexpr Register8<G1> REG1 = 0x0001;
   *        static constexpr Register8<G2> REG2 = 0x0002;
   *        
   *        // Create fields
   *        static constexpr Field8<G1, 0b0011> FIELD1 = REG1;
   *        static constexpr Field8<G2, 0b1100> FIELD2 = REG2;
   *        
   *        // Create virtual_fields
   *        static constexpr auto VFIELD = make_virtual_field(FIELD1, FIELD2);
   * 
   *        // Create configs
   *        static constexpr auto CONFIG1 = make_config(FIELD1, 0b11);
   *        static constexpr auto CONFIG2 = make_config(FIELD2, 0b11);
   *        
   *        // Create virtual_configs
   *        static constexpr auto VCONFIG = make_virtual_config(CONFIG1, CONFIG2);
   * 
   *        [...]
   *        
   *        VFIELD = VCONFIG;
   * 
   */
  template<typename Config, typename ... Next>
  constexpr VirtualConfig<Config, Next...> make_virtual_config(const Config config, const Next... next) {
    return VirtualConfig<Config, Next...>(config, next...);
  }
  
}

#endif//VIRTUAL_CONFIG_HPP
