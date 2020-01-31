#include "vex.h"
using namespace vex;

namespace drive {
motor l1 = motor(PORT1, ratio18_1, false);
motor l2 = motor(PORT17, ratio18_1, false);
motor r1 = motor(PORT2, ratio18_1, true);
motor r2 = motor(PORT14, ratio18_1, true);

void reset() {
  /*motor l1 = motor(PORT15, ratio18_1, false);
  motor l2 = motor(PORT16, ratio18_1, false);
  motor r1 = motor(PORT20, ratio18_1, true);
  motor r2 = motor(PORT11, ratio18_1, true);*/
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
  double y1, y2, x1, x2, lVel, rVel;
  double accel = 2, max = 100, k;
  while (1) {
    y1 = con.Axis3.position();
    y2 = con.Axis2.position();
    x1 = con.Axis4.position();
    x2 = con.Axis1.position();

    if (y1 > max)
      lVel = max;
    else if (y1 < -max)
      lVel = -max;
    else if (y1 > lVel)
      lVel += accel;
    else if (y1 < lVel)
      lVel -= accel;
    if (y2 > max)
      rVel = max;
    else if (y2 < -max)
      rVel = -max;
    else if (y2 > rVel)
      rVel += accel;
    else if (y2 < rVel)
      rVel -= accel;

    if (fabs(y1 - y2) < 20) {
      k = .75;
      y1 = (y1 + y2) / 2;
      y2 = (y1 + y2) / 2;
    } else {
      k = .25;
    }
    lVel = y1;
    rVel = y2;

    l1.spin(fwd, lVel * k, pct);
    l2.spin(fwd, lVel * k, pct);
    r1.spin(fwd, rVel * k, pct);
    r2.spin(fwd, rVel * k, pct);

    wait(5, msec);
  }
}

int forward(double dist, double max, double accel, double kP, double range,
            double time) {
  reset();
  double ticks = dist / (2 * 3.1415 * 1.93) * 360.0;
  double lErr = 0, rErr = 0, lVel = 0, rVel = 0;
  timer t;
  while (1) {
    lErr = ticks - l1.rotation(deg);
    rErr = ticks - l1.rotation(deg);
    //lVel = lErr;
    //rVel = rErr;

    if (lErr * kP > max)
      lVel = max;
    else if (lErr * kP < -max)
      lVel = -max;
    else if (lErr * kP > lVel)
      lVel += accel;
    else if (lErr * kP < lVel)
      lVel -= accel;
      /*
    if (rErr * kP > max)
      rVel = max;
    else if (rErr * kP < -max)
      rVel = -max;
    else if (rErr * kP > rVel)
      rVel += accel;
    else if (rErr * kP < rVel)
      rVel -= accel;
  */
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
  printf("N: %f\n", drive::l1.rotation(vex::degrees));
  reset();
  return 1;
}

int turn(double deg, double max, double accel, double kP, double range,
         double time) {
  reset();
  // double ticks = deg * (360.0/135.0);
  double ticks = deg * (250.0 / 90.0);
  double lErr=0, rErr=0, lVel=0, rVel=0;
  double rotations = l1.rotation(vex::deg);
  timer t, t1;
  while (1) {
    if (fabs(l1.rotation(vex::deg)) < fabs(r1.rotation(vex::deg)))
      rotations = -1* l1.rotation(vex::deg);
    else
      rotations = l1.rotation(vex::deg);

    lErr = ticks - rotations;
    rErr = -(ticks - rotations);

    if (lErr * kP > max)
      lVel = max;
    else if (lErr * kP < -max)
      lVel = -max;
    else if (lErr * kP > lVel)
      lVel += accel;
    else if (lErr * kP < lVel)
      lVel -= accel;
    if (rErr * kP > max)
      rVel = max;
    else if (rErr * kP < -max)
      rVel = -max;
    else if (rErr * kP > rVel)
      rVel += accel;
    else if (rErr * kP < rVel)
      rVel -= accel;

    lVel = lErr * kP;
    rVel = rErr * kP;

    l1.spin(fwd, lVel, pct);
    l2.spin(fwd, lVel, pct);
    r1.spin(fwd, rVel, pct);
    r2.spin(fwd, rVel, pct);

    if (fabs(lErr) > range || fabs(rErr) > range)
      t.reset();
    if (t.time(msec) > time)
      break;
    if (t1.time(msec) > 5000)
      break;

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
  reset();
}
} // namespace drive