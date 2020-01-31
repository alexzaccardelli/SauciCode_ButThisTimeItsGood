#include "vex.h"
using namespace vex;

namespace arm {
  motor m = motor(PORT14, ratio36_1, false);

  void reset() {

    //m = motor(PORT14, ratio36_1, false);
    m.stop(coast);

    //m = motor(PORT1, ratio36_1, false);
    //m.stop(hold);

    m.resetRotation();
  }
  void stop(vex::brakeType brake) {
    m.stop(brake);
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
        spin(upVel);
        while(con.ButtonX.pressing()) wait(5,msec);
      }
      if(con.ButtonB.pressing()) {
        spin(downVel);
        while(con.ButtonB.pressing()) wait(5,msec);
      }
      stop();
      wait(5, msec);
    }
    return 1;
  }

  int move(double height, double max, double kP, double range, double time) {
    stop();
    double ticks = height, err, vel;
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
    stop();
    return 1;
  }
}