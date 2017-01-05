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
#ifndef BOOL_REF_HPP
#define BOOL_REF_HPP

#include "config.hpp"
#include "integer.hpp"

namespace Aversive {

namespace Base {

  //! \class BoolRef bool_ref.hpp <base/bool_ref.hpp>
  //! \brief This class represents a reference to a boolean.
  class BoolRef {
  private:
    //! \brief The address where the boolean is stored.
    u8& _byte;

    //! \brief The mask to retrieve the required bit.
    u8 _mask;

    //! \brief Default constructor.
    BoolRef(void);

  public:
    //! \brief Constructor to reference a boolean within a byte.
    //! \param byte : a reference to the byte where the boolean is stored.
    //! \param bit : the index of the bit at which the boolean is stored.
    inline BoolRef(u8& byte, u8 bit)
      : _byte(byte), _mask(1 << bit) {
    }

    //! \brief Constructor to reference a regular boolean.
    //! \warning This assumes that the boolean is coded by the first bit at the address of the given boolean, however, how a boolean is represented in memory is platform-dependent.
    //! \todo Investigate how are booleans reprensented in memory on the supported platforms by Aversive++ and possibly specialise this method per platform (according to the first test, it works on x86-64).
    inline BoolRef(const bool& b)
      : _byte((u8&) b), _mask(1) {
    }

    //! \brief Copy constructor, the new BoolRef references the same boolean.
    inline BoolRef(const BoolRef& other)
      : _byte(other._byte), _mask(other._mask) {
    }

    //! \brief Cast operator to retrieve a regular C++ boolean representing the referenced boolean.
    //! \return A regular C++ boolean.
    inline operator bool(void) const {
      return (bool) (_byte & _mask);
    }

    //! \brief Assign a new value to the referenced boolean.
    //! \param b : the new boolean value.
    //! \return A reference to the BoolRef.
    inline BoolRef& operator=(bool b) {
      if(b) {
          _byte |= _mask;
        }
      else {
          _byte &= ~_mask;
        }

      return (*this);
    }

    //! \brief Copy the value of the supplied boolean by its reference to the referenced boolean.
    //! \param other : a reference to the boolean this boolean copying its value from.
    //! \return A reference to the BoolRef.
    //! \warning This does not make the BoolRef on which the method is applied reference the same boolean as the BoolRel supplied as argument. It really emulates a true reference to a boolean.
    inline BoolRef& operator=(const BoolRef& other) {
      return (*this) = (bool) other;
    }

    //! \brief += operator overloading.
    //! \param b : the boolean to add to the referenced one.
    //! \return A reference to the BoolRef.
    inline BoolRef& operator+=(bool b) {
      return (*this) = (bool) (*this) + b;
    }

    //! \brief -= operator overloading.
    //! \param b : the boolean to substract to the referenced one.
    //! \return A reference to the BoolRef.
    inline BoolRef& operator-=(bool b) {
      return (*this) = (bool) (*this) - b;
    }

    //! \brief *= operator overloading.
    //! \param b : the boolean to multiply with the referenced one.
    //! \return A reference to the BoolRef.
    inline BoolRef& operator*=(bool b) {
      return (*this) = (bool) (*this) * b;
    }

    //! \brief /= operator overloading.
    //! \param b : the boolean to divide the referenced one by.
    //! \return A reference to the BoolRef.
    inline BoolRef& operator/=(bool b) {
      return (*this) = (bool) (*this) / b;
    }

    //! \brief %= operator overloading.
    //! \param b : the boolean to divide the referenced one by.
    //! \return A reference to the BoolRef.
    inline BoolRef& operator%=(bool b) {
      return (*this) = (bool) (*this) % b;
    }
  };

}

}

#endif//BOOL_REF_HPP
