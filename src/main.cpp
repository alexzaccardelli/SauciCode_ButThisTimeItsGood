#include "vex.h"
using namespace vex;

competition Competition;
vex::brain cpu;
controller con;
task driveTask, intakeTask, tilterTask, armTask, autonTask;

int printInfo() {
  while (true) {
    
    printf("L1: %f\n", drive::l1.rotation(vex::deg));
    printf("L2: %f\n", drive::l2.rotation(vex::deg));
    printf("R1: %f\n", drive::r1.rotation(vex::deg));
    printf("R2: %f\n", drive::r2.rotation(vex::deg));
    wait(15, vex::msec);
  }
}
void usercontrol(void) {
  /*timer t;
  auton::resetAll();
  auton::skills();
  printf("%f\n",t.time(msec));*/
  /*drive::reset();
  task printI = task(printInfo);
  wait(1, sec);
  drive::turn(90, 25.0, 0.4, 0.2, 5, 200);
  while (true) {
    wait(5, msec);
  }*/
  //intake::spin(-100);
  //arm::move(170, 100, .8, 5, 100);
  driveTask = task(drive::op);
  intakeTask = task(intake::op);
  tilterTask = task(tilter::op);
  armTask = task(arm::op);
  autonTask = task(auton::op);
  while (1) {
    wait(5, msec);
  }
}

void pre_auton(void) {
  vexcodeInit();
  auton::resetAll();
}

void autonomous(void) {
  auton::resetAll();
  auton::blueSmall();
  auton::resetAll();
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true)
    wait(100, msec);
}
