#ifndef LINK_SPI_H
#define LINK_SPI_H

// --------------------------------------------------------------------------
// An SPI handler for the Link Port (Normal Mode, 32bits).
// --------------------------------------------------------------------------
// Usage:
// - 1) Include this header in your main.cpp file and add:
//       LinkSPI* linkSPI = new LinkSPI();
// - 2) (Optional) Add the interrupt service routines:
//       irq_init(NULL);
//       irq_add(II_SERIAL, LINK_SPI_ISR_SERIAL);
//       // (this is only required for `transferAsync`)
// - 3) Initialize the library with:
//       linkSPI->activate(LinkSPI::Mode::MASTER_256KBPS);
//       // (use LinkSPI::Mode::SLAVE on the other end)
// - 4) Exchange 32-bit data with the other end:
//       u32 data = linkSPI->transfer(0x1234);
//       // (this blocks the console indefinitely)
// - 5) Exchange data with a cancellation callback:
//       u32 data = linkSPI->transfer(0x1234, []() {
//         u16 keys = ~REG_KEYS & KEY_ANY;
//         return keys & KEY_START;
//       });
// - 6) Exchange data asynchronously:
//       linkSPI->transferAsync(0x1234);
//       // ...
//       if (linkSPI->getAsyncState() == LinkSPI::AsyncState::READY) {
//         u32 data = linkSPI->getAsyncData();
//         // ...
//       }
// --------------------------------------------------------------------------
// considerations:
// - when using Normal Mode between two GBAs, use a GBC Link Cable!
// - only use the 2Mbps mode with custom hardware (very short wires)!
// - don't send 0xFFFFFFFF, it's reserved for errors!
// --------------------------------------------------------------------------

#include <tonc_core.h>

#define LINK_SPI_NO_DATA 0xffffffff
#define LINK_SPI_SIOCNT_NORMAL 0
#define LINK_SPI_BIT_CLOCK 0
#define LINK_SPI_BIT_CLOCK_SPEED 1
#define LINK_SPI_BIT_SI 2
#define LINK_SPI_BIT_SO 3
#define LINK_SPI_BIT_START 7
#define LINK_SPI_BIT_LENGTH 12
#define LINK_SPI_BIT_IRQ 14
#define LINK_SPI_BIT_GENERAL_PURPOSE_LOW 14
#define LINK_SPI_BIT_GENERAL_PURPOSE_HIGH 15
#define LINK_SPI_SET_HIGH(REG, BIT) REG |= 1 << BIT
#define LINK_SPI_SET_LOW(REG, BIT) REG &= ~(1 << BIT)

static volatile char LINK_SPI_VERSION[] = "LinkSPI/v5.0.2";

class LinkSPI {
 public:
  enum Mode { SLAVE, MASTER_256KBPS, MASTER_2MBPS };
  enum AsyncState { IDLE, WAITING, READY };

  bool isActive() { return isEnabled; }

  void activate(Mode mode) {
    this->mode = mode;
    this->waitMode = false;
    this->asyncState = IDLE;
    this->asyncData = 0;

    setNormalMode();
    set32BitPackets();
    setInterruptsOff();
    disableTransfer();

    if (mode == SLAVE)
      setSlaveMode();
    else {
      setMasterMode();

      if (mode == MASTER_256KBPS)
        set256KbpsSpeed();
      else if (mode == MASTER_2MBPS)
        set2MbpsSpeed();
    }

    isEnabled = true;
  }

  void deactivate() {
    isEnabled = false;
    stopTransfer();
    disableTransfer();
    setGeneralPurposeMode();

    mode = SLAVE;
    waitMode = false;
    asyncState = IDLE;
    asyncData = 0;
  }

  u32 transfer(u32 data) {
    return transfer(data, []() { return false; });
  }

