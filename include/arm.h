#ifndef _ARM_H_
#define _ARM_H_
using namespace vex;

namespace arm {
  extern vex::motor m;

  void reset();
  void stop(vex::brakeType brake = vex::brakeType::hold);

  int move(double ticks, double max, double kP=.15, double range=10, double time=100, double timeout=5000);

  int op();
}

#endif