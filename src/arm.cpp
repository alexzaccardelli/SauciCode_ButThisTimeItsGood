#include "vex.h"
using namespace vex;

namespace arm {
  motor m = motor(PORT13, ratio36_1, false);

  void reset() {
    m.stop(coast);
    m.resetRotation();
  }
  void stop(vex::brakeType brake) {
    m.stop(brake);
  }
  void spin(double vel) {
    m.spin(fwd, vel, pct);
  }

  int op() {
    double upVel = 100, downVel = -100;
    int pressCount = 0;
    limit l = limit(cpu.ThreeWirePort.E);
    while(1) {
      if(con.ButtonX.pressing()) {
        spin(upVel);
        while(con.ButtonX.pressing()) {
          if(l.pressing()) m.resetRotation();
          wait(5,msec);
        }
      }
      if(con.ButtonB.pressing()) {
        spin(downVel);
        while(con.ButtonB.pressing()) {
          if(l.pressing()) m.resetRotation();
          wait(5,msec);
        }
      }
      if(con.ButtonUp.pressing()) {
        if(pressCount == 0) {
          pressCount = 1;
          intakeTask.suspend();
          intake::spin(-50);
          wait(700, msec);
          intake::reset();
          move(520, 50, .8, 5, 100);
          intakeTask.resume();
          while(con.ButtonUp.pressing()) wait(5, msec);
        }
        else {
          driveTask.suspend();
          intakeTask.suspend();
          pressCount = 0;
          arm::spin(-100);
          while(arm::m.torque() < 2.05) {}
          arm::stop();
          intake::spin(-50);
          drive::spin(-80);
          wait(500, msec);
          drive::reset();
          intake::reset();
          driveTask.resume();
          intakeTask.resume();
          arm::spin(-100);
          while(arm::m.torque() < 2.05) {}
          arm::reset();
          while(con.ButtonUp.pressing()) wait(5, msec);
        }
      }
      stop();
      if(l.pressing()) m.resetRotation();
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