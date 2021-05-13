#include "player.h"

#include <iostream>

#include "cpputils/graphics/image.h"

void Player::Draw(graphics::Image &gameCanvas) {
  graphics::Image player;
  player.Load("playersprite.bmp");

  // gets pixels of the enemy sprite image and puts them into the game canvas
  for (int i = 0; i < kWidth_; i++) {
    for (int j = 0; j < kHeight_; j++) {
      graphics::Color color = player.GetColor(i, j);
      gameCanvas.SetColor(x_ + i, y_ + j, color);

      // remember canvas size is 800x600 pixels
    }
  }
}

// DRAW PROJECTILE
void PlayerProjectile::Draw(graphics::Image &gameCanvas) {
  graphics::Image playerProjectile;
  playerProjectile.Load("playergun.bmp");

  // gets pixels of the enemy sprite image and puts them into the game canvas
  for (int i = 0; i < kWidth_; i++) {
    for (int j = 0; j < kHeight_; j++) {
      graphics::Color color = playerProjectile.GetColor(i, j);
      gameCanvas.SetColor(x_ + i, y_ + j, color);

      // remember canvas size is 800x600 pixels
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &character) {
  SetY(GetY() - 3);
  if (IsOutOfBounds(character)) {
    SetIsActive(false);
  }
}
