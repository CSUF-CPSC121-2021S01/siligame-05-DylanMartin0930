#include "game_element.h"

#include <iostream>

#include "cpputils/graphics/image.h"

bool GameElement::IntersectsWith(GameElement *object) {
  return !(GetX() > object->GetX() + object->GetWidth() ||
           object->GetX() > GetX() + GetWidth() ||
           GetY() > object->GetY() + object->GetHeight() ||
           object->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image &object) {
  // TO DO;
  //--canvas corners --
  // top left corner x ==0 y ==0
  // top right corner x == 800 y == 0
  // bottm left corner x == 0 y == 600
  // bottom right corner x == 800 y == 800
  return !(GetX() >= 0 && object.GetWidth() > GetX() + GetWidth() &&
           GetY() >= 0 && object.GetHeight() > GetY() + GetHeight());
}
// check if x y < 0
//
