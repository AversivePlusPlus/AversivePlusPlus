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

#include <base/array.hpp>

#include <math.h>

namespace Base {

  template<typename T, array_t SIZE>
  class Subarray {
  private:
    Array<T, SIZE>& _array;
    array_t _begin;
    array_t _end;

  public:
    constexpr Subarray(Array<T, SIZE>& array, array_t begin, array_t end)
      : _array(array), _begin(begin), _end(end) {
    }

    T& operator[](array_t i) {
      return _array[_begin+i];
    }
  };


  template<typename T, array_t ROWS, array_t COLS>
  class Matrix {
  private:
    Array<T, ROWS*COLS> _data;

  public:
    constexpr Matrix(void)
      : _data{(T)0} {
    }

    template<typename ...TArgs>
    constexpr Matrix(TArgs ...args)
      : _data{args...} {
    }

    array_t rows(void) {
      return ROWS;
    }

    array_t cols(void) {
      return COLS;
    }

    inline Subarray<T, ROWS*COLS> operator[](array_t row) {
      return Subarray<T, ROWS*COLS>(_data, row*COLS, row*(COLS+1));
    }

    inline T& operator()(array_t row, array_t col) {
      return _data[row*COLS+col];
    }

    inline const T& operator()(array_t row, array_t col) const {
      return _data[row*COLS+col];
    }

    constexpr Matrix<T, ROWS, COLS> operator*(T val) {
      return _data*val;
    }

    constexpr Matrix<T, ROWS, COLS> operator/(T val) {
      return _data/val;
    }

    Matrix<T, ROWS, COLS>& operator-=(Matrix other) {
      for(u32 col = 0 ; col < COLS ; col++) {
          for(u32 row = 0 ; row < ROWS ; row++) {
              (*this)[row][col] = (*this)[row][col] - other[row][col];
            }
        }
      return *this;
    }

    Matrix<T, ROWS, COLS>& operator+=(Matrix other) {
      for(u32 col = 0 ; col < COLS ; col++) {
          for(u32 row = 0 ; row < ROWS ; row++) {
              (*this)[row][col] = (*this)[row][col] + other[row][col];
            }
        }
      return *this;
    }

    Matrix<T, ROWS, COLS> operator-(Matrix other) {
      Matrix ret;

      for(u32 col = 0 ; col < COLS ; col++) {
          for(u32 row = 0 ; row < ROWS ; row++) {
              ret[row][col] = (*this)[row][col] - other[row][col];
            }
        }

      return ret;
    }

    Matrix<T, ROWS, COLS> operator+(Matrix other) {
      Matrix ret;

      for(u32 col = 0 ; col < COLS ; col++) {
          for(u32 row = 0 ; row < ROWS ; row++) {
              ret[row][col] = (*this)[row][col] + other[row][col];
            }
        }

      return ret;
    }

    template<array_t OTHER_COLS>
    Matrix<T, ROWS, OTHER_COLS> operator*(const Matrix<T, COLS, OTHER_COLS>& other) const {
      constexpr array_t OROWS = ROWS;
      constexpr array_t OCOLS = OTHER_COLS;

      Matrix<T, ROWS, OTHER_COLS> out;

      // Do the operation for each case of the "out" matrix
      for(u32 col = 0 ; col < OCOLS ; col++) {
          for(u32 row = 0 ; row < OROWS ; row++) {
              for(u32 k = 0 ; k < COLS ; k++) {
                  out(row,col) += (*this)(row,k) * other(k,col);
                }
            }
        }

      return out;
    }

    Matrix<T, COLS, ROWS> transpose(void) {
      Matrix<T, COLS, ROWS> ret;

      for(u32 col = 0 ; col < COLS ; col++) {
          for(u32 row = 0 ; row < ROWS ; row++) {
              ret[col][row] = (*this)[row][col];
            }
        }

      return ret;
    }

    Matrix<T, ROWS, COLS> unit(void) {
      Matrix<T, ROWS, COLS> ret;
      T sum = norm(*this);
      if(sum != 0) {
          for(u32 col = 0 ; col < COLS ; col++) {
              for(u32 row = 0 ; row < ROWS ; row++) {
                  ret[row][col] = ((*this)[row][col])/sum;
                }
            }
        }
      return ret;
    }
  };


  template<typename T, array_t ROWS, array_t COLS>
  T norm(Matrix<T,ROWS, COLS> m) {
    T ret = 0.0;
    for(array_t row = 0 ; row < ROWS ; row++) {
        for(array_t col = 0 ; col < COLS ; col++) {
            ret += m[row][col]*m[row][col];
          }
      }
    return sqrt((double)ret);
  }

  template<typename T, array_t ROWS, array_t COLS, typename Arg1, typename ...Args>
  struct BuildFromRows {
    static void apply(Matrix<T, ROWS, COLS>& ret, array_t row, Arg1 arg1, Args ...args) {
      for(array_t col = 0 ; col < COLS ; col++) {
          ret[row][col] = arg1[0][col];
        }
      BuildFromRows<T,ROWS,COLS,Args...>::apply(ret, row+1, args...);
    }
  };

  template<typename T, array_t ROWS, array_t COLS, typename Arg1>
  struct BuildFromRows<T,ROWS,COLS,Arg1> {
    static void apply(Matrix<T, ROWS, COLS>& ret, array_t row, Arg1 arg1) {
      for(array_t col = 0 ; col < COLS ; col++) {
          ret[row][col] = arg1[0][col];
        }
    }
  };

  template<typename T, array_t ROWS, array_t COLS, typename ...Args>
  Matrix<T, ROWS, COLS> build_from_rows(Args ...args) {
    Matrix<T, ROWS, COLS> ret;
    BuildFromRows<T,ROWS,COLS,Args...>::apply(ret, (array_t)0, args...);
    return ret;
  }

  template<typename T, array_t ROWS, array_t COLS>
  constexpr Matrix<T, ROWS, COLS> operator*(T val, const Matrix<T, ROWS, COLS>& m) {
    return m*val;
  }

}

#endif//MATRIX_HPP