  template <typename F>
  u32 transfer(u32 data,
               F cancel,
               bool _async = false,
               bool _customAck = false) {
    if (asyncState != IDLE)
      return LINK_SPI_NO_DATA;

    setData(data);

    if (_async) {
      asyncState = WAITING;
      setInterruptsOn();
    } else {
      setInterruptsOff();
    }

    enableTransfer();

    while (isMaster() && waitMode && !isSlaveReady())
      if (cancel()) {
        disableTransfer();
        setInterruptsOff();
        asyncState = IDLE;
        return LINK_SPI_NO_DATA;
      }

    startTransfer();

    if (_async)
      return LINK_SPI_NO_DATA;

    while (!isReady())
      if (cancel()) {
        stopTransfer();
        disableTransfer();
        return LINK_SPI_NO_DATA;
      }

    if (!_customAck)
      disableTransfer();

    return getData();
  }

  void transferAsync(u32 data) {
    transfer(
        data, []() { return false; }, true);
  }

  template <typename F>
  void transferAsync(u32 data, F cancel) {
    transfer(data, cancel, true);
  }

  u32 getAsyncData() {
    if (asyncState != READY)
      return LINK_SPI_NO_DATA;

    u32 data = asyncData;
    asyncState = IDLE;
    return data;
  }

  Mode getMode() { return mode; }
  void setWaitModeActive(bool isActive) { waitMode = isActive; }
  bool isWaitModeActive() { return waitMode; }
  AsyncState getAsyncState() { return asyncState; }

  void _onSerial(bool _customAck = false) {
    if (!isEnabled || asyncState != WAITING)
      return;

    if (!_customAck)
      disableTransfer();

    setInterruptsOff();
    asyncState = READY;
    asyncData = getData();
  }

  void _setSOHigh() { setBitHigh(LINK_SPI_BIT_SO); }
  void _setSOLow() { setBitLow(LINK_SPI_BIT_SO); }
  bool _isSIHigh() { return isBitHigh(LINK_SPI_BIT_SI); }

 private:
  Mode mode = Mode::SLAVE;
  bool waitMode = false;
  AsyncState asyncState = IDLE;
  u32 asyncData = 0;
  bool isEnabled = false;

  void setNormalMode() {
    LINK_SPI_SET_LOW(REG_RCNT, LINK_SPI_BIT_GENERAL_PURPOSE_HIGH);
    REG_SIOCNT = LINK_SPI_SIOCNT_NORMAL;
  }

  void setGeneralPurposeMode() {
    LINK_SPI_SET_LOW(REG_RCNT, LINK_SPI_BIT_GENERAL_PURPOSE_LOW);
    LINK_SPI_SET_HIGH(REG_RCNT, LINK_SPI_BIT_GENERAL_PURPOSE_HIGH);
  }

  void setData(u32 data) { REG_SIODATA32 = data; }
  u32 getData() { return REG_SIODATA32; }

  void enableTransfer() { _setSOLow(); }
  void disableTransfer() { _setSOHigh(); }
  void startTransfer() { setBitHigh(LINK_SPI_BIT_START); }
  void stopTransfer() { setBitLow(LINK_SPI_BIT_START); }
  bool isReady() { return !isBitHigh(LINK_SPI_BIT_START); }
  bool isSlaveReady() { return !_isSIHigh(); }

  void set32BitPackets() { setBitHigh(LINK_SPI_BIT_LENGTH); }
  void setMasterMode() { setBitHigh(LINK_SPI_BIT_CLOCK); }
  void setSlaveMode() { setBitLow(LINK_SPI_BIT_CLOCK); }
  void set256KbpsSpeed() { setBitLow(LINK_SPI_BIT_CLOCK_SPEED); }
  void set2MbpsSpeed() { setBitHigh(LINK_SPI_BIT_CLOCK_SPEED); }
  void setInterruptsOn() { setBitHigh(LINK_SPI_BIT_IRQ); }
  void setInterruptsOff() { setBitLow(LINK_SPI_BIT_IRQ); }

  bool isMaster() { return mode != SLAVE; }
  bool isBitHigh(u8 bit) { return (REG_SIOCNT >> bit) & 1; }
  void setBitHigh(u8 bit) { LINK_SPI_SET_HIGH(REG_SIOCNT, bit); }
  void setBitLow(u8 bit) { LINK_SPI_SET_LOW(REG_SIOCNT, bit); }
};

extern LinkSPI* linkSPI;

inline void LINK_SPI_ISR_SERIAL() {
  linkSPI->_onSerial();
}

#endif  // LINK_SPI_H