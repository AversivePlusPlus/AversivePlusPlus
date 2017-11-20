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
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "config.hpp"
#include "array.hpp"

#include <math.h>

namespace Aversive {

namespace Base {

  template<typename T, umax SIZE, typename _IndexType = u16>
  class Subarray {
  public:
    using IndexType = _IndexType;
    
  private:
    Array<T, SIZE, IndexType>& _array;
    IndexType _begin;
    IndexType _end;

  public:
    constexpr Subarray(Array<T, SIZE, IndexType>& array, IndexType begin, IndexType end)
      : _array(array), _begin(begin), _end(end) {
    }

    T& operator[](IndexType i) {
      return _array[_begin+i];
    }
  };


  template<typename T, umax ROWS, umax COLS, typename _IndexType = u16>
  class Matrix {
  public:
    using IndexType = _IndexType;
    
  private:
    Array<T, ROWS*COLS, IndexType> _data;

  public:
    constexpr Matrix(void)
      : _data{(T)0} {
    }

    template<typename ...TArgs>
    constexpr Matrix(TArgs ...args)
      : _data{args...} {
    }

    IndexType rows(void) {
      return ROWS;
    }

    IndexType cols(void) {
      return COLS;
    }

    inline Subarray<T, ROWS*COLS, IndexType> operator[](IndexType row) {
      return Subarray<T, ROWS*COLS>(_data, row*COLS, row*(COLS+1));
    }

    inline T& operator()(IndexType row, IndexType col) {
      return _data[row*COLS+col];
    }

    inline const T& operator()(IndexType row, IndexType col) const {
      return _data[row*COLS+col];
    }

    constexpr Matrix<T, ROWS, COLS, IndexType> operator*(T val) {
      return _data*val;
    }

    constexpr Matrix<T, ROWS, COLS, IndexType> operator/(T val) {
      return _data/val;
    }

    Matrix<T, ROWS, COLS, IndexType>& operator-=(Matrix other) {
      for(IndexType col = 0 ; col < COLS ; col++) {
          for(IndexType row = 0 ; row < ROWS ; row++) {
              (*this)[row][col] = (*this)[row][col] - other[row][col];
            }
        }
      return *this;
    }

    Matrix<T, ROWS, COLS, IndexType>& operator+=(Matrix other) {
      for(IndexType col = 0 ; col < COLS ; col++) {
          for(IndexType row = 0 ; row < ROWS ; row++) {
              (*this)[row][col] = (*this)[row][col] + other[row][col];
            }
        }
      return *this;
    }

    Matrix<T, ROWS, COLS, IndexType> operator-(Matrix other) {
      Matrix ret;

      for(IndexType col = 0 ; col < COLS ; col++) {
          for(IndexType row = 0 ; row < ROWS ; row++) {
              ret[row][col] = (*this)[row][col] - other[row][col];
            }
        }

      return ret;
    }

    Matrix<T, ROWS, COLS, IndexType> operator+(Matrix other) {
      Matrix ret;

      for(IndexType col = 0 ; col < COLS ; col++) {
          for(IndexType row = 0 ; row < ROWS ; row++) {
              ret[row][col] = (*this)[row][col] + other[row][col];
            }
        }

      return ret;
    }

    template<IndexType OTHER_COLS>
    Matrix<T, ROWS, OTHER_COLS, IndexType> operator*(const Matrix<T, COLS, OTHER_COLS, IndexType>& other) const {
      constexpr IndexType OROWS = ROWS;
      constexpr IndexType OCOLS = OTHER_COLS;

      Matrix<T, ROWS, OTHER_COLS, IndexType> out;

      // Do the operation for each case of the "out" matrix
      for(IndexType col = 0 ; col < OCOLS ; col++) {
          for(IndexType row = 0 ; row < OROWS ; row++) {
              for(IndexType k = 0 ; k < COLS ; k++) {
                  out(row,col) += (*this)(row,k) * other(k,col);
                }
            }
        }

      return out;
    }

    Matrix<T, COLS, ROWS, IndexType> transpose(void) {
      Matrix<T, COLS, ROWS, IndexType> ret;

      for(IndexType col = 0 ; col < COLS ; col++) {
          for(IndexType row = 0 ; row < ROWS ; row++) {
              ret[col][row] = (*this)[row][col];
            }
        }

      return ret;
    }

    Matrix<T, ROWS, COLS, IndexType> unit(void) {
      Matrix<T, ROWS, COLS, IndexType> ret;
      T sum = norm(*this);
      if(sum != 0) {
          for(IndexType col = 0 ; col < COLS ; col++) {
              for(IndexType row = 0 ; row < ROWS ; row++) {
                  ret[row][col] = ((*this)[row][col])/sum;
                }
            }
        }
      return ret;
    }
  };


  template<typename T, umax ROWS, umax COLS, typename IndexType = u16>
  T norm(Matrix<T,ROWS, COLS, IndexType> m) {
    T ret = 0.0;
    for(IndexType row = 0 ; row < ROWS ; row++) {
        for(IndexType col = 0 ; col < COLS ; col++) {
            ret += m[row][col]*m[row][col];
          }
      }
    return sqrt((double)ret);
  }

  template<typename T, umax ROWS, umax COLS, typename IndexType = u16, typename Arg1 = void, typename ...Args>
  struct BuildFromRows {
    static void apply(Matrix<T, ROWS, COLS, IndexType>& ret, IndexType row, Arg1 arg1, Args ...args) {
      for(IndexType col = 0 ; col < COLS ; col++) {
          ret[row][col] = arg1[0][col];
        }
      BuildFromRows<T,ROWS,COLS,IndexType,Args...>::apply(ret, row+1, args...);
    }
  };

  template<typename T, umax ROWS, umax COLS, typename IndexType, typename Arg1>
  struct BuildFromRows<T,ROWS,COLS,IndexType,Arg1> {
    static void apply(Matrix<T, ROWS, COLS, IndexType>& ret, IndexType row, Arg1 arg1) {
      for(IndexType col = 0 ; col < COLS ; col++) {
          ret[row][col] = arg1[0][col];
        }
    }
  };

  template<typename T, umax ROWS, umax COLS, typename IndexType = u16, typename ...Args>
  Matrix<T, ROWS, COLS> build_from_rows(Args ...args) {
    Matrix<T, ROWS, COLS, IndexType> ret;
    BuildFromRows<T,ROWS,COLS,IndexType,Args...>::apply(ret, (IndexType)0, args...);
    return ret;
  }

  template<typename T, umax ROWS, umax COLS, typename IndexType = u16>
  constexpr Matrix<T, ROWS, COLS, IndexType> operator*(T val, const Matrix<T, ROWS, COLS, IndexType>& m) {
    return m*val;
  }

}

}

#endif//MATRIX_HPP
