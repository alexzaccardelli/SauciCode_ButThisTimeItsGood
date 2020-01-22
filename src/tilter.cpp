#include "vex.h"
using namespace vex;

namespace tilter {
  motor m = motor(PORT2, ratio36_1, false);
  bool complete = false;

  void reset() {
    m = motor(PORT2, ratio36_1, false);
    m.stop(vex::hold);
    m.resetRotation();
  }

  void stop() {
    m.stop(vex::hold);
  }

  void spin(double vel) {
    m.spin(fwd, vel, pct);
  }

  int op() {
    limit b = limit(cpu.ThreeWirePort.A);
    double upVel = 40, downVel = -100, k = .5;
    while(1) {
      if(con.ButtonR1.pressing()) {
        intakeTask.suspend();
        intake::l.stop(coast);
        intake::r.stop(coast);
        while(con.ButtonR1.pressing() && m.rotation(deg) < 770) {
          if(m.rotation(deg) < 400)
            m.spin(fwd, upVel, pct);
          if(m.rotation(deg) > 810) 
            m.spin(fwd,-upVel, pct);
          else
            m.spin(fwd, upVel*k, pct);
        }
        intake::l.stop(vex::hold);
        intake::r.stop(vex::hold);
        intakeTask.resume();
      }
      if(con.ButtonR2.pressing()) {
        intakeTask.suspend();
        intake::l.stop(coast);
        intake::r.stop(coast);
        while(con.ButtonR2.pressing()) {
          if(b.value() != 0)
            tilter::reset();
          m.spin(fwd, downVel, pct);
        }
        intake::l.stop(vex::hold);
        intake::r.stop(vex::hold);
        intakeTask.resume();
      }
      m.stop(vex::hold);
    }
  }

  int move(double deg, double max, double kP, double range, double time) {
    //reset();
    double ticks = deg, err, vel, lastErr;
    timer t, t1;
    while(1) {
      lastErr = err;
      err = ticks - m.rotation(vex::deg);

      if(err * kP > max) vel = max;
      else if(err * kP < -max) vel = -max;
      else vel = err * kP;

      m.spin(fwd, vel, pct);

      if(fabs(err) > range) t.reset();
      if(t.time(msec) > time) break;
      if(fabs(err - lastErr) > 20) t1.reset();
      if(t1.time() > 5000) break;

      wait(5, msec);
    }
    stop();
    return 1;
  }
}