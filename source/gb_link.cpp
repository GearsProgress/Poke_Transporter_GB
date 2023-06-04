#include <string>
#include <tonc.h>

#include "gb_link.h"
#include "interrupt.h"
#include "LinkSPI.h"
#include "debug.h"
#include "sio.h"

// (1) Create a LinkSPI instance
LinkSPI *linkSPI = new LinkSPI();

vu32 trainerData[111] = {0x8A918892, 0x50505050, 0x50505006, 0x9B9B9B9B, 0x9B9BFF25, 0xDA9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A9B0021, 0x2B000025, 0xDA000087, 0x00000000, 0x00000000, 0x00007221, 0x231E0000, 0x46008581, 0x05000000, 0x13001300, 0x0A000900, 0x0B000B00, 0x0A8A9188, 0x92505050, 0x50505050, 0x8A918892, 0x50505050, 0x5050508A, 0x91889250, 0x50505050, 0x50508A91, 0x88925050, 0x50505050, 0x508A9188, 0x92505050, 0x50505050, 0x8A918892, 0x50505050, 0x50505082, 0x988D8380, 0x9094888B, 0x50508298, 0x8D838090, 0x94888B50, 0x5082988D, 0x83809094, 0x888B5050, 0x82988D83, 0x80909488, 0x8B505082, 0x988D8380, 0x9094888B, 0x50508298, 0x8D838090, 0x94888B50, 0x50000000};

void init()
{
  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
  tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));

  // (2) Add the interrupt service routines
  //interrupt_init();
  //interrupt_set_handler(INTR_VBLANK, VBLANK);
  //interrupt_enable(INTR_VBLANK);
  //interrupt_set_handler(INTR_SERIAL, LINK_SPI_ISR_SERIAL);
  //interrupt_enable(INTR_SERIAL);
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

  u8 SPIout = 0x00; // What the GBA is sending out to the GBC
  u8 SPIin = 0x00;  // What the GBA is receiving from the GBC
  std::string outputArr[16] = {};
  u32 mode = 0; // Trick game into entering trading room
  bool firstTransfer = false;
  u32 index = 0;
  std::string bigOut = "";
  // connection_state linkCable = POST_SAVE;

  connection_state_t connection_state = NOT_CONNECTED;
  trade_centre_state_gen_II_t trade_centre_state_gen_II = INIT;
  int counter = 0;
  byte in;
  byte send = 0x16;
  const int MODE = 1; // mode=0 will transfer pokemon data from pokemon.h
