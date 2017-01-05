#include "physicsengine.hpp"
#include <cmath>

PhysicsEngine::PhysicsEngine(Robot& robot)
  : _robot(robot), _time(0.) {
}

double PhysicsEngine::getTime() const
{
  return _time;
}

void PhysicsEngine::update() {
  double delta_t = 0.1;
  double left_move = _robot.left_speed * delta_t;
  double right_move = _robot.right_speed * delta_t;

  double dist_move = left_move + right_move;
  double angle_move = (right_move - left_move) * 2.0 / (_robot.width);

  _time += delta_t;

  _robot.left_encoder += left_move;
  _robot.right_encoder += right_move;

  _robot.angle += angle_move;
  _robot.x += dist_move * cos(_robot.angle);
  _robot.y += dist_move * sin(_robot.angle);
}
