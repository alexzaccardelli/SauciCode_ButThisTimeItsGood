#ifndef _INTAKE_H_
#define _INTAKE_H_
using namespace vex;

namespace intake {
  extern motor l, r;

  void reset();
  void stop(vex::brakeType brake = vex::brakeType::hold);
  
  void spin(double vel);

  int op();
}

#endif