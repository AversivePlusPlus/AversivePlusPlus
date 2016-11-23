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

#ifndef SASIAE_ENCODER_HPP
#define SASIAE_ENCODER_HPP

#include <sasiae/aversive.hpp>
#include <sasiae/client_thread.hpp>

#include <device/input.hpp>

#include <sstream>

namespace Device {
  namespace SASIAE {

    class Encoder : public ::SASIAE::Device, public ::Device::Input<s32, Encoder> {
    private:
      s32 _val;

    public:
      void get_value_from_msg(s32* dest, const char* msg) {
        long long in;
        sscanf(msg, "%lld", &in);
        *dest = (s32)in;
      }

      Encoder(const char* name)
        : ::SASIAE::Device(name) {

        ::SASIAE::Aversive::init();
        _val = 0;

        ::SASIAE::ClientThread::instance().
            registerDevice(*this,
                           std::function<void(char*)>([&] (char* msg) mutable -> void {
            using namespace std;
            string cmd;
            long long val;
            istringstream iss(msg);

            iss >> cmd;

            if(cmd == "value") {
                iss >> val;
                _val = val;
              }
            else {
                ::SASIAE::ClientThread::instance().sendMessage(
                      ::SASIAE::ClientThread::ERROR,
                      "unable to parse message correctly"
                      );
              }
          }));

        ::SASIAE::ClientThread::instance().
            sendDeviceMessage(*this, "init");
      }

      s32 getValue(void) {
        return _val;
      }

    };
  }
}

#endif//SASIAE_ENCODER_HPP
