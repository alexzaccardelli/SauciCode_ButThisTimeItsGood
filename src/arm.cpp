#include "vex.h"
using namespace vex;

namespace arm {
  motor m = motor(PORT14, ratio36_1, false);

  void reset() {
    m = motor(PORT14, ratio36_1, false);
    m.stop(coast);
    m.resetRotation();
  }
  void stop() {
    m.stop(coast);
  }
  void spin(double vel) {
    m.spin(fwd, vel, pct);
  }

  int blah() {
    tilter::move(150, 100, .8, 5, 100);
    return 1;
  }

  int op() {
    double upVel = 100, downVel = -100;
    while(1) {
      if(con.ButtonX.pressing()) {
        tilterTask.suspend();
        task h = task(blah);
        while(con.ButtonX.pressing()) {
          m.spin(fwd, upVel, pct);
        }
        tilterTask.resume();
      }
      if(con.ButtonB.pressing()) {
        while(con.ButtonB.pressing()) {
          if(m.position(vex::deg) < 100) {
            tilterTask.suspend();
            limit b = limit(cpu.ThreeWirePort.A);
            tilter::spin(-100);
            while(b.value() == 0) {}
            tilter::reset();
            tilterTask.resume();
          }
          m.spin(fwd, downVel, pct);
        }
      }
      m.stop(vex::hold);
      wait(5, msec);
    }
    return 1;
  }

  int move(double height, double max, double kP, double range, double time) {
    reset();
    double ticks = height * 1.7, err, vel; //temporary
    timer t;
    while(1) {
      err = ticks - m.rotation(vex::deg);

      if(err * kP > max) vel = max;
      else if(err * kP < -max) vel = -max;
      else vel = err * kP;
      
      m.spin(fwd, vel, pct);

      if(fabs(err) > range) t.reset();
      if(t.time(msec) > time) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }
}