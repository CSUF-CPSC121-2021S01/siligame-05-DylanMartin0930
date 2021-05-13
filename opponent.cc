#include "opponent.h"

#include <cstdlib>
#include <iostream>
#include <memory>

#include "cpputils/graphics/image.h"
#include "player.h"

void Opponent::Draw(graphics::Image &gameCanvas) {
  graphics::Image opponent;
  opponent.Load("enemysprite.bmp");

  // gets pixels of the enemy sprite image and puts them into the game canvas
  for (int i = 0; i < kWidth_; i++) {
    for (int j = 0; j < kHeight_; j++) {
      graphics::Color color = opponent.GetColor(i, j);

      gameCanvas.SetColor(GetX() + i, GetY() + j,
                          color);  // remember canvas size is 800x600 pixels
    }  // adding j and i puts the model at the top of the screen(?)
  }
}

// Launch projecile
std::unique_ptr<class OpponentProjectile> Opponent::LaunchProjectile() {
  std::unique_ptr<OpponentProjectile> projectile;

  if (counter < 5) {
    counter++;
    return nullptr;
  } else {
    projectile = std::make_unique<OpponentProjectile>(GetX(), GetY());
    counter = 0;
    return std::move(projectile);
  }
}

void OpponentProjectile::Draw(graphics::Image &gameCanvas) {
  graphics::Image opponentP;
  opponentP.Load("enemygun.bmp");

  for (int i = 0; i < kWidth_; i++) {
    for (int j = 0; j < kHeight_; j++) {
      graphics::Color color = opponentP.GetColor(i, j);

      gameCanvas.SetColor(
          GetX() + i, GetY() + j,
          color);  // adding j and i puts the model at the top of the screen(?)
    }
  }
}

void Opponent::Move(const graphics::Image &character) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(character)) {
    SetIsActive(false);
  }
}
void OpponentProjectile::Move(const graphics::Image &object) {
  SetY(GetY() + 3);
  if (IsOutOfBounds(object)) {
    SetIsActive(false);
  }
}
