#ifndef DEVICE_2WHEEL_LOCATOR_HPP
#define DEVICE_2WHEEL_LOCATOR_HPP

#include <device/input.hpp>
#include <device/asynchronous.hpp>
#include <math.h>

namespace Aversive {
namespace Device {
namespace TwoWheel {

template<typename T, typename CoordType, typename AngleType, typename DistanceSensor, typename AngleSensor> class LocatorX;
template<typename T, typename CoordType, typename AngleType, typename DistanceSensor, typename AngleSensor> class LocatorY;
template<typename T, typename CoordType, typename AngleType, typename DistanceSensor, typename AngleSensor> class LocatorAngle;

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
class Locator : Asynchronous {
public:
  using X = LocatorX<T, CoordType, AngleType, DistanceSensor, AngleSensor>;
  using Y = LocatorY<T, CoordType, AngleType, DistanceSensor, AngleSensor>;
  using Angle = LocatorAngle<T, CoordType, AngleType, DistanceSensor, AngleSensor>;

private:
  DistanceSensor& _dist;
  AngleSensor& _angle;

  AngleType _a_off = 0;

  CoordType _x = 0;
  CoordType _y = 0;

  T _last_dist;

public:
  //! \brief Constructor
  //! \param dist : distance sensor
  //! \param angle : angle sensor
  inline Locator(DistanceSensor& dist, AngleSensor& angle)
    : _dist(dist), _angle(angle),
      _last_dist(dist.get()) {
  }

public:
  //! \brief Get the x coordinate
  inline CoordType getX(void) const {
    return _x;
  }

  //! \brief Get the y coordinate
  inline CoordType getY(void) const {
    return _y;
  }

  //! \brief Get the angle coordinate
  //! \warning the angle may be differents from the angle returned by the odometer.
  inline AngleType getAngle(void) const {
    return fmod(_angle.get() + _a_off, 2.0*3.14159265359);
  }

  //! \brief Set the position of the robot
  inline void setPosition(CoordType x, CoordType y, AngleType angle) {
    _x = x;
    _y = y;
    _a_off = angle - _angle.get();
  }

public:
  //! \brief Update the position considering the angle and distance.
  void update(void) {
    T d = _dist.get();
    T diff_d = d - _last_dist;

    AngleType a = getAngle();

    _x += ((AngleType)diff_d * (AngleType)cos(a));
    _y += ((AngleType)diff_d * (AngleType)sin(a));

    _last_dist = d;
  }

public:
  inline X& x(void) {
    return (X&)*this;
  }

  inline Y& y(void) {
    return (Y&)*this;
  }

  inline Angle& angle(void) {
    return (Angle&)*this;
  }
};

//! \brief A Device that get the X coordinate from the Locator.
template<typename T, typename CoordType, typename AngleType, typename DistanceSensor, typename AngleSensor>
class LocatorX :
    private Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>,
    public Input<CoordType> {
public:
  inline CoordType get(void) {
    return this->getX();
  }
};

//! \brief A Device that get the Y coordinate from the Locator.
template<typename T, typename CoordType, typename AngleType, typename DistanceSensor, typename AngleSensor>
class LocatorY :
    private Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>,
    public Input<CoordType> {
public:
  inline CoordType get(void) {
    return this->getY();
  }
};

//! \brief A Device that get the angle coordinate from the Locator.
template<typename T, typename CoordType, typename AngleType, typename DistanceSensor, typename AngleSensor>
class LocatorAngle :
    private Locator<T, CoordType, AngleType, DistanceSensor, AngleSensor>,
    public Input<AngleType> {
public:
  inline CoordType get(void) {
    return this->getAngle();
  }
};

}
}
}

#endif//DEVICE_2WHEEL_LOCATOR_HPP
