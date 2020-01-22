#include "vex.h"
using namespace vex;

namespace drive {
  motor l1 = motor(PORT15, ratio18_1, false);
  motor l2 = motor(PORT16, ratio18_1, false);
  motor r1 = motor(PORT20, ratio18_1, true);
  motor r2 = motor(PORT11, ratio18_1, true);

  void reset() {
    motor l1 = motor(PORT15, ratio18_1, false);
    motor l2 = motor(PORT16, ratio18_1, false);
    motor r1 = motor(PORT20, ratio18_1, true);
    motor r2 = motor(PORT11, ratio18_1, true);
    l1.stop(coast);
    l2.stop(coast);
    r1.stop(coast);
    r2.stop(coast);
    l1.resetRotation();
    l2.resetRotation();
    r1.resetRotation();
    r2.resetRotation();
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

  int op() {
    double y1, y2, x1, x2, lVel, rVel;
    double accel = 2, max = 100, k;
    while(1) {
      y1 = con.Axis3.position();
      y2 = con.Axis2.position();
      x1 = con.Axis4.position();
      x2 = con.Axis1.position();

      if(y1 > max) lVel = max;
      else if(y1 < -max) lVel = -max;
      else if(y1 > lVel) lVel += accel;
      else if(y1 < lVel) lVel -= accel;
      if(y2 > max) rVel = max;
      else if(y2 < -max) rVel = -max;
      else if(y2 > rVel) rVel += accel;
      else if(y2 < rVel) rVel -= accel;
      
      if(fabs(y1 - y2) < 20) {
        k = .75;
        y1 = (y1 + y2) / 2;
        y2 = (y1 + y2) / 2;
      }
      else {
        k = .25;
      }
      lVel = y1;
      rVel = y2;

      l1.spin(fwd, lVel*k, pct);
      l2.spin(fwd, lVel*k, pct);
      r1.spin(fwd, rVel*k, pct);
      r2.spin(fwd, rVel*k, pct);
      
      wait(5, msec);
    }
  }

  int forward(double dist, double max, double accel, double kP, double range, double time) {
    reset();
    double ticks = dist / (2 * 3.1415 * 1.93) * 360.0;
    double lErr, rErr, lVel, rVel;
    timer t;
    while(1) {
      lErr = ticks - l1.rotation(deg);
      rErr = ticks - l1.rotation(deg);

      if(lErr * kP > max) lVel = max;
      else if(lErr * kP < -max) lVel = -max;
      else if(lErr * kP > lVel) lVel += accel;
      else if(lErr * kP < lVel) lVel -= accel;
      if(rErr * kP > max) rVel = max;
      else if(rErr * kP < -max) rVel = -max;
      else if(rErr * kP > rVel) rVel += accel;
      else if(rErr * kP < rVel) rVel -= accel;

      l1.spin(fwd, lVel, pct);
      l2.spin(fwd, lVel, pct);
      r1.spin(fwd, rVel, pct);
      r2.spin(fwd, rVel, pct);

      if(fabs(lErr) > range || fabs(rErr) > range) t.reset();
      if(t.time(msec) > time) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }

  int turn(double deg, double max, double accel, double kP, double range, double time) {
    reset();
    double ticks = deg * (360.0/135.0);
    double lErr, rErr, lVel, rVel;
    timer t;
    while(1) {
      lErr = ticks - l1.rotation(vex::deg);
      rErr = -(ticks - l1.rotation(vex::deg));

      lVel = kP*lErr;
      rVel = kP*rErr;

      l1.spin(fwd, lVel, pct);
      l2.spin(fwd, lVel, pct);
      r1.spin(fwd, rVel, pct);
      r2.spin(fwd, rVel, pct);

      if(fabs(lErr) > range || fabs(rErr) > range) t.reset();
      if(t.time(msec) > time) break;

      wait(5, msec);
    }
    reset();
    return 1;
  }
}