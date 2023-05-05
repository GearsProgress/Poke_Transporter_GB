#include <string>
#include <tonc.h>

#include "gb_link.h"
#include "interrupt.h"
#include "LinkSPI.h"


// (1) Create a LinkSPI instance
LinkSPI* linkSPI = new LinkSPI();

void init() {
  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
  tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));

  // (2) Add the interrupt service routines
  interrupt_init();
  interrupt_set_handler(INTR_VBLANK, VBLANK);
  interrupt_enable(INTR_VBLANK);
  interrupt_set_handler(INTR_SERIAL, LINK_SPI_ISR_SERIAL);
  interrupt_enable(INTR_SERIAL);
}

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

int start_link() {
  init();

u32 SPIout = 0x0200FEFE;
u32 SPIin = 0x00000000;
  bool firstTransfer = false;

  while (true) {
    std::string output = "";
    u16 keys = ~REG_KEYS & KEY_ANY;

    if (!linkSPI->isActive()) {
      firstTransfer = true;
    linkSPI->activate(LinkSPI::Mode::SLAVE);
    } else {
      // Title
      auto modeName =
          linkSPI->getMode() == LinkSPI::Mode::SLAVE ? "[slave]" : "[master]";
      output += std::string(modeName) + "\n";
      if (firstTransfer) {
        log(output + "Waiting for link cable...\nPress L and R to cancel");
        firstTransfer = false;
      }

        // (4)/(5) Exchange 32-bit data with the other end
        SPIin = linkSPI->transfer(SPIout, []() {
        bool exit = false;
          u16 keys = ~REG_KEYS & KEY_ANY;
          if ((keys & KEY_L) && (keys & KEY_R)){
            exit = true;
          }
          return exit;
        });
        if (SPIin == 0x61616161){
            SPIout = 0x61616161;
        } else if ((SPIin & 0x0000FFFF) == 0x0000D1D1){
            SPIout = 0xD1D1D1D1;
        }
        output += "Send: " + std::to_string((SPIout)) + "\n";
        output += "Recv: " + std::to_string((SPIin)) + "\n";

      // Cancel
      if ((keys & KEY_L) && (keys & KEY_R)) {
        linkSPI->deactivate();
        return 0;
      }
    }

    // Print
    VBlankIntrWait();
    log(output);
  }

  return 0;
}

void log(std::string text) {
  tte_erase_screen();
  tte_write("#{P:0,0}");
  tte_write(text.c_str());
}

void wait(u32 verticalLines) {
  u32 count = 0;
  u32 vCount = REG_VCOUNT;

  while (count < verticalLines) {
    if (REG_VCOUNT != vCount) {
      count++;
      vCount = REG_VCOUNT;
    }
  };
}


