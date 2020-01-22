#include "vex.h"
using namespace vex;

namespace intake {
  motor l = motor(PORT3, ratio36_1, false);
  motor r = motor(PORT4, ratio36_1, true);

  void reset() {
    l = motor(PORT3, ratio18_1, false);
    r = motor(PORT4, ratio18_1, true);
    l.stop(hold);
    r.stop(hold);
    l.resetRotation();
    r.resetRotation();
  }

  void spin(double vel) {
    l.spin(fwd, vel, pct);
    r.spin(fwd, vel, pct);
  }

  int op() {
    double delay = 200;
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