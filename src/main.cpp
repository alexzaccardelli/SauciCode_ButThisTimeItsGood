#include "vex.h"
using namespace vex;

competition Competition;
vex::brain cpu;
controller con;
task driveTask, intakeTask, tilterTask, armTask, autonTask, a, deployButtonTask;

void driverSkills() {
  auton::deployTray();
  driveTask = task(drive::op);
  intakeTask = task(intake::op);
  tilterTask = task(tilter::op);
  armTask = task(arm::op);
  a = task(drive::a);
  deployButtonTask = task(auton::deployButton);
  
  while (1) {
    wait(5, msec);
  }
}

void driverMatch() {
  driveTask = task(drive::op);
  intakeTask = task(intake::op);
  tilterTask = task(tilter::op);
  armTask = task(arm::op);
  a = task(drive::a);
  deployButtonTask = task(auton::deployButton);
  
  while (1) {
    wait(5, msec);
  }
}

void usercontrol(void) {
  driverMatch();
}

void pre_auton(void) {
  vexcodeInit();
  auton::resetAll();
}

void autonomous(void) {
  auton::resetAll();
  auton::big(auton::blue);
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