int trade_pokemon = -1;

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

      // (4)/(5) Exchange 8-bit data with the other end
      /*SPIin = linkSPI->transfer(SPIout, []()
                                {
        bool exit = false;
          u16 keys = ~REG_KEYS & KEY_ANY;
          if ((keys & KEY_L) && (keys & KEY_R)){
            exit = true;
          }
          return exit; });
      */
      // - - - - - - - - - - - - -

      in = SPIin;

      byte send = 0x07;

  switch(connection_state) {
  case NOT_CONNECTED:
    if(in == PKMN_MASTER)
      send = PKMN_SLAVE;
    else if(in == PKMN_BLANK)
      send = PKMN_BLANK;
    else if(in == PKMN_CONNECTED_II) {
      send = PKMN_CONNECTED_II;
      connection_state = CONNECTED;
    }
    break;

  case CONNECTED:
    if(in == PKMN_CONNECTED_II)   //acknowledge connection
      send = PKMN_CONNECTED_II;
    else if(in == GEN_II_CABLE_TRADE_CENTER){   //acknowledge trade center selection
      connection_state = TRADE_CENTRE;
      send = GEN_II_CABLE_TRADE_CENTER;
    }
    else if(in == GEN_II_CABLE_CLUB_COLOSSEUM){   //acknowledge colosseum selection
      connection_state = COLOSSEUM;
      send = GEN_II_CABLE_CLUB_COLOSSEUM;
    }
    else {
      send = in;
    }
    break;

  case TRADE_CENTRE:
    if(trade_centre_state_gen_II == INIT && in == 0x00) {
        trade_centre_state_gen_II = READY_TO_GO;
        send = 0x00;
    } else if(trade_centre_state_gen_II == READY_TO_GO && in == 0xFD) {
        trade_centre_state_gen_II = SEEN_FIRST_WAIT;
        send = 0xFD;
    } else if(trade_centre_state_gen_II == SEEN_FIRST_WAIT && in != 0x70) {
        // random data of slave is ignored.
        send = in;
        trade_centre_state_gen_II = SENDING_RANDOM_DATA;
    } else if(trade_centre_state_gen_II == SENDING_RANDOM_DATA && in == 0xFD) {
        trade_centre_state_gen_II = WAITING_TO_SEND_DATA;
        send = 0xFD;
    } else if(trade_centre_state_gen_II == WAITING_TO_SEND_DATA && in != 0xFD) {
        counter = 0;
        // send first byte
        switch(MODE){
          case 0:
            //send = pgm_read_byte(&(DATA_BLOCK_GEN_II[counter]));
            //INPUT_BLOCK_GEN_II[counter] = in;
            break;
          case 1:
            send = in;
            break;
          default:
            send = in;
            break;
        }
        counter++;
        trade_centre_state_gen_II = SENDING_DATA;
    } else if(trade_centre_state_gen_II == SENDING_DATA) {
        switch(MODE){
          case 0:
            //send = pgm_read_byte(&(DATA_BLOCK_GEN_II[counter]));
            //INPUT_BLOCK_GEN_II[counter] = in;
            break;
          case 1:
            send = in;
            break;
          default:
            send = in;
            break;
        }
        counter++;
        if(counter == PLAYER_LENGTH_GEN_II) {
          trade_centre_state_gen_II = SENDING_PATCH_DATA;
        }
    } else if(trade_centre_state_gen_II == SENDING_PATCH_DATA && in == 0xFD) {
        counter = 0;
        send = 0xFD;
    } else if(trade_centre_state_gen_II == SENDING_PATCH_DATA && in != 0xFD) {
        send = in;
        trade_centre_state_gen_II = MIMIC;
    } else if(trade_centre_state_gen_II == MIMIC){
        send = in;




      
    } else if(trade_centre_state_gen_II == TRADE_PENDING && (in & 0x60) == 0x60) {
      if (in == 0x6f) {
        trade_centre_state_gen_II = READY_TO_GO;
        send = 0x6f;
      } else {
        send = 0x60; // first pokemon
        trade_pokemon = in - 0x60;
      }
    } else if(trade_centre_state_gen_II == TRADE_PENDING && in == 0x00) {
      send = 0;
      trade_centre_state_gen_II = TRADE_CONFIRMATION;
    } else if(trade_centre_state_gen_II == TRADE_CONFIRMATION && (in & 0x60) == 0x60) {
      send = in;
      if (in  == 0x61) {
        trade_pokemon = -1;
        trade_centre_state_gen_II = TRADE_PENDING;
      } else {
        trade_centre_state_gen_II = DONE;
      }
    } else if(trade_centre_state_gen_II == DONE && in == 0x00) {
      send = 0;
      trade_centre_state_gen_II = INIT;
    } else {
      send = in;
    }
    break;

  default:
    send = in;
    break;
  }

      SPIout = send;
      //SPIin = sio_send_master(0x75, SIO_8);

      for (int i = 7; i > 0; i--)
      {
        outputArr[i] = outputArr[i - 1];
      }
      outputArr[0] = "TS: " + std::to_string((int)trade_centre_state_gen_II) + " CS: " + std::to_string((int)connection_state) +
                     " OUT: " + u8ToHexStr(SPIout) + " IN: " + u8ToHexStr(SPIin);
                     

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
    
    for (int i = 0; i < 8; i++)
    {
      output += (outputArr[i] + "\n");
    }
    
   log(output);
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