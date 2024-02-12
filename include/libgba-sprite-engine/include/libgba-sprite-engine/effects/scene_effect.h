//
// Created by Wouter Groeneveld on 04/08/18.
//

#ifndef GBA_SPRITE_ENGINE_SCENE_EFFECT_H
#define GBA_SPRITE_ENGINE_SCENE_EFFECT_H

#pragma GCC system_header

#include <libgba-sprite-engine/scene.h>

class SceneEffect {
 protected:
  // WHY no reference? Scene& operator= is implicitly deleted and no intentions
  // to use that
  Scene* sceneToAffect;

 public:
  void setSceneToAffect(Scene* scene) { sceneToAffect = scene; };

  virtual void update() = 0;
  virtual bool isDone() = 0;
};

#endif  // GBA_SPRITE_ENGINE_SCENE_EFFECT_H
