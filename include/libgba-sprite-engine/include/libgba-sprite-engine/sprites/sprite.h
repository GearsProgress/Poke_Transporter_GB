//
// Created by Wouter Groeneveld on 26/07/18.
//

#ifndef GBA_SPRITE_ENGINE_SPRITE_H
#define GBA_SPRITE_ENGINE_SPRITE_H

#pragma GCC system_header

// inline-functions---
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#define GBA_SCREEN_WIDTH 240
#define GBA_SCREEN_HEIGHT 160
// -------------------

#include <libgba-sprite-engine/gba/tonc_types.h>

#include <memory>
#ifdef CODE_COMPILED_AS_PART_OF_TEST
#include <libgba-sprite-engine/gba/tonc_math_stub.h>
#else
#include <libgba-sprite-engine/gba/tonc_math.h>
#endif

#define COLOR_MODE_16 0
#define COLOR_MODE_256 1
#define GFX_MODE 0
#define MOSAIC_MODE 1
#define AFFINE_FLAG_NONE_SET_YET 0

#define FLIP_VERTICAL_CLEAR 0xdfff
#define FLIP_HORIZONTAL_CLEAR 0xefff
#define OAM_TILE_OFFSET_CLEAR 0xfc00
#define OAM_TILE_OFFSET_NEW 0x03ff

enum SpriteSize {
  SIZE_8_8,
  SIZE_16_16,
  SIZE_32_32,
  SIZE_64_64,
  SIZE_16_8,
  SIZE_32_8,
  SIZE_32_16,
  SIZE_64_32,
  SIZE_8_16,
  SIZE_8_32,
  SIZE_16_32,
  SIZE_32_64
};

class SpriteManager;

class Sprite {
 private:
  inline void updateAnimation();
  inline void syncPosition();

 protected:
  const void* data;
  int x, y;
  u8 animation_offset;
  u32 priority, w, h, size_bits, shape_bits;
  u32 imageSize, tileIndex;
  SpriteSize spriteSize;
  u8 animationDelay, numberOfFrames, beginFrame, currentFrame, previousFrame,
      animationCounter;
  bool animating;

  inline void syncAnimation();
  inline void syncOam();
  inline void buildOam(int tileIndex);
  inline void setAttributesBasedOnSize(SpriteSize size);

 public:
  OBJ_ATTR oam;
  bool enabled = true;
  explicit Sprite(const Sprite& other);
  explicit Sprite(const void* imageData,
                  int imageSize,
                  int x,
                  int y,
                  SpriteSize size);
  virtual ~Sprite() {}

  inline const void* getData() { return data; }
  inline void setData(void* newData) { data = newData; }
  inline u32 getImageSize() { return imageSize; }
  inline void setImageSize(u32 size) { imageSize = size; }

  inline void setPriority(u32 priority) { this->priority = priority; }
  inline void makeAnimated(int beginFrame,
                           int numberOfFrames,
                           int animationDelay);
  inline void setBeginFrame(int frame) { this->beginFrame = frame; }
  inline void animateToFrame(int frame) { this->currentFrame = frame; }
  inline void animate() { this->animating = true; }
  inline void stopAnimating() { this->animating = false; }
  inline void update();

  inline void moveTo(int x, int y);
  inline bool collidesWith(Sprite& s2);

  inline void flipVertically(bool flip);
  inline void flipHorizontally(bool flip);

  inline u32 getTileIndex() { return tileIndex; }
  inline int getX() { return x; }
  inline int getY() { return y; }
  inline u32 getWidth() { return w; }
  inline u32 getHeight() { return h; }
  inline u32 getAnimationDelay() { return animationDelay; }
  inline u32 getNumberOfFrames() { return numberOfFrames; }
  inline u32 getCurrentFrame() { return currentFrame; }
  inline bool isAnimating() { return animating; };
  inline bool isOffScreen();

  friend class SpriteManager;
};

inline void Sprite::moveTo(int x, int y) {
  this->x = x;
  this->y = y;
}

inline bool Sprite::isOffScreen() {
  return x < 0 || x > GBA_SCREEN_WIDTH || y < 0 || y > GBA_SCREEN_HEIGHT;
}

inline void Sprite::flipHorizontally(bool flip) {
  if (flip) {
    oam.attr1 |= ATTR1_HFLIP;
  } else {
    oam.attr1 &= FLIP_HORIZONTAL_CLEAR;
  }
}

inline void Sprite::flipVertically(bool flip) {
  if (flip) {
    oam.attr1 |= ATTR1_VFLIP;
  } else {
    oam.attr1 &= FLIP_VERTICAL_CLEAR;
  }
}

inline void Sprite::makeAnimated(int beginFrame,
                                 int numberOfFrames,
                                 int animationDelay) {
  previousFrame = -1;
  setBeginFrame(beginFrame);
  animateToFrame(beginFrame);
  this->numberOfFrames = numberOfFrames;
  this->animationDelay = animationDelay;
  animate();
}

