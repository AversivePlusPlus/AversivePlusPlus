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

#ifndef SASIAE_UART_STREAM_HPP
#define SASIAE_UART_STREAM_HPP

#include <sasiae/aversive.hpp>
#include <sasiae/client_thread.hpp>

#include <stream/io_stream.hpp>
#include <stream/formatted_stream.hpp>

#include <sstream>
#include <QtCore/QList>

namespace Stream {
  namespace SASIAE {

    class Stream :
        public ::SASIAE::Device,
        //public ::Stream::InputStream<Stream>,
        public ::Stream::OutputStream<Stream>
    {
    private:
      QList<char> _buffer;

    public:

      Stream(const char* name) : ::SASIAE::Device(name) {
        ::SASIAE::Aversive::init();

        ::SASIAE::ClientThread::instance().
            registerDevice(*this,
                           std::function<void(char*)>([&] (char* msg) mutable -> void {
            using namespace std;
            string cmd;
            int val;
            istringstream iss(msg);

            iss >> cmd;

            if(cmd == "value") {
                iss >> val;
                //_buffer.append((char) val);
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

      /*
      char getChar(void) {
        QList<char> &buffer = _buffer;
        if(buffer.size()) {
            return buffer.takeFirst();
          }
        return 0;
      }
      */

      void putChar(char val) {
        std::ostringstream oss;
        oss << "value " << (unsigned int)val;

        ::SASIAE::ClientThread::instance().
            sendDeviceMessage(*this,
                              oss.str().c_str());
      }
    };

  }
}

#endif//SASIAE_UART_STREAM_HPP
