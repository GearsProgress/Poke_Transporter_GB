//
// Created by Wouter Groeneveld on 05/08/18.
//

#ifndef GBA_SPRITE_ENGINE_COMBINED_PALETTE_H
#define GBA_SPRITE_ENGINE_COMBINED_PALETTE_H

#pragma GCC system_header

class PaletteManager;

class CombinedPalette {
 private:
  // WHY use references here? lifetimes not bound, not owned by CombinedPalette
  PaletteManager& palette1;
  PaletteManager& palette2;

  void changeBrightness(PaletteManager& palette,
                        int bank,
                        int index,
                        int intensity);

 public:
  CombinedPalette(PaletteManager& one, PaletteManager& two)
      : palette1(one), palette2(two) {}
  CombinedPalette(const CombinedPalette& other) = delete;

  void changeBrightness(int intensity);
};

#endif  // GBA_SPRITE_ENGINE_COMBINED_PALETTE_H
