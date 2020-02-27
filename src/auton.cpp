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
    arm::move(150, 100, .8, 5, 100);
    arm::m.spin(fwd, -100, pct);
    while(arm::m.torque() < 2.05) {}
    arm::reset();
    return 1;
  }
  
  void small(int side) {
    timer t;
    t.reset();
    //deployTray();
    intake::spin(100);
    drive::forward(37, 50.0, 0.25);
    intake::reset();
    drive::forward(-25, 50.0, 0.25);
    if(side == red) drive::turn(131, 60.0);
    else drive::turn(-123, 60.0);
    drive::spin(60);
    wait(600, msec);
    drive::reset();
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::move(640, 100, .8, 15, 100);
    tilter::move(850, 40, .8, 15, 100);
    drive::spin(-20);
    wait(1000, msec);
    cpu.Screen.clearScreen();
    cpu.Screen.setCursor(5,5);
    cpu.Screen.print("%f", t.time(msec));
    //while(t.time(msec) < 15000) {}
    drive::reset();
  }

  void big(int side) {
    auton::deployTray();
    intake::spin(100);
    drive::forward(21, 35.0);
    if(side == blue) { drive::turn(93, 75.0); }
    else {drive::turn(-90, 75.0);}
    drive::forward(23,35.0);
    intake::reset();
    if(side == blue) { drive::turn(45, 75.0); }
    else {drive::turn(-30, 75.0);}
    drive::forward(8, 60.0);
    drive::reset();
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::move(600, 90, .8, 15, 100);
    tilter::move(850, 40, .8, 15, 100);
    drive::spin(-20);
    wait(800, msec);
    drive::reset();
  }

  int skills() {
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

  int tower(){
    wait(500, msec);
    arm::move(520,100,0.8,5,100);
    drive::spin(15);
    wait(2, sec);
    drive::reset();
    intake::spin(-25);

    wait(1,sec);
    arm::move(650,100,0.8,5,100);
    intake::reset();

    drive::forward(-10, 30.0);
    arm::m.spin(fwd, -100, pct);
    wait(100, msec);
    return 0; 
  }
}