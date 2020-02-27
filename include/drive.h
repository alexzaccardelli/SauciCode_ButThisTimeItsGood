#ifndef _DRIVE_H_
#define _DRIVE_H_
using namespace vex;

namespace drive {
  extern motor l1, l2, r1, r2;
  extern encoder enc;

  void reset();
  void stop();
  
  void spin(int vel);
  void spinRight(int vel);
  void spinLeft(int vel);
  void untilHitWall(double speed);

  int turn(double deg, double max, double kP=0.2, double range=4, double time=250, double timeout=5000);
  int forward(double dist, double max, double kP=0.2, double range=10, double time=200, double timeout=5000);

  int op();
}

#endif