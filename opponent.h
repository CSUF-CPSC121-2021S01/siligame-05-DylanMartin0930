#include <cstdlib>
#include <iostream>
#include <memory>

#include "cpputils/graphics/image.h"
#include "game_element.h"

#ifndef OPPONENT_H
#define OPPONENT_H

class Opponent : public GameElement {
 public:
  Opponent() {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  // getters for widght and height
  int GetWidth() const { return kWidth_; }
  int GetHeight() const { return kHeight_; }

  // draw function
  void Draw(graphics::Image &gameCanvas);
  void Move(const graphics::Image &character);

  // Launching projecctile
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();

 private:
  const int kWidth_ = 50;
  const int kHeight_ = 50;
  int counter = 0;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  // getters for width and height
  int GetWidth() { return kWidth_; }
  int GetHeight() { return kHeight_; }
  // draw function
  void Draw(graphics::Image &gameCanvas);
  void Move(const graphics::Image &object);

 private:
  const int kWidth_ = 5;
  const int kHeight_ = 5;
};

#endif
