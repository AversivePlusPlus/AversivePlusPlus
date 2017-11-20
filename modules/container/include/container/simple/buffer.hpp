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

#include "config.hpp"

#include <container/container.hpp>
#include <container/flushable.hpp>
#include <container/headed.hpp>
#include <container/queue.hpp>
#include <container/limited.hpp>

namespace Aversive {
namespace Container {
namespace Simple {

//! \class Buffer buffer.hpp <container/buffer.hpp>
//! \brief Buffer implementation which is thread-safe if there are only one provider and one consumer.
//! \warning _SIZE must be a power of 2, it is verified with an assert.
//! \param _SIZE : the number of elements the buffer can handle at any given time.
//! \param _ElementType : type of the buffered elements.
template <typename _Element, umax _SIZE, typename _Index = unsigned int>
class Buffer :
    public Container<Traits::Default<_Element>, _Index>,
    public Flushable<Traits::Default<_Element>, _Index>,
    public Headed<Traits::Default<_Element>, _Index>,
    public Queue<Traits::Default<_Element>, _Index>,
    public Limited<Traits::Default<_Element>, _Index> {
public:
  using Index = _Index;
  using Element = _Element;
  using ElementRef = Element&;
  using ConstElementRef = const Element&;

  //! \brief Number of elements the buffer can handle.
  static const Index SIZE = _SIZE;

private:
  static_assert((SIZE != 0 && (SIZE & (SIZE - 1)) == 0), "Buffer size must be a power of 2.");

private:
  //! \brief The array containing the datas.
  Array<Element, SIZE> _data;

  //! \brief Read counter.
  volatile Index _reads;

  //! \brief Write counter.
  volatile Index _writes;

public:
  //! \brief Default Constructor.
  inline Buffer()
    : _data(), _reads(0), _writes(0) {
  }

  //! \brief Variadic constructor to insert multiple elements.
  //! \param args : the value list to insert in the buffer.
  template<typename... Targs>
  inline Buffer(const Targs&... args)
    : _data(args...), _reads(0), _writes(argc(args...)) {
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
  inline void dequeue(void) {
    while(empty());
    _reads++;
  }

  //! \brief Enqueue an element to the buffer.
  //! \param element : the element to enqueue in the buffer.
  //! \return A boolean telling whether the element has been successfully enqueued or not.
  inline void enqueue(ConstElementRef element) {
    while(full());
    _data[_writes % SIZE] = element;
    _writes++;
  }

  //! \brief Access to the oldest element.
  //! \return A reference to the element at the head of the buffer.
  //! \warning If the buffer is actually empty, this causes an undefined behavior.
  inline ElementRef head(void) {
    while(empty());
    return _data[_reads % SIZE];
  }

  //! \brief Access to the oldest element.
  //! \return A reference to the element at the head of the buffer.
  //! \warning If the buffer is actually empty, this causes an undefined behavior.
  inline ConstElementRef head(void) const {
    while(empty());
    return _data[_reads % SIZE];
  }

  //! \brief Test if the buffer is empty.
  //! \return A boolean telling whether the buffer is empty or not.
  inline bool empty(void) const {
    return _reads == _writes;
  }

  //! \brief Test if the buffer is full.
  //! \return A boolean telling whether the buffer is full or not.
  inline bool full(void) const {
    return size() >= limit();
  }

  //! \brief Give the space currently in use in the buffer.
  //! \return The amount of elements currently buffered.
  inline Index size(void) const {
    return (_writes - _reads);
  }

  //! \brief Give the maximum space usable in the buffer.
  //! \return The amount of elements that can be contained in buffer.
  inline Index limit(void) const {
    return SIZE;
  }
};

}
}
}

#endif//BUFFER_HPP
