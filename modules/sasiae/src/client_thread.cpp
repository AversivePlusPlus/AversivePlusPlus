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

#include <sasiae/client_thread.hpp>
#include <sasiae/aversive.hpp>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>

namespace SASIAE {

  static const int DEFAULT_BUFFER_SIZE = 64;

  static const char* const err_detect_device = "Impossible to detect device's name";
  static const char* const err_unknown_device = "Unknown device \"%s\"";
  static const char* const err_unknown_command = "Unknown command %c";
  static const char* const err_invalid_synchro = "Invalid synchro message";

  ClientThread* ClientThread::_inst = NULL;

  ClientThread::ClientThread(void) : QThread() {
    _keep_going = true;
    _inst = this;
    _buffer = new char[DEFAULT_BUFFER_SIZE];
    _length = DEFAULT_BUFFER_SIZE;
    _time = 0;
    _sync_func = NULL;
    _timed_task_done = _synchronized = true;

    // To init cout, etc...
    std::ios_base::Init();
  }

  ClientThread::~ClientThread(void) {
    delete[] _buffer;
    _inst = NULL;
  }

  void ClientThread::expandBuffer(void) {
    char* new_buffer = new char[_length * 2];
    memset(new_buffer, 0, _length * 2);
    memcpy(new_buffer, _buffer, _length);
    _length *= 2;
    delete _buffer;
    _buffer = new_buffer;
  }

  void ClientThread::readLine(void) {
    unsigned int i = 0;
    int c;
    while((c = getchar()) && c != '\n' && c != -1) {
        _buffer[i++] = (char) c;
        if(i >= _length) {
            expandBuffer();
          }
      }
    _buffer[i] = '\0';
    if(c == -1) {
        Aversive::stop();
        quit();
      }
  }

  void ClientThread::quit(void) {
    _keep_going = false;
  }

  void ClientThread::run(void) {
    while(_keep_going) {
        readLine();
        if(!_keep_going) {
            break;
          }

        if(_buffer[0] == '\0') {
          }
        else if(_buffer[0] == 'T') {
            // Synchronization message
            if(_buffer[1] != ' ') {
                sendMessage(ERROR, err_invalid_synchro);
                continue;
              }

            char* ptr = _buffer + 2;
            while(isdigit(*ptr)) {
                ++ptr;
              }

            if(*ptr != ' ') {
                sendMessage(ERROR, err_invalid_synchro);
                continue;
              }

            char* second_field = ++ptr;
            while(isdigit(*ptr)) {
                ++ptr;
              }

            if(*ptr != '\0') {
                sendMessage(ERROR, err_invalid_synchro);
                continue;
              }

            _time = strtoul(_buffer + 2, NULL, 10);
            int it = (int) strtol(second_field, NULL, 10);
            _timed_task_done = false;
            _synchronized = false;

            // We let the robot loop iterating for some time
            _iteration.release(it);

            // We execute the scheduler
            if(_sync_func) {
                _sync_func(_time);
              }
            _timed_task_done = true;

            // Let synchronize
            sync();
          }
        else if(_buffer[0] == 'D') {
            // Device message
            int b = 2, e = 2;
            while(_buffer[e++] != ' ' && _buffer[e] != '\0');
            if(_buffer[e] == '\0') {
                // Impossible to detect device's name
                snprintf(_buffer, (size_t) _length, err_detect_device);
                sendMessage(ERROR, _buffer);
                continue;
              }

            char* name = new char[e - b];
            memcpy(name, _buffer + 2, e - b);
            name[e - b - 1] = '\0';

            _devices_mutex.lock();
            if(!_devices.contains(name)) {
                // Unknown device
                _devices_mutex.unlock();
                snprintf(_buffer, (size_t) _length, err_unknown_device, name);
                sendMessage(ERROR, _buffer);
              }
            else {
                // Device is known, we give its interpreter function the message
                const std::function<void(char*)>& interpreter = _devices[name];
                _devices_mutex.unlock();
                interpreter(_buffer + e);
              }
            delete[] name;
          }
        else if(_buffer[0] == 'B') {
            // Begin match message
          }
        else if(_buffer[0] == 'S') {
            // Stop message
            Aversive::stop();
            // To unblock the main thread if it's waiting
            _iteration.release();
          }
        else {
            // Unknown command
            char cmd = _buffer[0];
            snprintf(_buffer, (size_t) _length, err_unknown_command, cmd);
            sendMessage(ERROR, _buffer);
          }
      }
  }

  void ClientThread::sync(void) {
    _sync_mutex.lock();
    if(!_synchronized && _timed_task_done && _iteration.available() == 0) {
        sendData("T");
        _synchronized = true;
      }
    _sync_mutex.unlock();
  }

  bool ClientThread::sendData(const char* data) {
    _com_mutex.lock();
    std::cout << data << "\n";
    std::cout.flush();
    _com_mutex.unlock();
    return true;
  }

  bool ClientThread::sendDeviceMessage(const Device& dev, const char* msg) {
    return sendData((std::string("D ") + dev.name() + " " + msg).c_str());
  }

  bool ClientThread::sendMessage(MessageLevel lvl, const char* msg) {
    char msg_lvl = 'I';
    switch(lvl) {
      case ERROR:
        msg_lvl = 'E';
        break;
      case INFO:
        msg_lvl = 'I';
        break;
      case DEBUG:
        msg_lvl = 'D';
        break;
      case WARNING:
        msg_lvl = 'W';
        break;
      }

    return sendData((std::string("M ") + msg_lvl + " " + msg).c_str());
  }

  bool ClientThread::registerDevice(const Device& dev, const std::function<void(char*)>& interpreter) {
    QString device = dev.name();
    _devices_mutex.lock();
    if(_devices.contains(device)) {
        // If the device is already registered
        _devices_mutex.unlock();
        return false;
      }
    else {
        _devices.insert(device, interpreter);
        _devices_mutex.unlock();
        return true;
      }
  }

  ClientThread& ClientThread::instance() {
    return *_inst;
  }

  bool ClientThread::setSyncFunction(const std::function<void(int)>& interpreter) {
    _sync_func = interpreter;
    return true;
  }

  unsigned long int ClientThread::time() const {
    return _time;
  }

}
