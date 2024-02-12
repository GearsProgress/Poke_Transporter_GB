//
// Created by Wouter Groeneveld on 28/07/18.
//

#ifndef GBA_SPRITE_ENGINE_TEXT_STREAM_H
#define GBA_SPRITE_ENGINE_TEXT_STREAM_H

#pragma GCC system_header

#include <libgba-sprite-engine/palette/palette_manager.h>

#include <memory>
#include <string>

#include "background.h"
#include "text.h"

#define CHAR_OFFSET_INDEX 32
#define TILE_WIDTH 32
#define PALETTE_COLOR_INDEX 15
#define PALETTE_TEXT_BANK 15

#define failure_gba(__mess) \
  (consoleLog_func(__FILE__, __LINE__, __PRETTY_FUNCTION__, #__mess))
void log_text(const char* text);
void consoleLog_func(const char* fileName,
                     const int lineNr,
                     const char* fnName,
                     const char* msg);

class TextStream : public Background {
 private:
  int currRow, currCol;
  std::unique_ptr<BackgroundPaletteManager> palette;

  static TextStream* inst;
  TextStream();
  TextStream(TextStream& other) = delete;
  TextStream(TextStream&& other) = delete;

 public:
  void clear();
  void setText(std::string text, int row, int col);
  void setText(const char* text, int row, int col);

  void setFontColor(COLOR color);
  void setFontStyle(const void* data, int size);

  static TextStream& instance();

  void persist() override;

  TextStream& operator<<(const char* s);
  TextStream& operator<<(const int s);
  TextStream& operator<<(const u32 s);
  TextStream& operator<<(const bool s);
};

#endif  // GBA_SPRITE_ENGINE_TEXT_STREAM_H
