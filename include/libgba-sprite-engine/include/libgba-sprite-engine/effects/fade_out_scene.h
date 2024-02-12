//
// Created by Wouter Groeneveld on 04/08/18.
//

#ifndef GBA_SPRITE_ENGINE_FADE_OUT_SCENE_H
#define GBA_SPRITE_ENGINE_FADE_OUT_SCENE_H

#pragma GCC system_header

#include <libgba-sprite-engine/scene.h>

#include "scene_effect.h"

enum FadeOutType { ToWhite, ToBlack };

class FadeOutScene : public SceneEffect {
 private:
  FadeOutType type;
  int timesUpdated;
  int speed;
  std::unique_ptr<CombinedPalette> palette;

 public:
  FadeOutScene(int speed);
  FadeOutScene(int speed, FadeOutType type);
  void update() override;
  bool isDone() override { return timesUpdated >= (32 / speed); }
};

#endif  // GBA_SPRITE_ENGINE_FADE_OUT_SCENE_H
