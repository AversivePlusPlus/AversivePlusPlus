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
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

namespace Base {

  //! \class Singleton singleton.hpp <base/singleton.hpp>
  //! \brief Interface for classes that should have only one instance.
  //! \param _BASE : The class that should have only one instance.
  template<typename _BASE>
  class Singleton {
  protected:
    //! \brief Protected default constructor, to avoid instanciation.
    inline Singleton(void) {
    }

    //! \brief Protected copy constructor, to avoid copy construction.
    inline Singleton(const Singleton&) {
    }

  public:
    //! \brief Access to the single instance of the class.
    //! \return A reference to the instance.
    static inline _BASE& instance(void) {
      static _BASE inst;
      return inst;
    }
  };

}

#ifndef AVERSIVE_DISABLE_BASE_DEFAULT
using namespace Base;
#endif//AVERSIVE_DISABLE_BASE_DEFAULT

#endif//SINGLETON_HPP
