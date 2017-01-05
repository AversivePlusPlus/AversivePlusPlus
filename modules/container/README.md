# Container

This library is a part of the [Aversive++ project](https://github.com/AversivePlusPlus/AversivePlusPlus).

## Description

This library implements most common containers you can find in computer science (list, queue, stack, heap, buffer, ...).
The particularity of these containers (compared to C++'s stl) is that they don't use dynamic allocations.
Thereby, the user must define the maximum of entities that can be manipulated by an algorithm.

## Installation

This library has one dependency : [Base](https://github.com/AversivePlusPlus/base)

### Simple

Clone the git repositories :
```bash
git clone https://github.com/AversivePlusPlus/base.git
git clone https://github.com/AversivePlusPlus/container.git
```

Since this library is header only, you can just add the compiler `-I` option to your project :
```bash
g++ -I/path/to/base/include -I/path/to/container/include myfile.cpp
```

### Arduino (from sources)

Please note that this package use C++11, which is not enabled by default in most versions of the Arduino IDE. You may need to enable C++11 (google is your friend ;) ), or update the IDE.

This library has dependencies, you need to add all dependencies to the Arduino IDE.

Clone the git repository :
```bash
git clone https://github.com/AversivePlusPlus/container.git
cd container
make arduino_package
```

You will find the file `container.zip` in `build` directory. 
You can add it to your Arduino IDE (sketch > include library > add .zip library)

## Use

### Queue and Buffer

```c++
#include <container/queue.hpp>
#include <container/buffer.hpp>
```

These are 2 FIFO containers. The diference of Buffer over Queue is that a buffer's size must be a power of 2, and Buffer is more optimized than Queue.

```c++
Buffer<64, char> buff;
buff.enqueue('a');
buff.enqueue('b');
char c1 = buff.head(); // c1 = 'a'
char c2 = buff.head(); // c2 = 'a'
buff.dequeue();
char c3 = buff.head(); // c3 = 'b'
```

### Stack

```c++
#include <container/stack.hpp>
```

This is a LIFO container.

```c++
Stack<64, char> stk;
stk.push('a');
stk.push('b');
char c1 = stk.head(); // c1 = 'a'
stk.pop();
char c2 = stk.head(); // c2 = 'b'
```

### Heap

```c++
#include <container/heap.hpp>
```

A Heap is a container where inserting or removing an element is done with a complexity of `log(n)`, and accessing to the max element is done instantly.

```c++
Heap<64, u32> heap;
heap.insert(1);
heap.insert(3);
heap.insert(2);
u32 val1 = heap.max(); // val1 = 3
heap.pop();
u32 val2 = heap/max(); // val2 = 2
```

### List

```c++
#include <container/list.hpp>
```

A List is a container where you can insert or remove any element at any position.

```c++
List<64, u32> list(1,2,3); // [1,2,3]
u32 val = list[0];         // val = 1
list.append(4);            // [1,2,3,4]
list.prepend(0);           // [0,1,2,3,4]
list.insertAt(1, 4);       // [0,4,1,2,3,4]
list.removeAt(0);          // [4,1,2,3,4]
list.remove(4);            // [1,2,3]
```

