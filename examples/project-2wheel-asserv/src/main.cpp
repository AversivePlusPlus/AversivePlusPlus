#include "absolute_control_layer/layer.hpp"


bool is_at(RobotControlLayer::Dev& dev, s32 dist, s32 angle) {
  return
      abs(dev.distance.getValue() - dist) < 20 &&
      abs(dev.angle.getValue() - angle) < 20 &&
      true;
}

static constexpr s32 DIST = 5000;

int main(int, char**) {
  AbsoluteControlLayer::Dev dev;

  dev.updater_constructor
      .start();

  dev.robot.setSpeedX(1000);

  while(SASIAE::Aversive::sync()) {
      if(dev.x.getValue() < -DIST && !(dev.y.getValue() > DIST)) {
          dev.robot.setSpeedY(1000);
          dev.robot.setSpeedX(0);
        }
      else if(dev.y.getValue() > DIST && !(dev.x.getValue() > DIST)) {
          dev.robot.setSpeedX(1000);
          dev.robot.setSpeedY(0);
        }
      else if(dev.x.getValue() > DIST && !(dev.y.getValue() < -DIST)) {
          dev.robot.setSpeedY(-1000);
          dev.robot.setSpeedX(0);
        }
      else if(dev.y.getValue() < -DIST && !(dev.x.getValue() < -DIST)) {
          dev.robot.setSpeedX(-1000);
          dev.robot.setSpeedY(0);
        }

    }

  return 0;
}
