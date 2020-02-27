#include "vex.h"
using namespace vex;

namespace drive {
  motor l1 = motor(PORT13, ratio18_1, false);
  motor l2 = motor(PORT19, ratio18_1, false);
  motor r1 = motor(PORT15, ratio18_1, true);
  motor r2 = motor(PORT16, ratio18_1, true);

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

  int op() {
    double y1, y2, x1, x2, lVel, rVel, k;
    while (1) {
      y1 = con.Axis3.position();
      y2 = con.Axis2.position();
      x1 = con.Axis4.position();
      x2 = con.Axis1.position();

      if (fabs(y1 - y2) < 20) {
        k = .75;
        y1 = (y1 + y2) / 2;
        y2 = (y1 + y2) / 2;
      }
      else k = .25;
      lVel = y1;
      rVel = y2;

      l1.spin(fwd, lVel * k, pct);
      l2.spin(fwd, lVel * k, pct);
      r1.spin(fwd, rVel * k, pct);
      r2.spin(fwd, rVel * k, pct);

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
    wait(1, vex::sec);
    bool hit = false;
    while (!hit) {
      if (drive::l1.torque(vex::torqueUnits::InLb) > threshold ||
          drive::l2.torque(vex::torqueUnits::InLb) > threshold ||
          drive::r1.torque(vex::torqueUnits::InLb) > threshold ||
          drive::r2.torque(vex::torqueUnits::InLb) > threshold)
        hit = true;
    }
    wait(250,msec);
    reset();
  }
}