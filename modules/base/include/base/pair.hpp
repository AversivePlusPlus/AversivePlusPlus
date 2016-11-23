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
#ifndef PAIR_HPP
#define PAIR_HPP

#include "integer.hpp"

namespace Base {

  //! \class Pair pair.hpp <base/pair.hpp>
  //! \brief Two-member tuple.
  //! \param _LeftType : left member type.
  //! \param _RightType : right member type.
  //! \note This class is specialized for two-boolean tuples. See Pair<bool, bool> for more information.
  template<typename _LeftType, typename _RightType>
  class Pair {
  public:
    //! \brief Left member's type.
    typedef _LeftType LeftType;

    //! \brief Right member's type.
    typedef _RightType RightType;

    //! \brief Left member's reference type.
    typedef LeftType& LeftRef;

    //! \brief Right member's reference type.
    typedef RightType& RightRef;

    //! \brief Left member's constant reference type.
    typedef const LeftType& LeftConstRef;

    //! \brief Right member's constant reference type.
    typedef const RightType& RightConstRef;

  private:
    //! \brief The left member.
    LeftType _left;

    //! \brief The right member.
    RightType _right;

  public:
    //! \brief Default Constructor.
    //! \attention The objects within the pair are not set to any value (i.e.: their default constructor is called).
    constexpr inline Pair(void) {
    }

    //! \brief Constructor with parameters.
    //! \param l : a reference to the object to copy in the left member.
    //! \param r : a reference to the object to copy in the right member.
    //! \attention Left and right types must have a copy constructor.
    constexpr inline Pair(LeftConstRef l, RightConstRef r)
      : _left(l), _right(r) {
    }

    //! \brief Copy Constructor.
    //! \param other : the pair to copy.
    constexpr inline Pair(const Pair& other)
      : _left(other._left), _right(other._right) {
    }

    //! \brief Copy Operator.
    //! \param other : the pair to copy.
    //! \return A reference to the pair that has been written.
    inline Pair& operator=(const Pair& other) {
      _left = other._left;
      _right = other._right;
      return (*this);
    }

    //! \brief Access the left member.
    //! \return The reference to the left member.
    constexpr inline LeftRef left(void) {
      return _left;
    }

    //! \brief Access the right member.
    //! \return The reference to the right member.
    constexpr inline RightRef right(void) {
      return _right;
    }
  };

}

#ifndef AVERSIVE_DISABLE_BASE_DEFAULT
using namespace Base;
#endif//AVERSIVE_DISABLE_BASE_DEFAULT

#endif//PAIR_HPP
