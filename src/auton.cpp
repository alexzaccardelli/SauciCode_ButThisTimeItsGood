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
    tilter::move(300, 100, .8, 15, 100);
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::m.spin(fwd, -100, pct);
    while(tilter::m.torque() < 1.9) {}
    tilter::reset();
    arm::move(100, 100, .8, 5, 100);
    arm::m.spin(fwd, -100, pct);
    while(arm::m.torque() < 2.05) {}
    arm::reset();

    /*arm::m.spin(fwd, -100, pct);
    intake::l.stop(coast);
    intake::r.stop(coast);
    arm::reset();
    while(tilter::m.torque() < 2.05)
      tilter::m.spin(fwd, -100, pct);
    tilter::reset();*/
    return 1;
  }
  int a() {
    wait(1,sec);
    
    return 1;
  }
  
  void small() {
    timer t;
  t.reset();
  
    deployTray();
    intake::spin(100);
    drive::forward(40, 35.0, 0.6, 0.2, 17, 100);
    intake::reset();
    drive::forward(-27, 100.0, 0.6, 0.2, 17, 100);
    wait(100, msec);
    drive::turn(-128, 75.0, 0.6, 0.2, 20, 100);
    drive::forward(14, 40.0, 0.6, 0.2, 17, 100);
    tilter::move(600, 100, .8, 15, 100);
    tilter::move(850, 40, .8, 15, 100);
    
    drive::forward(-5, 20.0, 0.6, 0.2, 17, 100);
    cpu.Screen.clearScreen();
  cpu.Screen.setCursor(5,5);
  cpu.Screen.print("%f", t.time(msec));
    
  }

  int skills() {
    //auton::deployTray();
    intake::spin(100);
    drive::forward(60, 30.0, 0.6, 0.2, 17, 200);
    wait(1, sec);
    drive::forward(40, 30.0, 0.6, 0.2, 17, 200);
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
    drive::forward(-40, 30.0, 0.6, 0.2, 17, 200);
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