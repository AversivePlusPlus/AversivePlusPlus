/*
    Aversive++
    Copyright (C) 2014 Eirbot

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TASK_HPP
#define TASK_HPP

#include <base/integer.hpp>

namespace SASIAE {

  typedef void(*TaskFunc)(void);

  //! \brief Define the period and priority of a function called by the scheduler
  class Task {
  protected:
    TaskFunc _func;
    
    u32 _period;
    u8 _priority;
    bool _unique;

  public:
    //! \brief Default constructor
    inline Task(void)
      : _func(0), _period(0), _priority(0), _unique(true) {
    }

    //! \brief Task constructor
    inline Task(TaskFunc f)
      : _func(f), _period(0), _priority(0), _unique(true) {
    }

    //! \brief Copy Constructor
    inline Task(const Task& other)
      : _func(other._func), _period(other._period),
        _priority(other._priority), _unique(other._unique) {
    }

    //! \brief Copy operation
    inline Task& operator=(const Task& other) {
      _func = other._func;
      _period = other._period;
      _priority = other._priority;
      _unique = other._unique;
      return *this;
    }

    //! \brief Set the interval of time during two task call (in microseconds)
    inline void setPeriod(u32 period_us) {
      _period = period_us;
    }

    //! \brief Set the priority of the task
    /*!

    If two tasks may be executed at the same time, the first to be
    called is the one with the greatest priority

  */
    inline void setPriority(u8 priority) {
      _priority = priority;
    }

    //! \brief Enable periodicity
    inline void setRepeat(void) {
      _unique = false;
    }

    //! \brief Disable periodicity, the task will be removed once executed
    inline void setUnique(void) {
      _unique = true;
    }

    inline u32 period(void) const {
      return _period;
    }

    inline bool isUnique(void) const {
      return _unique;
    }

    inline bool operator==(const Task& other) const {
      return _func == other._func;
    }

    inline void operator()(void) const {
      if(_func) {
          _func();
        }
    }
  };

}

#endif//TASK_HPP
