#ifndef _TILTER_H_
#define _TILTER_H_
using namespace vex;

namespace tilter {
  extern motor m;
  extern bool complete;

  void reset();
  void stop(vex::brakeType brake = vex::brakeType::hold);
  void spin(double vel);

  int move(double ticks, double max, double kP=.15, double range=10, double time=100, double timeout=5000);

  int op();
}

#endif