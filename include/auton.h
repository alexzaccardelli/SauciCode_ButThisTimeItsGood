#ifndef _AUTON_H_
#define _AUTON_H_
using namespace vex;

namespace auton {
  enum {
    red = 1,
    blue = -1
  };

  void resetAll();
  void small();
  int deployTray();
  int op();
  int skills();
  int redSmall();
  int blueSmall();
  void onePoint();
}

#endif