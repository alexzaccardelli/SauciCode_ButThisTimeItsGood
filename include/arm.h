#ifndef _ARM_H_
#define _ARM_H_
using namespace vex;

namespace arm {
  extern vex::motor m;

  void reset();
  void stop(vex::brakeType brake = vex::brakeType::coast);

  int move(double height, double max, double kP, double range, double time);

  int op();
}

#endif