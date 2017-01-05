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
#ifndef HEAP_HPP
#define HEAP_HPP

#include "config.hpp"

#include <base/integer.hpp>
#include <base/array.hpp>

namespace Aversive {

namespace Container {

  typedef array_t heap_t;

  //! \class Heap heap.hpp <container/heap.hpp>
  //! \brief Class representing a heap that allows to easily extract the maximum element of a given set.
  //! \param _SIZE : the number of elements the heap can handle at any given time.
  //! \param _ElementType : type of the elements within the heap.
  /*!
  The heap allows to easily extract the maximum value of a given set.
  Once the element is inserted, it is compared to others to order it.
  The only element accessible and deletable is the maximum. The
  maximum is the element for which the comparison operator returns
  true foreach comparision with others element in the heap.
*/
  template<heap_t _SIZE = 0, typename _ElementType = u8>
  class Heap {
  public:
    //! \brief Number of elements the heap can handle.
    static const heap_t SIZE = _SIZE;

    //! \brief Element's type.
    typedef _ElementType ElementType;

    //! \brief Element's reference type.
    typedef typename Array<ElementType, SIZE>::ElementRef ElementRef;

    //! \brief Element's constant reference type.
    typedef typename Array<ElementType, SIZE>::ElementConstRef ElementConstRef;

  private:
    //! \brief The array containing the datas.
    Array<ElementType, SIZE> _data;

    //! \brief The current size of the heap.
    heap_t _size;

    //! \brief Private class representing a node in a binary tree.
    /*
    Useful for percolation functions.
  */
    class Node {
    private:
      Heap* _heap;
      heap_t _index;

      //! \brief Default constructor.
      inline Node(void) {
      }

    public:
      //! \brief Constructor.
      //! \param h : a pointer to the heap this node is in.
      //! \param index : the index of this node in the heap data array.
      inline Node(Heap* h, heap_t index)
        : _heap(h), _index(index) {
      }

      //! \brief Copy operator.
      //! \param other : the node to copy.
      //! \return A reference to the node that has been written.
      inline Node& operator=(const Node& other) {
        _heap = other._heap;
        _index = other._index;
        return *this;
      }

      //! \brief Check if the node really represents an element in the heap.
      inline bool isValid(void) const {
        return _index < _heap->_size;
      }

      //! \brief Exchange the elements of two nodes.
      //! \param other : the node that the current node has to switch element with.
      //! \warning Does not change the nodes' position.
      inline void switchElements(Node&& other) {
        ElementType tmp = element();
        element() = other.element();
        other.element() = tmp;
      }

      //! \brief Returns the current node's parent.
      inline Node parent(void) const {
        return Node(_heap, (_index-1)/2);
      }

      //! \brief Returns the current node's first child.
      inline Node firstChild(void) const {
        return Node(_heap, (_index*2)+1);
      }

      //! \brief Returns the current node's second child.
      inline Node secondChild(void) const {
        return Node(_heap, (_index*2)+2);
      }

      //! \brief Check if the node has a parent.
      inline bool hasParent(void) const {
        return _index > 0;
      }

      //! \brief Check if the node has a first child.
      inline bool hasFirstChild(void) const {
        return firstChild().isValid();
      }

      //! \brief Check if the node has a second child.
      inline bool hasSecondChild(void) const {
        return secondChild().isValid();
      }

      //! \brief Returns a reference to the element of the node.
      inline ElementRef element(void) {
        return _heap->_data[_index];
      }

      //! \brief Returns a constant reference to the element of the node.
      inline const ElementRef element(void) const {
        return _heap->_data[_index];
      }
    };

    //! \brief Place correctly an element which has to be moved upward.
    //! \param index : the index in the data array of the element to move upward.
    void percolateUp(heap_t index) {
      Node cur(this, index);
      if(cur.isValid()) {
          while(cur.hasParent() && cur.parent().element() < cur.element()) {
              cur.switchElements(cur.parent());
              cur = cur.parent();
            }
        }
    }

