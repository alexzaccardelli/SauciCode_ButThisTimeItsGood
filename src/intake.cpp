#include "vex.h"
using namespace vex;

namespace intake {
  motor l = motor(PORT12, ratio36_1, false);
  motor r = motor(PORT21, ratio36_1, true);

  void reset() {
    l.stop(hold);
    r.stop(hold);
    l.resetRotation();
    r.resetRotation();
  }

  void stop(vex::brakeType brake) {
    l.stop(brake);
    r.stop(brake);
  }

  void spin(double vel) {
    l.spin(fwd, vel, pct);
    r.spin(fwd, vel, pct);
  }

  int op() {
    double delay = 100;
    int last = 0;
    while(1) {
      if(con.ButtonL1.pressing()) {
        if(last == 1) {
          last = 0;
          reset();
        }
        else {
          last = 1;
          spin(100);
        }
        while(con.ButtonL1.pressing()) {
          wait(5, msec);
        }
        wait(delay, msec);
      }
      if(con.ButtonL2.pressing()) {
        if(last == 2) {
          last = 0;
          reset();
        }
        else {
          last = 2;
          spin(-100);
        }
        while(con.ButtonL2.pressing()) {
          wait(5, msec);
        }
        wait(delay, msec);
      }
      wait(5, msec);
    }
    return 1;
  }
}