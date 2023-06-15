#ifndef LINK_GPIO_H
#define LINK_GPIO_H

// --------------------------------------------------------------------------
// A General Purpose Input-Output handler for the Link Port.
// --------------------------------------------------------------------------
// Usage:
// - 1) Include this header in your main.cpp file and add:
//       LinkGPIO* linkGPIO = new LinkGPIO();
// - 2) Initialize the library with:
//       linkGPIO->reset();
// - 3) Write pins by using:
//       linkGPIO->setMode(LinkGPIO::Pin::SD, LinkGPIO::Direction::OUTPUT);
//       linkGPIO->writePin(LinkGPIO::Pin::SD, true);
// - 4) Read pins by using:
//       linkGPIO->setMode(LinkGPIO::Pin::SC, LinkGPIO::Direction::INPUT);
//       bool isHigh = linkGPIO->readPin(LinkGPIO::Pin::SC);
// - 5) Subscribe to SI falling:
//       linkGPIO->setSIInterrupts(true);
//       // (when SI changes from high to low, an IRQ will be generated)
// --------------------------------------------------------------------------
// `setMode` restrictions:
// - always set the SI terminal to an input!
// --------------------------------------------------------------------------

#include <tonc_core.h>

#define LINK_GPIO_RCNT_GENERAL_PURPOSE (1 << 15)
#define LINK_GPIO_SIOCNT_GENERAL_PURPOSE 0
#define LINK_GPIO_BIT_SI_INTERRUPT 8
#define LINK_GPIO_GET(REG, BIT) ((REG >> BIT) & 1)
#define LINK_GPIO_SET(REG, BIT, DATA) \
  if (DATA)                           \
    LINK_GPIO_SET_HIGH(REG, BIT);     \
  else                                \
    LINK_GPIO_SET_LOW(REG, BIT);
#define LINK_GPIO_SET_HIGH(REG, BIT) REG |= 1 << BIT
#define LINK_GPIO_SET_LOW(REG, BIT) REG &= ~(1 << BIT)

static volatile char LINK_GPIO_VERSION[] = "LinkGPIO/v5.0.2";

const u8 LINK_GPIO_DATA_BITS[] = {2, 3, 1, 0};
const u8 LINK_GPIO_DIRECTION_BITS[] = {6, 7, 5, 4};

class LinkGPIO {
 public:
  enum Pin { SI, SO, SD, SC };
  enum Direction { INPUT, OUTPUT };

  void reset() {
    REG_RCNT = LINK_GPIO_RCNT_GENERAL_PURPOSE;
    REG_SIOCNT = LINK_GPIO_SIOCNT_GENERAL_PURPOSE;
  }

  void setMode(Pin pin, Direction direction) {
    if (pin == Pin::SI && Direction::OUTPUT)
      return;  // (disabled for safety reasons)

    LINK_GPIO_SET(REG_RCNT, LINK_GPIO_DIRECTION_BITS[pin],
                  direction == Direction::OUTPUT);
  }

  Direction getMode(Pin pin) {
    return Direction(LINK_GPIO_GET(REG_RCNT, LINK_GPIO_DIRECTION_BITS[pin]));
  }

  bool readPin(Pin pin) {
    return (REG_RCNT & (1 << LINK_GPIO_DATA_BITS[pin])) != 0;
  }

  void writePin(Pin pin, bool isHigh) {
    LINK_GPIO_SET(REG_RCNT, LINK_GPIO_DATA_BITS[pin], isHigh);
  }

  void setSIInterrupts(bool isEnabled) {
    LINK_GPIO_SET(REG_RCNT, LINK_GPIO_BIT_SI_INTERRUPT, isEnabled);
  }
};

extern LinkGPIO* linkGPIO;

#endif  // LINK_GPIO_H
