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

#ifndef DEVICE_HPP
#define DEVICE_HPP

namespace SASIAE {

  //! \class Device
  //! \brief Class representing a generic device.
  class Device {
  private:
    //! \brief The device's name.
    const char* _name;

    //! \brief Private default constructor to prevent its use.
    inline Device(void) {
    }

  protected:
    //! \brief Protected copy constructor to prevent its use by final user.
    //! \param other : the device to copy.
    inline Device(const Device& other)
      : _name(other._name) {
    }

  public:
    //! \brief Construct a device with a given name.
    //! \param name : the device's name.
    //! \note The device's name is used by SASIAE to identify it.
    explicit inline Device(const char* name)
      : _name(name) {
    }

    //! \brief Return the name of the device.
    //! \return The device's name.
    inline const char* name(void) const {
      return _name;
    }
  };

}

#endif//DEVICE_HPP