inline void Sprite::syncPosition() {
  oam.attr0 = (oam.attr0 & ~ATTR0_Y_MASK) | (y & ATTR0_Y_MASK);
  oam.attr1 = (oam.attr1 & ~ATTR1_X_MASK) | (x & ATTR1_X_MASK);
  oam.attr2 =
      (oam.attr2 & ~ATTR2_PRIO_MASK) | (ATTR2_PRIO(priority) & ATTR2_PRIO_MASK);
}

inline void Sprite::syncAnimation() {
  if (previousFrame == currentFrame)
    return;

  int newTileIndex =
      this->tileIndex + (currentFrame * (this->animation_offset * 2));
  oam.attr2 &= OAM_TILE_OFFSET_CLEAR;
  oam.attr2 |= (newTileIndex & OAM_TILE_OFFSET_NEW);

  previousFrame = currentFrame;
}

inline void Sprite::syncOam() {
  syncPosition();
  syncAnimation();
}

inline void Sprite::updateAnimation() {
  if (!animating)
    return;

  animationCounter++;
  if (animationCounter > animationDelay) {
    currentFrame++;
    if (currentFrame > (numberOfFrames - 1) + beginFrame) {
      currentFrame = beginFrame;
    }
    if (currentFrame < beginFrame) {
      currentFrame = beginFrame;
    }

    animationCounter = 0;
  }
}

inline void Sprite::update() {
  updateAnimation();
  syncOam();
}

inline void Sprite::setAttributesBasedOnSize(SpriteSize size) {
  switch (size) {
    case SIZE_8_8:
      size_bits = 0;
      shape_bits = 0;
      w = 8;
      h = 8;
      animation_offset = 1;
      break;
    case SIZE_16_16:
      size_bits = 1;
      shape_bits = 0;
      w = 16;
      h = 16;
      animation_offset = 4;
      break;
    case SIZE_32_32:
      size_bits = 2;
      shape_bits = 0;
      w = 32;
      h = 32;
      animation_offset = 16;
      break;
    case SIZE_64_64:
      size_bits = 3;
      shape_bits = 0;
      w = 64;
      h = 64;
      animation_offset = 64;
      break;
    case SIZE_16_8:
      size_bits = 0;
      shape_bits = 1;
      w = 16;
      h = 8;
      animation_offset = 2;
      break;
    case SIZE_32_8:
      size_bits = 1;
      shape_bits = 1;
      w = 32;
      h = 8;
      animation_offset = 4;
      break;
    case SIZE_32_16:
      size_bits = 2;
      shape_bits = 1;
      w = 32;
      h = 16;
      animation_offset = 8;
      break;
    case SIZE_64_32:
      size_bits = 3;
      shape_bits = 1;
      w = 64;
      h = 32;
      animation_offset = 32;
      break;
    case SIZE_8_16:
      size_bits = 0;
      shape_bits = 2;
      w = 8;
      h = 16;
      animation_offset = 2;
      break;
    case SIZE_8_32:
      size_bits = 1;
      shape_bits = 2;
      w = 8;
      h = 32;
      animation_offset = 4;
      break;
    case SIZE_16_32:
      size_bits = 2;
      shape_bits = 2;
      w = 16;
      h = 32;
      animation_offset = 8;
      break;
    case SIZE_32_64:
      size_bits = 3;
      shape_bits = 2;
      w = 32;
      h = 64;
      animation_offset = 32;
      break;
  }
}

inline bool Sprite::collidesWith(Sprite& s2) {
  const Sprite& s1 = *this;

  if (s1.x < s2.x + s2.w && s1.x + s1.w > s2.x && s1.y < s2.y + s2.h &&
      s1.h + s1.y > s2.y) {
    return true;
  }
  return false;
}

inline void Sprite::buildOam(int tileIndex) {
  this->tileIndex = tileIndex;

  oam.attr0 = ATTR0_Y(this->y & 0x00FF) | ATTR0_MODE(0) | (GFX_MODE << 10) |
              (MOSAIC_MODE << 12) | (COLOR_MODE_256 << 13) |
              (this->shape_bits << 14);
  oam.attr1 = (this->x & 0x01FF) | (AFFINE_FLAG_NONE_SET_YET << 9) |
              (((oam.attr1 & ATTR1_HFLIP) != 0) << 12) |
              (((oam.attr1 & ATTR1_VFLIP) != 0) << 13) |
              (this->size_bits << 14);

  oam.attr2 = ATTR2_ID(tileIndex) | ATTR2_PRIO(priority) | ATTR2_PALBANK(0);
}

#endif  // GBA_SPRITE_ENGINE_SPRITE_H
