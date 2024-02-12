// Original code created by afska https://github.com/afska/gba-link-connection/tree/master

#include <tonc.h>
#include <string>

// (0) Include the header
#include "LinkSPI.hpp"

// (1) Create a LinkSPI instance
LinkSPI* linkSPI = new LinkSPI();

void cable_init() {
  
  // (2) Add the interrupt service routines
  /* LIBUGBA setup:
  interrupt_init();
  interrupt_set_handler(INTR_VBLANK, VBLANK);
  interrupt_enable(INTR_VBLANK);
  interrupt_set_handler(INTR_SERIAL, LINK_SPI_ISR_SERIAL);
  interrupt_enable(INTR_SERIAL);
  */
  irq_init(NULL);
  irq_enable(II_VBLANK);
  irq_add(II_SERIAL, LINK_SPI_ISR_SERIAL);

}

int example_main() {
  cable_init();

  bool firstTransfer = false;
  bool async = false;
  u32 counter = 0;

  while (true) {
    std::string output = "";
    u16 keys = ~REG_KEYS & KEY_ANY;

    if (!linkSPI->isActive()) {
      firstTransfer = true;
      output += "START: Set as Master\n";
      output += "SELECT: Set as Slave\n";
      output += "\n(stop: press L+R)\n";
      output += "(hold A on start for async)\n";
      output += "(hold B on start for waitMode)\n";
      output +=
          "\n\n\n\n\n\n\n\n\n\n\n\n[!] to test this demo...\n      "
          "...use a GBC Link Cable!";

      if ((keys & KEY_START) | (keys & KEY_SELECT)) {
        // (3) Initialize the library
        linkSPI->activate((keys & KEY_START) ? LinkSPI::Mode::MASTER_256KBPS
                                             : LinkSPI::Mode::SLAVE);
        linkSPI->setWaitModeActive(keys &
                                   KEY_B);  // see `waitMode` in README.md
        if (keys & KEY_A)
          async = true;
      }
    } else {
      // Title
      auto modeName =
          linkSPI->getMode() == LinkSPI::Mode::SLAVE ? "[slave]" : "[master]";
      output += std::string(modeName) + "\n";
      if (firstTransfer) {
        log(output + "Waiting...");
        firstTransfer = false;
      }

      if (!async) {
        // (4)/(5) Exchange 32-bit data with the other end
        u32 remoteKeys = linkSPI->transfer(keys, []() {
          u16 keys = ~REG_KEYS & KEY_ANY;
          return (keys & KEY_L) && (keys & KEY_R);
        });
        output += "> " + std::to_string(keys) + "\n";
        output += "< " + std::to_string(remoteKeys) + "\n";
      } else {
        // (6) Exchange data asynchronously
        if (keys != 0 &&
            linkSPI->getAsyncState() == LinkSPI::AsyncState::IDLE) {
          counter++;
          linkSPI->transferAsync(counter, []() {
            u16 keys = ~REG_KEYS & KEY_ANY;
            return (keys & KEY_L) && (keys & KEY_R);
          });
          log(output + ">> " + std::to_string(counter));
          wait(228 * 60);
        }
        if (linkSPI->getAsyncState() == LinkSPI::AsyncState::READY) {
          log(output + "<< " + std::to_string(linkSPI->getAsyncData()));
          wait(228 * 60);
        }
      }

      // Cancel
      if ((keys & KEY_L) && (keys & KEY_R)) {
        linkSPI->deactivate();
        async = false;
        counter = 0;
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