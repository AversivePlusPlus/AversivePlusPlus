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
#ifndef DEVICE_ASYNCHRONOUS_HPP
#define DEVICE_ASYNCHRONOUS_HPP

namespace Aversive {

namespace Device {

  //! \brief Asynchronous interface used by devices that need periodical computation
  //! \param Derived : The class that inherits from the interface
  /*!
    The Asynchronous device need the update method to be called regularly (and even best at a constant period).
    If the update function is not called, the device may do nothing.
   */
  template<typename Derived>
  class Asynchronous {
  public:
    //! \brief The method that need to be called periodically
    inline void update(void) {
      static_cast<Derived*>(this)->update();
    }
  };

  //! \brief A Asynchronous device that update two Asynchronous devices at the same time (composite pattern)
  //! \param First : First Asynchronous device to be updated
  //! \param Second : Second Asynchronous device to be updated
  template<typename First, typename Second>
  class AsynchronousChain : Asynchronous<AsynchronousChain<First, Second>> {
    Asynchronous<First>& _first;
    Asynchronous<Second>& _second;

  public:
    //! \brief constructor
    //! \param first : First Asynchronous device to be updated
    //! \param second : Second Asynchronous device to be updated
    AsynchronousChain(Asynchronous<First>& first, Asynchronous<Second>& second)
      : _first(first), _second(second) {
    }

    //! \brief Update function : updates first and then updates second
    inline void update(void) {
      _first.update();
      _second.update();
    }
  };

}

}

#endif//DEVICE_ASYNCHRONOUS_HPP
