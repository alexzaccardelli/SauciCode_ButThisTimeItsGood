#include "vex.h"
using namespace vex;


namespace auton {
  bool complete = false;
  void resetAll() {
    drive::reset();
    intake::reset();
    tilter::reset();
    arm::reset();
  }

  int deployTray() {
    arm::move(400, 100, .8, 5, 100);
    arm::m.spin(fwd, -100, pct);
    wait(500, msec);
    while(arm::m.torque() < 2.05) {}
    arm::reset();
    return 1;
  }
  
  void small(int side) {
    timer t;
    t.reset();
    deployTray();
    intake::spin(100);
    drive::forward(32, 40.0, 0.25);
    intake::reset();
    drive::forward(-11.5, 50.0, 0.2);
    if(side == red) drive::turn(200, 60.0);
    else drive::turn(-138, 60.0);
    drive::spin(60);
    wait(900, msec);
    drive::reset();
    intake::reset();
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::move(640, 100, .8, 15, 100);
    tilter::move(950, 40, .8, 15, 100);
    drive::spin(-20);
    wait(1000, msec);
    drive::reset();
    tilter::spin(-100);
    while(tilter::m.torque() < 1.9) {}
    tilter::reset();
    wait(200, msec);
    arm::m.spin(fwd, -100, pct);
    while(arm::m.torque() < 2.05) {}
    arm::reset();
    if(t.time(msec)<15000) complete = true;
    cpu.Screen.clearScreen();
    cpu.Screen.setCursor(5,5);
    cpu.Screen.print("%f", t.time(msec));
  }

  void big(int side) {
    auton::deployTray();
    intake::spin(100);
    drive::forward(21, 40.0);
    if(side == blue) { drive::turn(135, 75.0); }
    else {drive::turn(-90, 75.0);}
    drive::forward(23,40.0);
    intake::reset();
    if(side == blue) { drive::turn(60, 75.0); }
    else {drive::turn(-45, 75.0);}
    drive::forward(11, 60.0);
    drive::reset();
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::move(640, 100, .8, 15, 100);
    tilter::move(950, 40, .8, 15, 100);
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