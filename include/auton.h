#ifndef _AUTON_H_
#define _AUTON_H_
using namespace vex;

namespace auton {
  enum {
    red = -1,
    blue = 1
  };

  void resetAll();
  int deployTray();

  void onePoint();
  void small(int side);
  void big(int side);

  int skills();
  int tower();
}

#endif