    //! \brief Place correctly an element which has to be moved downward.
    //! \param index : the index in the data array of the element to move downward.
    void percolateDown(heap_t index) {
      Node cur(this, index);
      if(cur.isValid()) {
          // While there is one child greater than current
          while((cur.hasFirstChild() &&
                 cur.element() < cur.firstChild().element()) ||
                (cur.hasSecondChild() &&
                 cur.element() < cur.secondChild().element())) {
              // If there is only one child
              // The first child must be filled first !
              if(!cur.hasFirstChild()) {
                  cur.switchElements(cur.secondChild());
                  cur = cur.secondChild();
                }
              else if(!cur.hasSecondChild()) {
                  cur.switchElements(cur.firstChild());
                  cur = cur.firstChild();
                }
              // If there is two children
              else {
                  // Switch with the max
                  if(cur.firstChild().element() < cur.secondChild().element()) {
                      cur.switchElements(cur.secondChild());
                      cur = cur.secondChild();
                    }
                  else {
                      cur.switchElements(cur.firstChild());
                      cur = cur.firstChild();
                    }
                }
            }
        }
    }

    //! \brief Variadic templated method to insert multiple elements at the construction of the heap.
    //! \param e : the next element to add to the heap.
    //! \param args : the remaining arguments.
    template<typename... Targs>
    inline void set(ElementConstRef e, const Targs&... args) {
      insert(e);
      set(args...);
    }

    //! \brief Termination method to insert multiple elements at the construction of the heap.
    inline void set(void) {
    }

  public:
    //! \brief Default Constructor
    inline Heap(void)
      : _size(0) {
    }

    //! \brief Variadic constructor to insert multiple elements.
    //! \param args : the value list to insert in the heap.
    template<typename... Targs>
    inline Heap(const Targs&... args)
      : Heap() {
      set(args...);
    }

    //! \brief Copy Constructor
    //! \param other : the heap to copy.
    inline Heap(const Heap& other) {
      (*this) = other;
    }

    //! \brief Copy Operator.
    //! \param other : the heap to copy.
    //! \return A reference to the heap that has been written.
    inline Heap& operator=(const Heap& other) {
      _size = other._size;
      _data = other._data;
      return *this;
    }

    //! \brief Insert an element in the Heap
    //! \param e : the element to add within the heap.
    //! \return A boolean telling whether the element has been successfully inserted or not.
    inline bool insert(ElementConstRef e) {
      if(SIZE == _size) {
          return false;
        }
      _data[_size] = e;
      percolateUp(_size++);
      return true;
    }

    //! \brief Delete the maximal element
    //! \return A boolean telling whether an element has been removed from the heap or not.
    inline bool pop(void) {
      if(_size == 0) {
          return false;
        }
      _data[0] = _data[_size - 1];
      _size--;
      percolateDown(0);
      return true;
    }

    //! \brief Completely empty the heap.
    inline void flush(void) {
      _size = 0;
    }

    //! \brief Access to the maximal element.
    //! \return A reference to the maximal element.
    //! \warning If the heap is actually empty, this causes an undefined behavior.
    inline ElementConstRef max(void) const {
      return _data[0];
    }

    //! \brief Test if the heap is empty.
    //! \return A boolean telling whether the heap is empty or not.
    inline bool isEmpty(void) const {
      return _size == 0;
    }

    //! \brief Test if the heap is full.
    //! \return A boolean telling whether the heap is full or not.
    inline bool isFull(void) const {
      return _size == SIZE;
    }

    //! \brief Give the space currently free to use in the heap.
    //! \return The amount of elements that can currently be added to the heap.
    inline heap_t freeSpace(void) const {
      return SIZE - _size;
    }

    //! \brief Give the space currently in use in the heap.
    //! \return The amount of elements currently in the heap.
    inline heap_t usedSpace(void) const {
      return _size;
    }
  };

}

}

#endif//HEAP_HPP
