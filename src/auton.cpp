
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
  
  void small(int side) {
    timer t;
    t.reset();
  
    deployTray();
    intake::spin(100);
    drive::forwardEasy(43.5, 30.0);
    intake::reset();
    drive::forwardEasy(-28, 80.0);
    if(side == red) drive::turnEasy(132, 75.0);
    else drive::turnEasy(-123, 75.0);
    drive::forwardEasy(13.5, 40.0);
    tilter::move(600, 100, .8, 15, 100);
    tilter::move(850, 40, .8, 15, 100);
    drive::spin(-20);
    cpu.Screen.clearScreen();
    cpu.Screen.setCursor(5,5);
    cpu.Screen.print("%f", t.time(msec));
    while(t.time(msec) < 15000) {}
    drive::reset();

    
  }

  int skills() {
    drive::spin(-30);
    //auton::deployTray();

    //intake 10 cubes
    drive::spin(-30);
    wait(750,msec);
    drive::reset();
    intake::spin(100);
    drive::forward(70, 30.0, 0.6, 0.2, 17, 200);
    wait(1, sec); 
    //drive::turn(-10, 65.0, 0.6, 0.2, 17, 200);
    drive::forwardEasy(15, 20.0);
    drive::forwardEasy(15, 20.0);
    drive::forwardEasy(15, 20.0);
    drive::forwardEasy(10, 20.0);

    drive::reset();
    wait(2, vex::seconds);
    intake::reset();

    
    //turn towards goal zone
    drive::turnEasy(-43,25);
    drive::forward(19, 35.0, 0.6, 0.2, 17, 200);

    //stacking
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::move(850, 15, .6, 15, 500);
    wait(2, vex::seconds); 
    
    //drive away from goal zone 
    drive::forward(-14, 30.0, 0.6, 0.2, 17, 200);

    /*
    //turn to align with wall, hit wall
    drive::turn(-135, 65.0, 0.6, 0.2, 17, 200);
    drive::untilHitWall(-50);
    
    //drive forward
    drive::forward(30, 35.0, 0.6, 0.2, 17, 200);

    //turn towards tower 
    drive::turn(-90, 25.0, 0.6, 0.2, 2, 300);
    drive::untilHitWall(-50);

    //move tilter back
    tilter::m.spin(fwd, -100, pct);
    while(tilter::m.torque() < 1.9) {}
    tilter::reset();

    intake::spin(100);

    //drive towards the tower 
    //drive::forward(46, 35.0, 0.6, 0.2, 17, 200);
    //drive::forward(10, 15.0, 0.6, 0.2, 17, 200);
    drive::forward(56, 30.0, 0.6, 0.2, 17, 200);
    wait(2, sec);
    drive::forward(-4, 15.0, 0.6, 0.2, 17, 200);

    //intake cube and place in first tower 
    intake::spin(100);
    wait(500, msec);
    intake::reset();
    wait(500,msec);
    intake::spin(-50);
    wait(700, msec);
    intake::reset();
    tower();

    //drive back until it hits the wall
    
    drive::forward(-30, 50.0, 0.6, 0.2, 17, 200);
    drive::untilHitWall(-50);

    //drive forward and turn toward second tower
    drive::forward(23, 50.0, 0.6, 0.2, 17, 200);
    drive::turn(95, 50.0, 0.6, 0.2, 10, 200);

    //move backward to align with the wall
    drive::forward(-24, 50.0, 0.6, 0.2, 17, 200);
    drive::untilHitWall(-50);

    //move tray back
    tilter::m.spin(fwd, -100, pct);
    while(tilter::m.torque() < 1.9) {}
    tilter::reset();

    //drive toward second tower
    intake::spin(100);
    drive::forward(58, 35.0, 0.6, 0.2, 17, 200);

    //back up from the second tower
    drive::forward(-20, 25.0, 0.6, 0.2, 17, 200);

    //turn left and back up to align with the base wall
    drive::turn(-90, 50.0, 0.6, 0.2, 10, 200);
    drive::untilHitWall(-50);

    //move forward until parallel with third tower
    drive::forward(34, 25.0, 0.6, 0.2, 17, 200);

    //turn toward third tower
    drive::turn(-90, 50.0, 0.6, 0.2, 10, 200);

    //hit tower
    drive::forward(28, 25.0, 0.6, 0.2, 17, 200);
    drive::untilHitWall(50);

    //move back to put cube in third tower
    drive::forward(-12, 25.0, 0.6, 0.2, 17, 200);
    intake::spin(100);
    wait(500, msec);
    intake::reset();
    wait(500,msec);
    intake::spin(-50);
    wait(700, msec);
    intake::reset();
    tower();

    //move back from third tower
    drive::forward(-30, 25.0, 0.6, 0.2, 17, 200);

    while(1){
      printf("%f\n", drive::sonic.distance(vex::inches));
    }*/
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

  int tower(){
  intake::l.setBrake(hold);
  intake::r.setBrake(hold);
  wait(500, msec);
  arm::move(520,100,0.8,5,100);
 // drive::forwardEasy(12, 20.0);
  drive::spin(15);
  wait(2, sec);
  drive::reset();
  intake::spin(-25);

  wait(1,sec);
  arm::move(650,100,0.8,5,100);
  intake::reset();

  drive::forwardEasy(-10, 30.0);
  arm::m.spin(fwd, -100, pct);
  wait(100, msec);
  return 0; 
  }
}