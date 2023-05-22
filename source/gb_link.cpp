#include <string>
#include <tonc.h>

#include "gb_link.h"
#include "interrupt.h"
#include "LinkSPI.h"
#include "debug.h"

// (1) Create a LinkSPI instance
LinkSPI *linkSPI = new LinkSPI();

vu32 trainerData[111] = {0x8A918892, 0x50505050, 0x50505006, 0x9B9B9B9B, 0x9B9BFF25, 0xDA9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A8A9188, 0x92505050, 0x50505050, 0x8A918892, 0x50505050, 0x5050508A, 0x91889250, 0x50505050, 0x50508A91, 0x88925050, 0x50505050, 0x508A9188, 0x92505050, 0x50505050, 0x8A918892, 0x50505050, 0x50505082, 0x988D8380, 0x9094888B, 0x50508298, 0x8D838090, 0x94888B50, 0x5082988D, 0x83809094, 0x888B5050, 0x82988D83, 0x80909488, 0x8B505082, 0x988D8380, 0x9094888B, 0x50508298, 0x8D838090, 0x94888B50, 0x50000000};

void init()
{
  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
  tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));

  // (2) Add the interrupt service routines
  interrupt_init();
  interrupt_set_handler(INTR_VBLANK, VBLANK);
  interrupt_enable(INTR_VBLANK);
  interrupt_set_handler(INTR_SERIAL, LINK_SPI_ISR_SERIAL);
  interrupt_enable(INTR_SERIAL);
}

std::string convertToString(char *a, int size)
{
  int i;
  std::string s = "";
  for (i = 0; i < size; i++)
  {
    s = s + a[i];
  }
  return s;
}

int start_link()
{
  init();

  u32 SPIout = 0x0200FEFE; // What the GBA is sending out to the GBC
  u32 SPIin = 0x00000000;  // What the GBA is receiving from the GBC
  std::string outputSArr[16] = {};
  std::string outputRArr[16] = {};
  u32 mode = 0; // Trick game into entering trading room
  bool firstTransfer = false;
  u32 index = 0;
  std::string bigOut = "";

  while (true)
  {
    std::string output = "";

    u16 keys = ~REG_KEYS & KEY_ANY;

    if (!linkSPI->isActive())
    {
      firstTransfer = true;
      linkSPI->activate(LinkSPI::Mode::SLAVE);
    }
    else
    {
      // Title
      auto modeName =
          linkSPI->getMode() == LinkSPI::Mode::SLAVE ? "[slave]" : "[master]";
      output += std::string(modeName) + "\n";
      if (firstTransfer)
      {
        log(output + "Waiting for link cable...\nPress L and R to cancel");
        firstTransfer = false;
      }

      // (4)/(5) Exchange 32-bit data with the other end
      SPIin = linkSPI->transfer(SPIout, []()
                                {
        bool exit = false;
          u16 keys = ~REG_KEYS & KEY_ANY;
          if ((keys & KEY_L) && (keys & KEY_R)){
            exit = true;
          }
          return exit; });

      if (mode == 0)
      {
        switch (SPIin & 0xFF)
        {
        case 0x61:
          SPIout = 0x61616161;
          break;

        case 0xD1:
          SPIout = 0xD1D1D1D1;
          break;

        case 0x75:
          SPIout = 0x75757575;
          break;

        case 0x76:
          SPIout = 0x76767676;
          break;

        case 0xFD:
          SPIout = 0xFDFDFDFD;
          mode = 1;
          break;

        default:
          SPIout = 0x01234567;
        }
      }
      else if (mode == 1)
      {
        if (index < 111){
        SPIout = trainerData[index];
        // Do better ^
        index++;
        }
        else if (index == 8){
          while(true){}
        }
        else {
          SPIout = 0x00000000;
        }
      }

      for (int i = 15; i > 0; i--)
      {
        outputSArr[i] = outputSArr[i - 1];
        outputRArr[i] = outputRArr[i - 1];
      }
      outputSArr[0] = "S(" + std::to_string(index) + "): " + u32ToHexStr(SPIout);
      outputRArr[0] = "R: " + u32ToHexStr(SPIin);

      // Cancel
      if ((keys & KEY_L) && (keys & KEY_R))
      {
        linkSPI->deactivate();
        return 0;
      }
    }

    // Print
    VBlankIntrWait();
    output = "";
    for (int i = 0; i < 16; i++)
    {
      output += (outputSArr[i] + " " + outputRArr[i] + "\n");
    }
    if (mode == 1){
      bigOut = bigOut + u32ToHexStr(SPIin);
      log(bigOut);
    } else {
      log(output);
    }
  }

  return 0;
}

void log(std::string text)
{
  tte_erase_screen();
  tte_write("#{P:0,0}");
  tte_write(text.c_str());
}

void wait(u32 verticalLines)
{
  u32 count = 0;
  u32 vCount = REG_VCOUNT;

  while (count < verticalLines)
  {
    if (REG_VCOUNT != vCount)
    {
      count++;
      vCount = REG_VCOUNT;
    }
  };
}
