#include "vex.h"
using namespace vex;

competition Competition;
vex::brain cpu;
controller con;
task driveTask, intakeTask, tilterTask, armTask, autonTask;

void usercontrol(void) {
  /*
  //----driver skills----
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
    //printf("%f  %f  %f  %f\n", arm::m.rotation(deg), arm::m.torque(), tilter::m.rotation(deg), tilter::m.torque());
    //printf("%f\n", drive::enc.rotation(deg));    
  }
  */
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
  auton::skills();
  auton::resetAll();
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true)
    wait(100, msec);
}
