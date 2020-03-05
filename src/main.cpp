#include "vex.h"
using namespace vex;

competition Competition;
vex::brain cpu;
controller con;
task driveTask, intakeTask, tilterTask, armTask, autonTask, a, stopperTask;

void driverSkills() {
  //drive::l1.vex::spin(50);
  /*timer clown;
  auton::deployTray();
  intake::spin(100);
  drive::forward(70, 30.0, 0.6, 0.2, 17, 200);
  wait(1, sec); 
  drive::forwardEasy(15, 20.0);
  drive::forwardEasy(8, 20.0);

  driveTask = task(drive::op);
  intakeTask = task(intake::op);
  tilterTask = task(tilter::op);
  armTask = task(arm::op);
  while (1) {
    wait(5, msec);
    if (clown.time(msec) > 60000) { break; }
  }
  driveTask.stop();
  intakeTask.stop();
  tilterTask.stop();
  armTask.stop();
  auton::resetAll();*/
}

void driverMatch() {
  /*if(!auton::complete){
    while(arm::m.torque() < 2.05) {}
    arm::reset();
  }*/
  /*tilter::spin(-100);
  while(tilter::m.torque() < 1.9) {}
  tilter::reset();
  arm::move(150, 100, .8, 5, 100);
  arm::m.spin(fwd, -100, pct);
  while(arm::m.torque() < 2.05) {}
  arm::reset();
  auton::resetAll();*/

  driveTask = task(drive::op);
  intakeTask = task(intake::op);
  tilterTask = task(tilter::op);
  armTask = task(arm::op);
  a = task(drive::a);
  stopperTask = task(arm::stopper);
  
  while (1) {
    printf("%f\n", arm::m.torque());
    wait(5, msec);
  }
}

void usercontrol(void) {
  driverMatch();
  timer clown;
  auton::skills();
  printf("%f\n", clown.time(msec));
}

void pre_auton(void) {
  vexcodeInit();
  auton::resetAll();
}

void autonomous(void) {
  auton::resetAll();
  wait(200, msec);
  auton::resetAll();
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true)
    wait(100, msec);
}
