#ifndef ROBOT_HPP
#define ROBOT_HPP

struct Robot {
  inline Robot()
    : width(0.), x(0.), y(0.), angle(0.),
      left_speed(0.), right_speed(0.),
      left_encoder(0.), right_encoder(0.)
  {
  }

  double width;

  double x;
  double y;
  double angle;
  
  double left_speed;
  double right_speed;

  double left_encoder;
  double right_encoder;
};

#endif//ROBOT_HPP
