#include <iostream>

#include "cpputils/graphics/image.h"

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

class GameElement {
 public:
  // constructors
  GameElement() : x_(0), y_(0), width_(50), height_(50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  // accessors & mutators
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }

  int GetX() const { return x_; }
  int GetY() const { return y_; }

  int GetWidth() { return width_; }
  int GetHeight() { return height_; }

  void SetIsActive(bool status) { is_active = status; }
  bool GetIsActive() { return is_active; }

  // member functions
  virtual void Draw(graphics::Image &rectangle) = 0;
  virtual void Move(const graphics::Image &character) = 0;
  bool IntersectsWith(GameElement *object);
  bool IsOutOfBounds(const graphics::Image &object);

 protected:
  int x_;
  int y_;
  const int width_;
  const int height_;
  bool is_active = true;
};
#endif
