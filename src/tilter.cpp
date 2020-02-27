#include "vex.h"
using namespace vex;

namespace tilter {
  motor m = motor(PORT20, ratio36_1, false);
  bool complete = false;

  void reset() {
    m.stop(vex::hold);
    m.resetRotation();
  }

  void stop(vex::brakeType brake) {
    m.stop(brake);
  }

  void spin(double vel) {
    m.spin(fwd, vel, pct);
  }

  int op() {
    limit b = limit(cpu.ThreeWirePort.H);
    double upVel = 40, downVel = -100, k = .5;
    while(1) {
      if(con.ButtonR1.pressing()) {
        intakeTask.suspend();
        stop(coast);
        while(con.ButtonR1.pressing()) {
          if(m.rotation(deg) < 400)
            m.spin(fwd, upVel, pct);
          else
            m.spin(fwd, upVel*k, pct);
        }
        stop();
        intakeTask.resume();
      }
      if(con.ButtonR2.pressing()) {
        intakeTask.suspend();
        stop(coast);
        while(con.ButtonR2.pressing()) {
          m.spin(fwd, downVel, pct);
        }
        stop();
        intakeTask.resume();
      }
      stop();
    }
  }

  int move(double ticks, double max, double kP, double range, double time, double timeout) {
    stop();
    double err = 0, vel = 0;
    timer t, t1;
    while(1) {
      err = ticks - m.rotation(deg);

      if(err * kP > max) vel = max;
      else if(err * kP < -max) vel = -max;
      else vel = err * kP;

      m.spin(fwd, vel, pct);

      if(fabs(err) > range) t.reset();
      if(t.time(msec) > time) break;
      if(t1.time() > 5000) break;

      wait(5, msec);
    }
    stop();
    return 1;
  }
}