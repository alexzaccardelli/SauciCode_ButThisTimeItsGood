#include "vex.h"
using namespace vex;

namespace drive {
  motor l1 = motor(PORT13, ratio18_1, false);
  motor l2 = motor(PORT19, ratio18_1, false);
  motor r1 = motor(PORT15, ratio18_1, true);
  motor r2 = motor(PORT16, ratio18_1, true);
  bool b = false;

  void reset() {
    l1.stop(coast);
    l2.stop(coast);
    r1.stop(coast);
    r2.stop(coast);
    l1.resetRotation();
    l2.resetRotation();
    r1.resetRotation();
    r2.resetRotation();
  }

  void stop() {
    l1.stop(brake);
    l2.stop(brake);
    r1.stop(brake);
    r2.stop(brake);
  }
  void spin(int vel) {
    l1.spin(fwd, vel, pct);
    l2.spin(fwd, vel, pct);
    r1.spin(fwd, vel, pct);
    r2.spin(fwd, vel, pct);
  }
  void spinRight(int vel) {
    r1.spin(fwd, vel, pct);
    r2.spin(fwd, vel, pct);
  }
  void spinLeft(int vel) {
    l1.spin(fwd, vel, pct);
    l2.spin(fwd, vel, pct);
  }

  int a() {
    int last = 0;
    while(1) {
      if(con.ButtonLeft.pressing()) {
        if(last == 1) {
          last = 0;
          b = true;
        }
        else {
          last = 1;
          b = false;
        }
        while(con.ButtonLeft.pressing()) {
          wait(5, msec);
        }
      }
      wait(5, msec);
    }
  }

  int op() {
    double y1, y2, x1, x2, lVel, rVel, k;
    double accel = .8, decel = .3;
    while (1) {
      if(con.ButtonRight.pressing()) {
        while(con.ButtonRight.pressing()) {
          spin(40);
        }
        reset();
      }
      y1 = con.Axis3.position();
      y2 = con.Axis2.position();
      x1 = con.Axis4.position();
      x2 = con.Axis1.position();
      
      if(fabs(y1 - y2) < 20 && y1 > 0 && y2 > 0) {
        k = .65;
        if((y1 + y2) / 2 > lVel) {
          lVel += accel;
          rVel += accel;
        }
        else {
          lVel = (y1 + y2) / 2 * k;
          rVel = (y1 + y2) / 2 * k;
        }
      }
      else if(fabs(y1 - y2) < 20 && y1 < 0 && y2 < 0 && b) {
        k =.20;
        if((y1 + y2) / 2 < lVel) {
          lVel -= decel;
          rVel -= decel;
        }
        if(lVel < -20) {
            lVel = -20;
          }
          if(rVel < -20) {
            rVel = -20;
          }
        else {
          lVel = (y1 + y2) / 2 * k;
          rVel = (y1 + y2) / 2 * k;
        }
      }
      else if(fabs(y1 - y2) < 20 && y1 < 0 && y2 < 0 && !b) {
        k =.75;
        if((y1 + y2) / 2 < lVel) {
          lVel -= decel;
          rVel -= decel;
          if(lVel < -75) {
            lVel = -75;
          }
          if(rVel < -75) {
            rVel = -75;
          }
        }
        else {
          lVel = (y1 + y2) / 2 * k;
          rVel = (y1 + y2) / 2 * k;
        }
      }
      else if(fabs(y1 - y2) > 20) {
        k =.25;
        lVel = y1 * k;
        rVel = y2 * k;
      }
      else {
        if(lVel > 0) {
          lVel -= accel;
        }
        else if(lVel < 0) {
          lVel += decel;
        }
        else lVel = 0;
        if(rVel > 0) {
          rVel -= accel;
        }
        else if(rVel < 0) {
          rVel += decel;
        }
        else rVel = 0;
      }

      l1.spin(fwd, lVel, pct);
      l2.spin(fwd, lVel, pct);
      r1.spin(fwd, rVel, pct);
      r2.spin(fwd, rVel, pct);

      wait(5, msec);
    }
  }
  int forward(double dist, double max, double kP, double range, double time, double timeout) {
    reset();
    double ticks = dist / (2.0 * 3.145 * 1.87) * 360.0;
    double err = 0, vel = 0;
    timer t, t1;
    while (1) {
      err = ticks - l1.rotation(deg);

      if (err * kP > max) vel = max;
      else if (err * kP < -max) vel = -max;
      else vel = err * kP;

      l1.spin(fwd, vel, pct);
      l2.spin(fwd, vel, pct);
      r1.spin(fwd, vel, pct);
      r2.spin(fwd, vel, pct);

      if (fabs(err) > range) t.reset();
      if (t.time(msec) > time) break;
      if (t1.time(msec) > timeout) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }

  int turn(double deg, double max, double kP, double range, double time, double timeout) {
    reset();
    double ticks = deg * 2.49;
    double err = 0, vel = 0;
    timer t, t1;
    while (1) {
      err = ticks - l1.rotation(vex::deg);

      if (err * kP > max) vel = max;
      else if (err * kP < -max) vel = -max;
      else vel = err * kP;

      l1.spin(fwd, vel, pct);
      l2.spin(fwd, vel, pct);
      r1.spin(fwd, -vel, pct);
      r2.spin(fwd, -vel, pct);

      if (fabs(vel) > range) t.reset();
      if (t.time(msec) > time) break;
      if (t1.time(msec) > timeout) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }

  void untilHitWall(double speed) {
    double threshold = 7.0;
    drive::l1.spin(vex::fwd, speed, vex::pct);
    drive::l2.spin(vex::fwd, speed, vex::pct);
    drive::r1.spin(vex::fwd, speed, vex::pct);
    drive::r2.spin(vex::fwd, speed, vex::pct);
    wait(400, vex::sec);
    bool hit = false;
    while (!hit) {
      if (drive::l1.torque(vex::torqueUnits::InLb) > threshold ||
          drive::l2.torque(vex::torqueUnits::InLb) > threshold ||
          drive::r1.torque(vex::torqueUnits::InLb) > threshold ||
          drive::r2.torque(vex::torqueUnits::InLb) > threshold)
        hit = true;
    }
    //wait(250,msec);
    reset();
  }
}