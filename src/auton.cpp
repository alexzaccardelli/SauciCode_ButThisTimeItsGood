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

  void big(int side) {
    auton::deployTray();
    intake::spin(100);
    drive::forwardEasy(21, 35.0);
    if(side == 1) { drive::turnEasy(95, 75.0); }
    else {drive::turnEasy(-90, 75.0);}
    drive::forwardEasy(23,35.0);
    intake::reset();
    if(side == 1) { drive::turnEasy(45, 75.0); }
    else {drive::turnEasy(-30, 75.0);}
    drive::forwardEasy(8, 10.0);
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
    timer t;
    intake::spin(100);
    drive::spin(-30);
    auton::deployTray();

    //intake 10 cubes
    wait(1000,msec);
    drive::reset();
    intake::spin(100);
    drive::forward(70, 30.0, 0.6, 0.2, 17, 200);
    wait(1, sec); 
    //drive::reset();
    
    //drive::turn(-10, 65.0, 0.6, 0.2, 17, 200);
    drive::forwardEasy(15, 20.0);
    drive::forwardEasy(8, 20.0);
    drive::forwardEasy(8, 20.0);
    drive::forwardEasy(8, 20.0);
    drive::forwardEasy(16, 20.0);

    
    drive::reset();
    wait(2, vex::seconds);
    intake::reset();

    
    //turn towards goal zone
    drive::turnEasy(-43,25);
    //drive::forward(18, 35.0, 0.6, 0.2, 17, 200);
    drive::spin(35);
    wait(900, msec);
    drive::reset();

    
    //stacking
    intake::l.stop(coast);
    intake::r.stop(coast);
    tilter::move(850, 15, .6, 15, 500);
    wait(2, vex::seconds); 
    
    //drive away from goal zone 
    drive::forward(-16, 30.0, 0.6, 0.2, 17, 200);

    
    
    //turn to align with wall, hit wall
    drive::turn(125, 65.0, 0.6, 0.2, 17, 200);
    drive::untilHitWall(-50);
    
    //drive forward
    drive::forward(26, 70.0, 0.6, 0.2, 17, 200); //changed max to 100

    //turn towards tower 
    drive::turn(90, 25.0, 0.6, 0.2, 5, 300);
    tilter::m.spin(fwd, -100, pct);
    drive::untilHitWall(-50);

    //move tilter back
    
    while(tilter::m.torque() < 1.9) {}
    tilter::reset();

    intake::spin(100);

    //drive towards the tower 
    //drive::forward(46, 35.0, 0.6, 0.2, 17, 200);
    //drive::forward(10, 15.0, 0.6, 0.2, 17, 200);
    //drive::forward(56, 30.0, 0.6, 0.2, 17, 200);
    drive::forward(44, 60.0, 0.6, 0.2, 17, 200);
    drive::forward(12, 30.0, 0.6, 0.2, 17, 200);
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
    printf("%f\n",t.time(msec));
    tower();
    printf("%f\n",t.time(msec));

    //drive back until it hits the wall
    
    //drive::forward(-30, 50.0, 0.6, 0.2, 17, 200);
   

    /*
    drive::untilHitWall(-50);

    //drive forward and turn toward second tower
    drive::forward(23, 50.0, 0.6, 0.2, 17, 200);
    drive::turn(-95, 50.0, 0.6, 0.2, 10, 200);

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
    drive::turn(90, 50.0, 0.6, 0.2, 10, 200);
    drive::untilHitWall(-50);

    //move forward until parallel with third tower
    drive::forward(34, 25.0, 0.6, 0.2, 17, 200);

    //turn toward third tower
    drive::turn(90, 50.0, 0.6, 0.2, 10, 200);

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