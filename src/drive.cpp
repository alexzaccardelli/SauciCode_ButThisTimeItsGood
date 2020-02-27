#include "vex.h"
using namespace vex;

namespace drive {
motor l1 = motor(PORT13, ratio18_1, false);
motor l2 = motor(PORT19, ratio18_1, false);
motor r1 = motor(PORT15, ratio18_1, true);
motor r2 = motor(PORT16, ratio18_1, true);
encoder enc = encoder(cpu.ThreeWirePort.C);

void reset() {
  l1.stop(coast);
  l2.stop(coast);
  r1.stop(coast);
  r2.stop(coast);
  l1.resetRotation();
  l2.resetRotation();
  r1.resetRotation();
  r2.resetRotation();
  enc.resetRotation();
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
int forwardEasy(double dist, double max, double kP) {
  reset();
  double range = 17, time = 100;
  double ticks = dist / (2.0 * 3.145 * 1.625) * 360.0;
  double err = 0, vel = 0;
  timer t;
  while (1) {
    err = ticks - l1.rotation(deg);

    if (err * kP > max)
      vel = max;
    else if (err * kP < -max)
      vel = -max;
    else vel = err * kP;

    l1.spin(fwd, vel, pct);
    l2.spin(fwd, vel, pct);
    r1.spin(fwd, vel, pct);
    r2.spin(fwd, vel, pct);

    if (fabs(err) > range)
      t.reset();
    if (t.time(msec) > time)
      break;

    wait(5, msec);
  }
  reset();
  return 1;
}
int forward(double dist, double max, double accel, double kP, double range,
            double time) {
  reset();
  double ticks = dist / (2 * 3.1415 * 1.93) * 360.0;
  double lErr = 0, rErr = 0, lVel = 0, rVel = 0;
  timer t;
  while (1) {
    lErr = ticks - enc.rotation(deg);
    rErr = ticks - enc.rotation(deg);

    if (lErr * kP > max) lVel = max;
    else if (lErr * kP < -max) lVel = -max;
    else if (lErr * kP > lVel) lVel += accel;
    else if (lErr * kP < lVel) lVel -= accel;
    
    rVel = lVel;
    l1.spin(fwd, lVel, pct);
    l2.spin(fwd, lVel, pct);
    r1.spin(fwd, rVel, pct);
    r2.spin(fwd, rVel, pct);

    if (fabs(lErr) > range || fabs(rErr) > range)
      t.reset();
    if (t.time(msec) > time)
      break;

    wait(5, msec);
  }
  reset();
  return 1;
}

int turn(double deg, double max, double accel, double kP, double range,
         double time) {
  reset();
  double ticks = deg * (250.0 / 90.0);
  double lErr=0, rErr=0, lVel=0, rVel=0;
  double rotations = l1.rotation(vex::deg);
  timer t, t1;
  while (1) {
    rotations = l1.rotation(vex::deg);

    lErr = ticks - rotations;
    rErr = -(ticks - rotations);

    if (lErr * kP > max) lVel = max;
    else if (lErr * kP < -max) lVel = -max;
    else if (lErr * kP > lVel) lVel += accel;
    else if (lErr * kP < lVel) lVel -= accel;
    if (rErr * kP > max) rVel = max;
    else if (rErr * kP < -max) rVel = -max;
    else if (rErr * kP > rVel) rVel += accel;
    else if (rErr * kP < rVel) rVel -= accel;

    lVel = lErr * kP;
    rVel = rErr * kP;

    l1.spin(fwd, lVel, pct);
    l2.spin(fwd, lVel, pct);
    r1.spin(fwd, rVel, pct);
    r2.spin(fwd, rVel, pct);

    if (fabs(lErr) > range || fabs(rErr) > range)
      t.reset();
    if (t.time(msec) > time) break;
    if (t1.time(msec) > 5000) break;

    wait(5, msec);
  }
  reset();
  return 1;
}

int turnEasy(double deg, double max) {
  double kP=0.25, range=4, time=250;
  reset();
  double ticks = deg * (250.0 / 90.0);
  double lErr=0, rErr=0, lVel=0, rVel=0;
  double rotations = l1.rotation(vex::deg);
  timer t, t1;
  while (1) {
    rotations = l1.rotation(vex::deg);

    lErr = ticks - rotations;
    rErr = -(ticks - rotations);

    if (lErr * kP > max) lVel = max;
    else if (lErr * kP < -max) lVel = -max;
    else lVel = lErr * kP;
    if (rErr * kP > max) rVel = max;
    else if (rErr * kP < -max) rVel = -max;
    else rVel = rErr * kP;

    l1.spin(fwd, lVel, pct);
    l2.spin(fwd, lVel, pct);
    r1.spin(fwd, rVel, pct);
    r2.spin(fwd, rVel, pct);

    if (fabs(lErr) > range || fabs(rErr) > range)
      t.reset();
    if (t.time(msec) > time) break;
    if (t1.time(msec) > 5000) break;

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
} // namespace drive