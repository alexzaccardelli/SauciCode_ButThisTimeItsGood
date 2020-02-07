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

  int turn(double deg, double max, double accel, double kP, double range, double time);
  int turnEasy(double deg, double max);
  int forward(double dist, double max, double accel, double kP, double range, double time);
  int forwardEasy(double dist, double max, double kP=0.15);

  int op();
}

#endif