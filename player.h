#include <iostream>

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player() {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}

  // getters for Width and height
  int GetWidth() { return kWidth_; }
  int GetHeight() { return kHeight_; }

  // draw function
  void Draw(graphics::Image &gameCanvas);
  void Move(const graphics::Image &character) {}

  // intersect with opponent

 private:
  const int kWidth_ = 50;
  const int kHeight_ = 50;
};

// PLAYER PROJECTILE
class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  int GetWidth() { return kWidth_; }
  int GetHeight() { return kHeight_; }

  // draw function
  void Draw(graphics::Image &gameCanvas);
  // intersect with opponent
  void Move(const graphics::Image &character);

 private:
  const int kWidth_ = 5;
  const int kHeight_ = 5;
};
#endif
