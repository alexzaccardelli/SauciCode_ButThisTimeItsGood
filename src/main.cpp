#include "vex.h"
using namespace vex;

competition Competition;
vex::brain cpu;
controller con;
task driveTask, intakeTask, tilterTask, armTask, autonTask;

int printInfo() {
  while (true) {
    
    printf("L1: %f\n", drive::l1.rotation(vex::deg));
    
    //printf("L2: %f\n", drive::l2.rotation(vex::deg));
    //printf("R1: %f\n", drive::r1.rotation(vex::deg));
    //printf("R2: %f\n", drive::r2.rotation(vex::deg));
    wait(15, vex::msec);
  }
}
void usercontrol(void) {
  /*timer clown;
  auton::big(1);
  printf("%f\n", clown.time(msec));*/

  
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
  //autonTask = task(auton::op);
  while (1) {
    wait(5, msec);
    printf("%f  %f  %f  %f\n", arm::m.rotation(deg), arm::m.torque(), tilter::m.rotation(deg), tilter::m.torque());
    //printf("%f\n", drive::enc.rotation(deg));
    
  }
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
