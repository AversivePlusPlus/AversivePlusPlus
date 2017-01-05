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
#ifndef LIST_HPP
#define LIST_HPP

#include "config.hpp"

#include <base/integer.hpp>
#include <base/array.hpp>

namespace Aversive {

namespace Container {

  typedef array_t list_t;

  //! \class List list.hpp <container/list.hpp>
  //! \brief Class reprensenting a list of elements.
  //! \param _SIZE : the number of elements the list can handle at any given time.
  //! \param _ElementType : type of the elements within the list.
  template<list_t _SIZE = 0, typename _ElementType = u8>
  class List {
  public:
    //! \brief Number of elements the list can handle.
    static const list_t SIZE = _SIZE;

    //! \brief Element's type.
    typedef _ElementType ElementType;

    //! \brief Element's reference type.
    typedef typename Array<ElementType, SIZE>::ElementRef ElementRef;

    //! \brief Element's constant reference type.
    typedef typename Array<ElementType, SIZE>::ElementConstRef ElementConstRef;

  private:
    //! \brief The array containing the datas.
    Array<ElementType, SIZE> _data;

    //! \brief The current size of the list.
    list_t _size;

    //! \brief Variadic templated method to insert multiple elements at the construction of the list.
    //! \param e : the next element to add to the list.
    //! \param args : the remaining arguments.
    template<typename... Targs>
    inline void set(ElementConstRef e, const Targs&... args) {
      append(e);
      set(args...);
    }

    //! \brief Termination method to insert multiple elements at the construction of the list.
    inline void set(void) {
    }

  public:
    //! \brief Default Constructor.
    inline List(void)
      : _data(), _size(0) {
    }

    //! \brief Variadic constructor to insert multiple elements.
    //! \param args : the value list to insert in the list.
    template<typename... Targs>
    inline List(const Targs&... args)
      : List() {
      set(args...);
    }

    //! \brief Copy constructor.
    //! \param other : the list to copy.
    inline List(const List& other) {
      *this = other;
    }

    //! \brief Copy operator.
    //! \param other : the list to copy.
    //! \return A reference to the list that has been written.
    inline List& operator=(const List& other) {
      _size = other._size;
      _data = other._data;
      return *this;
    }

    //! \brief Append an element at the end of the list.
    //! \param e : the element to append to the list.
    //! \return A boolean telling whether the insertion has been done successfully or not.
    inline bool append(ElementConstRef e) {
      if(_size == SIZE) { // The list is full.
          return false;
        }

      _data[_size++] = e;
      return true;
    }

    //! \brief Prepend an element at the beginning of the list.
    //! \param e : the element to prepend to the list.
    //! \return A boolean telling whether the insertion has been done successfully or not.
    inline bool prepend(ElementConstRef e) {
      return insertAt(0, e);
    }

    //! \brief Insert an element at a given index.
    //! \param index : the index to add the element at.
    //! \param e : the element to add to the list.
    //! \return A boolean telling whether the insertion has been done successfully or not.
    bool insertAt(list_t index, ElementConstRef e) {
      if(_size == SIZE) { // The list is full.
          return false;
        }

      if(index >= _size) { // The given index is out of the current index range.
          return append(e); // So we add the element at the end of the list.
        }

      // We first shift right the elements to make a free spot at the given index.
      for(list_t i = _size; index < i; i--) {
          _data[i] = _data[i - 1];
        }
      _data[index] = e;
      _size++;
      return true;
    }

    //! \brief Remove the element at a given index.
    //! \param index : the index of the element to remove.
    //! \return A boolean telling whether the removal has been done successfully or not.
    bool removeAt(list_t index) {
      if(index >= _size) { // Index out of range.
          return false;
        }

      for(list_t i = index + 1; i < _size; i++) {
          _data[i - 1] = _data[i];
        }
      _size--;
      return true;
    }

    //! \brief Remove all the elements equal to a given one.
    //! \param e : the element to remove from the list.
    //! \return True if at least one element has been removed, false otherwise.
    bool remove(ElementConstRef e) {
      bool res = false;
      for(list_t i = 0; i < _size; i++) {
          if(_data[i] == e) {
              removeAt(i--);
              res = true;
            }
        }
      return res;
    }

    //! \brief Completely empty the list.
    inline void flush(void) {
      _size = 0;
    }

    //! \brief Test if the list is empty.
    //! \return A boolean telling whether the list is empty or not.
    inline bool isEmpty(void) const {
      return _size == 0;
    }

    //! \brief Test if the list is full.
    //! \return A boolean telling whether the list is full or not.
    inline bool isFull(void) const {
      return _size == SIZE;
    }

    //! \brief Give the space currently in use in the list.
    //! \return The amount of elements currently listed.
    inline list_t usedSpace(void) const {
      return _size;
    }

    //! \brief Give the space currently free to use in the list.
    //! \return The amount of elements that can currently be listed.
    inline list_t freeSpace(void) const {
      return SIZE - usedSpace();
    }

    //! \brief Test if the list contains a specified element.
    //! \param e : the element to search in the list.
    //! \return A boolean telling whether the element is contained in the list or not.
    inline bool contains(ElementConstRef e) const {
      for(list_t i = 0; i < _size; i++) {
          if(_data[i] == e) {
              return true;
            }
        }
      return false;
    }

    //! \brief Give the index in the list of a specified element.
    //! \param e : the element to search its index in the list.
    //! \return : The index of the element if it is in the list, the current size of the list otherwise.
    inline list_t indexOf(ElementConstRef e) const {
      for(list_t i = 0; i < _size; i++) {
          if(_data[i] == e) {
              return i;
            }
        }
      return _size;
    }

    //! \brief Get a reference to the element at a given index.
    //! \param index : the index of the element to return.
    //! \return The reference to the asked element.
    //! \warning If the index is out of range, this causes an undefined behavior.
    inline ElementRef get(list_t index) {
      return _data[index];
    }

    //! \brief Get a constant reference to the element at a given index.
    //! \param index : the index of the element to return.
    //! \return The constant reference to the asked element.
    //! \warning If the index is out of range, this causes an undefined behavior.
    inline ElementConstRef get(list_t index) const {
      return _data[index];
    }

    //! \brief Call a function on each element of the list.
    //! \param func : the function to apply on each element of the list.
    template<typename Callable>
    inline void doForeach(Callable func) {
      for(list_t i = 0 ; i < _size ; i++) {
          func(_data[i]);
        }
    }

    //! \brief Call a function on each element of the list (const version)
    //! \param func : the function to apply on each element of the list.
    template<typename Callable>
    inline void doForeach(Callable func) const {
      for(list_t i = 0 ; i < _size ; i++) {
          func(_data[i]);
        }
    }
  };

}

}

#endif//LIST_HPP
