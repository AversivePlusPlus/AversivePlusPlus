#ifndef DEVICE_2WHEEL_LOCATOR_HPP
#define DEVICE_2WHEEL_LOCATOR_HPP

#include <device/input.hpp>
#include <device/asynchronous.hpp>
#include <math.h>

namespace Device {
  namespace TwoWheel {

    //! \brief A device that compute a position and angle coordinate from an odometer sensor
    //! \param T : The type of data received from odometer
    //! \param CoordType : The type of position coordinates
    //! \param AngleType : The type of angle values
    //! \warning This device is Asynchronous, you will need to call the update() method to compute the position.
    /*!
      This device does not inherit directly from Input class, since it returns complex data : the pair (x, y, angle).
      So, it defines 3 subclasses that inherit from Input : Locator::CoordX, Locator::CoordX and Locator::Angle.
     */
    template<typename T, typename CoordType, typename AngleType, typename DistanceSensor, typename AngleSensor>
    class Locator : Asynchronous<Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>> {
    private:
      Input<T, DistanceSensor>& _dist;
      Input<T, AngleSensor>& _angle;

      AngleType _a_off = 0;

      CoordType _x = 0;
      CoordType _y = 0;

      T _last_dist;

    public:
      //! \brief Constructor
      //! \param dist : distance sensor
      //! \param angle : angle sensor
      inline Locator(Input<T, DistanceSensor>& dist, Input<T, AngleSensor>& angle)
        : _dist(dist), _angle(angle),
          _last_dist(dist.getValue()) {
      }

      //! \brief Get the x coordinate
      inline CoordType x(void) const {
        return _x;
      }

      //! \brief Get the y coordinate
      inline CoordType y(void) const {
        return _y;
      }

      //! \brief Get the angle coordinate
      //! \warning the angle may be differents from the angle returned by the odometer.
      inline AngleType angle(void) const {
        return fmod(_angle.getValue() + _a_off, 2.0*3.14159265359);
      }

      //! \brief Set the position of the robot
      inline void setPosition(CoordType x, CoordType y, AngleType angle) {
        _x = x;
        _y = y;
        _a_off = angle - _angle.getValue();
      }

      //! \brief Update the position considering the angle and distance.
      void update(void) {
        T d = _dist.getValue();
        T diff_d = d - _last_dist;

        AngleType a = angle();

        _x += ((AngleType)diff_d * (AngleType)cos(a));
        _y += ((AngleType)diff_d * (AngleType)sin(a));

        _last_dist = d;
      }

    public:
      //! \brief A Device that get the X coordinate from the Locator.
      class CoordX : public Input<CoordType, CoordX> {
        Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>& _loc;
      public:
        inline CoordX(Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>& loc)
          : _loc(loc) {
        }

        inline CoordType getValue(void) {
          return _loc.x();
        }
      };

      //! \brief A Device that get the Y coordinate from the Locator.
      class CoordY : public Input<CoordType, CoordY> {
        Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>& _loc;
      public:
        inline CoordY(Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>& loc)
          : _loc(loc) {
        }

        inline CoordType getValue(void) {
          return _loc.y();
        }
      };

      //! \brief A Device that get the angle coordinate from the Locator.
      class Angle : public Input<AngleType, Angle> {
        Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>& _loc;
      public:
        inline Angle(Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>& loc)
          : _loc(loc) {
        }

        inline CoordType getValue(void) {
          return _loc.angle();
        }
      };

    };

  }
}

#endif//DEVICE_2WHEEL_LOCATOR_HPP
