#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

#include "robot-config.h"

extern brain cpu;
extern controller con;

#include "drive.h"
#include "intake.h"
#include "tilter.h"
#include "arm.h"
#include "auton.h"

extern task driveTask, intakeTask, tilterTask, armTask, autonTask, a, stopperTask;

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)