#ifndef _DRIVE_H_
#define _DRIVE_H_
using namespace vex;

namespace drive {
  extern motor l1, l2, r1, r2;

  void reset();

  void spin(int vel);
  void spinRight(int vel);
  void spinLeft(int vel);

  int turn(double deg, double max, double accel, double kP, double range, double time);
  int forward(double dist, double max, double accel, double kP, double range, double time);

  int op();
}

#endif