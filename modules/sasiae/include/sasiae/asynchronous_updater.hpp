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
#ifndef SASIAE_ASYNCHRONOUS_UPDATER_HPP
#define SASIAE_ASYNCHRONOUS_UPDATER_HPP

#include <base/singleton.hpp>
#include <device/asynchronous.hpp>
#include <sasiae/task_manager.hpp>

namespace SASIAE {
  class AsynchronousUpdaterConstructor : public Singleton<AsynchronousUpdaterConstructor> {
    
    typedef void(*Func)(void);

    template<typename Lambda>
    static Func getFuncFromLambda(Lambda lambda) {
      static Lambda l = lambda;
      return [](){
          l();
        };
    }

    template<typename Sync, typename Prev>
    class _AsynchronousUpdaterConstructor : public Prev {
      Sync& _s;
      u32 _t;

    public:
      static constexpr int ID = Prev::ID+1;

      _AsynchronousUpdaterConstructor(Sync& s, u32 t, Prev& p)
        : Prev(p), _s(s), _t(t) {
      }

      template<typename _Sync>
      _AsynchronousUpdaterConstructor<_Sync, _AsynchronousUpdaterConstructor<Sync, Prev>>
      build(_Sync& s, u32 t) {
        return _AsynchronousUpdaterConstructor<_Sync,  _AsynchronousUpdaterConstructor<Sync, Prev>>(s, t, *this);
      }

      template<int ID>
      void _start(void) {
        this->Prev::template _start<ID>();

        SASIAE::Task task(getFuncFromLambda([this]() {
            _s.update();
          }));
        task.setRepeat();
        task.setPeriod(_t);
        SASIAE::TaskManager<ID>::instance().addTask(task);
      }

      void start(void) {
        _start<_AsynchronousUpdaterConstructor<Sync, Prev>::ID>();
      }
    };

  public:
    template<typename Sync>
    _AsynchronousUpdaterConstructor<Sync, AsynchronousUpdaterConstructor>
    build(Sync& s, u32 t) {
      return _AsynchronousUpdaterConstructor<Sync, AsynchronousUpdaterConstructor>(s, t, *this);
    }

    template<int ID>
    void _start(void) {
    }

    void start(void) {
      _start<0>();
    }

    static constexpr int ID = 0;
  };

}

#endif//SASIAE_ASYNCHRONOUS_UPDATER_HPP
