#include "vex.h"
using namespace vex;

namespace auton {

  void resetAll() {
    drive::reset();
    intake::reset();
    tilter::reset();
    arm::reset();
  }

  int deployTray() {
    intake::spin(-100);
    tilter::move(730, 100, .8, 5, 100);
    tilter::move(150, 100, .8, 5, 100);
    arm::move(130, 100, .8, 5, 100);
    arm::m.spin(fwd, -100, pct);
    intake::l.stop(coast);
    intake::r.stop(coast);
    arm::reset();
    while(tilter::m.torque() < 2.05)
      tilter::m.spin(fwd, -100, pct);
    tilter::reset();
    return 1;
  }

  int skills() {
    auton::deployTray();
    intake::spin(100);
    drive::forward(100, 30.0, 0.6, 0.2, 17, 200);
    wait(2, vex::seconds);
    drive::reset();
    wait(2, vex::seconds);
    intake::reset();
    drive::turn(33, 75.0, 0.6, 0.2, 17, 200);
    drive::forward(21, 35.0, 0.6, 0.2, 17, 200);

    //stacking
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::move(770, 25, .6, 15, 500);
    wait(2, vex::seconds);
    drive::forward(-10, 30.0, 0.6, 0.2, 17, 200);
    return 1;
  }

  int op() {
    while(1) {
      if(con.ButtonLeft.pressing()) {
        driveTask.suspend();
        armTask.suspend();
        tilterTask.suspend();
        drive::forward(-15, 50.0, 0.8, 0.2, 200, 100);
        wait(1000, msec);
        tilter::move(150, 100, .8, 5, 100);
        arm::move(100, 100, .8, 5, 100);
        arm::m.spin(fwd, -100, pct);
        while(arm::m.torque()) {}
        arm::reset();
        while(tilter::m.torque() < 2.05)
          tilter::m.spin(fwd, -100, pct);
        tilter::reset();
        tilterTask.resume();
        driveTask.resume();
        armTask.resume();
      }
      wait(5, msec);
    }
    return 1;
  }
  int moveTilter() { //for auton task
    if(!tilter::complete) {
      tilter::move(710, 40, 0.6, 15, 500);
      tilter::complete = true;
    }
    return 1;    
  }

  int redSmall() {
    auton::deployTray();
    wait(800, msec);
    intake::spin(100);
    drive::forward(34, 50.0, 0.6, 0.2, 17, 200);
    wait(270, msec);
    intake::reset();
    drive::forward(-18, 100.0, 0.6, 0.2, 17, 100);
    drive::turn(123, 60.0, 0.6, 0.2, 17, 200);
    drive::reset();
    vex::task tiltTask = vex::task(moveTilter);
    drive::forward(14.0, 60, 0.6, 0.2, 17, 200);
    intake::l.stop(coast);
    intake::r.stop(coast);
    wait(2, sec);
    drive::forward(-10, 40.0, 0.6, 0.2, 17, 200);
    return 1;
  }

  int blueSmall() {
    auton::deployTray();
    wait(800, msec);
    intake::spin(100);
    drive::forward(34, 50.0, 0.6, 0.2, 17, 200);
    wait(310, msec);
    intake::reset();
    drive::forward(-18, 100.0, 0.6, 0.2, 17, 100);
    drive::turn(-148, 60.0, 0.6, 0.2, 17, 200);
    drive::reset();
    vex::task tiltTask = vex::task(moveTilter);
    drive::forward(14.0, 60, 0.6, 0.2, 17, 200);
    intake::l.stop(coast);
    intake::r.stop(coast);
    wait(2, sec);
    drive::forward(-10, 40.0, 0.6, 0.2, 17, 200);
    return 1;
  }

  void onePoint(){
    drive::spin(-50);
    wait(500, msec);
    drive::reset();
    drive::spin(50);
    wait(500,msec);
    drive::reset();
    auton::deployTray();
  }
}