#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "ControllerStatus.hpp"

class SerialHandler {
  public:
    SerialHandler(ControllerStatus& Status);

  private:
    void serialCountdown(int timer);
    void serialDebugEnabler(ControllerStatus& Status);
};

#endif
