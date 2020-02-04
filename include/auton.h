#ifndef _AUTON_H_
#define _AUTON_H_
using namespace vex;

namespace auton {
  enum {
    red = -1,
    blue = 1
  };

  void resetAll();
  void small(int side);
  int deployTray();
  int op();
  int skills();
  int big(int side); //blue = 1, red = -1
  int redSmall();
  int blueSmall();
  void onePoint();
  int tower();
}

#endif