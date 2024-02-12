//
// Created by Wouter Groeneveld on 28/07/18.
//

#ifndef GBA_SPRITE_ENGINE_GBAENGINE_H
#define GBA_SPRITE_ENGINE_GBAENGINE_H

#pragma GCC system_header

#include <libgba-sprite-engine/effects/scene_effect.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/sprites/sprite_manager.h>

#include "scene.h"

#define GBA_SCREEN_WIDTH 240
#define GBA_SCREEN_HEIGHT 160

class GBAEngine {
 private:
  // WHY raw pointers? the engine does the transition and cleanup work itself
  Scene* currentScene;
  Scene* sceneToTransitionTo;
  SceneEffect* currentEffectForTransition;

  bool disableTextBg;
  SpriteManager spriteManager;

  void cleanupPreviousScene();

 public:
  GBAEngine();

  void setScene(Scene* scene);
  void dynamicallyAddSprite(Sprite* s) { spriteManager.add(s); }
  void transitionIntoScene(Scene* scene, SceneEffect* effect);
  bool isTransitioning() { return currentEffectForTransition != nullptr; }
  void disableText() { this->disableTextBg = true; }
  void enableText() { this->disableTextBg = false; }

  u16 readKeys();

  inline void update() {
    // main update loop, in while(true) {}.
    // WARNING - keep amount of instructions as minimal as possible in here!

    if (sceneToTransitionTo) {
      currentEffectForTransition->update();

      if (currentEffectForTransition->isDone()) {
        setScene(sceneToTransitionTo);
      }
    }

    u16 keys = readKeys();

    // Main scene update loop call. This *might* take a while.
    currentScene->tick(keys);

    // You should handle vsync externally.

    spriteManager.render();
  }

  void updateSpritesInScene();
  void delay(int times) {
    for (int i = 0; i < times; i++) {
    }
  }
};

#endif  // GBA_SPRITE_ENGINE_GBAENGINE_H
