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
#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <base/array.hpp>
#include <base/integer.hpp>

namespace Container {

  typedef u16 buffer_t;

  //! \class Buffer buffer.hpp <container/buffer.hpp>
  //! \brief Buffer implementation which is thread-safe if there are only one provider and one consumer.
  //! \warning _SIZE must be a power of 2, it is verified with an assert.
  //! \param _SIZE : the number of elements the buffer can handle at any given time.
  //! \param _ElementType : type of the buffered elements.
  template <buffer_t _SIZE = 0, typename _ElementType = u8>
  class Buffer {
  public:
    //! \brief Maximum number of elements a buffer can handle.
    static const buffer_t MAX_SIZE = 1 << 15;

    //! \brief Number of elements the buffer can handle.
    static const buffer_t SIZE = _SIZE;

    //! \brief Element's type.
    typedef _ElementType ElementType;

    //! \brief Element's reference type.
    typedef typename Array<ElementType, SIZE>::ElementRef ElementRef;

    //! \brief Element's constant reference type.
    typedef typename Array<ElementType, SIZE>::ElementConstRef ElementConstRef;

  private:
    //! \brief The array containing the datas.
    Array<ElementType, SIZE> _data;

    //! \brief Read counter.
    volatile buffer_t _reads;

    //! \brief Write counter.
    volatile buffer_t _writes;

    //! \brief Variadic templated method to insert multiple elements at the construction of the buffer.
    //! \param e : the next element to add to the buffer.
    //! \param args : the remaining arguments.
    template<typename... Targs>
    inline void set(ElementConstRef e, const Targs&... args) {
      enqueue(e);
      set(args...);
    }

    //! \brief Termination method to insert multiple elements at the construction of the buffer.
    inline void set(void) {
    }

  public:
    //! \brief Default Constructor.
    inline Buffer()
      : _data(), _reads(0), _writes(0) {
      static_assert((SIZE != 0 && (SIZE & (SIZE - 1)) == 0), "Buffer size must be a power of 2.");
    }

    //! \brief Variadic constructor to insert multiple elements.
    //! \param args : the value list to insert in the buffer.
    template<typename... Targs>
    inline Buffer(const Targs&... args)
      : Buffer() {
      set(args...);
    }

    //! \brief Copy Constructor.
    //! \param buff : the buffer to copy.
    inline Buffer(const Buffer& buff)
      : _data(buff._data), _reads(buff._reads), _writes(buff._writes) {
    }

    //! \brief Copy Operator.
    //! \param buff : the buffer to copy.
    //! \return A reference to the buffer that has been written.
    inline Buffer& operator=(const Buffer& buff){
      _data = buff._data;
      _reads = buff._reads;
      _writes = buff._writes;
    }

    //! \brief Completely empty the buffer.
    inline void flush(void) {
      _reads = _writes;
    }

    //! \brief Delete the oldest element.
    //! \return A boolean telling whether an element has been successfully dequeued or not.
    inline bool dequeue(void) {
      if(isEmpty()) {
          return false;
        }
      _reads++;
      return true;
    }

    //! \brief Enqueue an element to the buffer.
    //! \param element : the element to enqueue in the buffer.
    //! \return A boolean telling whether the element has been successfully enqueued or not.
    inline bool enqueue(ElementConstRef element) {
      if(isFull()) {
          return false;
        }
      _data[_writes % SIZE] = element;
      _writes++;
      return true;
    }

    //! \brief Access to the oldest element.
    //! \return A reference to the element at the head of the buffer.
    //! \warning If the buffer is actually empty, this causes an undefined behavior.
    inline ElementConstRef head(void) const {
      return _data[_reads % SIZE];
    }

    //! \brief Test if the buffer is empty.
    //! \return A boolean telling whether the buffer is empty or not.
    inline bool isEmpty(void) const {
      return _reads == _writes;
    }

    //! \brief Test if the buffer is full.
    //! \return A boolean telling whether the buffer is full or not.
    inline bool isFull(void) const {
      return usedSpace() >= SIZE;
    }

    //! \brief Give the space currently in use in the buffer.
    //! \return The amount of elements currently buffered.
    inline buffer_t usedSpace(void) const {
      return (_writes - _reads);
    }

    //! \brief Give the space currently free to use in the buffer.
    //! \return The amount of elements that can currently be buffered.
    inline buffer_t freeSpace(void) const {
      return SIZE - usedSpace();
    }
  };

}

#endif//BUFFER_HPP
