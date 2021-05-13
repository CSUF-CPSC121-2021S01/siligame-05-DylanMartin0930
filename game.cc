#include "game.h"

#include <iostream>
#include <vector>

void Game::UpdateScreen() {
  gamescreen_.DrawRectangle(0, 0, gamescreen_.GetWidth(),
                            gamescreen_.GetHeight(),
                            graphics::Color(255, 255, 255));

  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive() == true) {
      opponents_[i]->Draw(gamescreen_);
    }
  }

  for (int i = 0; i < opponentprojectiles_.size(); i++) {
    if (opponentprojectiles_[i]->GetIsActive() == true) {
      opponentprojectiles_[i]->Draw(gamescreen_);
    }
  }
  for (int i = 0; i < playerprojectiles_.size(); i++) {
    if (playerprojectiles_[i]->GetIsActive() == true) {
      playerprojectiles_[i]->Draw(gamescreen_);
    }
  }
  if (player_.GetIsActive() == true) {
    player_.Draw(gamescreen_);
  } else {
    gamescreen_.DrawText(400, 300, "GAME OVER", 80, graphics::Color(0, 0, 0));
  }
  std::string playerScoreText = "Score: ";
  playerScoreText += std::to_string(playerScore);
  gamescreen_.DrawText(0, 0, playerScoreText, 50, graphics::Color(0, 0, 0));
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponents_.size(); i++) {
    if (opponents_[i]->GetIsActive() == true) {
      opponents_[i]->Move(gamescreen_);
    }
  }
  for (int j = 0; j < opponentprojectiles_.size(); j++) {
    if (opponentprojectiles_[j]->GetIsActive() == true) {
      opponentprojectiles_[j]->Move(gamescreen_);
    }
  }
  for (int f = 0; f < playerprojectiles_.size(); f++) {
    if (playerprojectiles_[f]->GetIsActive() == true) {
      playerprojectiles_[f]->Move(gamescreen_);
    }
  }
}

void Game::FilterIntersections() {
  // if player intersect with opponent
  for (int i = 0; i < opponents_.size(); i++) {
    if (player_.IntersectsWith(opponents_[i].get()) == true) {
      player_.SetIsActive(false);
      isPlaying = false;
      opponents_[i]->SetIsActive(false);
    }
  }
  // check if a player projectile intersects with opponent
  for (int k = 0; k < opponents_.size(); k++) {
    for (int p = 0; p < playerprojectiles_.size(); p++) {
      if (playerprojectiles_[p]->IntersectsWith(opponents_[k].get()) == true) {
        playerprojectiles_[p]->SetIsActive(false);
        opponents_[k]->SetIsActive(false);
        if (player_.GetIsActive()) {
          playerScore = playerScore + 1;
        }
      }
    }
  }
  // check each opponent projectile intersects with player
  for (int j = 0; j < opponentprojectiles_.size(); j++) {
    if (player_.IntersectsWith(opponentprojectiles_[j].get()) == true) {
      player_.SetIsActive(false);
      isPlaying = false;
      opponentprojectiles_[j]->SetIsActive(false);
    }
  }
}

void Game::OnAnimationStep() {
  if (opponents_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();

  gamescreen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &object) {
  if (object.GetMouseAction() == graphics::MouseAction::kMoved ||
      object.GetMouseAction() == graphics::MouseAction::kDragged) {
    int oldPositionX = player_.GetX();
    int oldPositionY = player_.GetY();

    player_.SetX(object.GetX() - player_.GetWidth() / 2);
    player_.SetY(object.GetY() - player_.GetHeight() / 2);

    if (player_.GetX() + player_.GetWidth() > width_ || player_.GetX() <= 0) {
      player_.SetX(oldPositionX);
      player_.SetY(oldPositionY);
    }
    if (player_.GetY() + player_.GetHeight() > height_ || player_.GetY() <= 0) {
      player_.SetX(oldPositionX);
      player_.SetY(oldPositionY);
    }
  }
  if (object.GetMouseAction() == graphics::MouseAction::kPressed ||
      object.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> projectile =
        std::make_unique<PlayerProjectile>(player_.GetX(), player_.GetY());
    playerprojectiles_.push_back(std::move(projectile));
  }
}

void Game::LaunchProjectiles() {
  std::unique_ptr<OpponentProjectile> holder;
  for (int i = 0; i < opponents_.size(); i++) {
    holder = opponents_[i]->LaunchProjectile();
    if (holder != nullptr) {
      opponentprojectiles_.push_back(std::move(holder));
    }
  }
}

void Game::RemoveInactive() {
  for (int i = opponents_.size() - 1; i >= 0; i--) {
    if (opponents_[i]->GetIsActive() == false) {
      opponents_.erase(opponents_.begin() + i);
    }
  }
  for (int i = opponentprojectiles_.size() - 1; i >= 0; i--) {
    if (opponentprojectiles_[i]->GetIsActive() == false) {
      opponentprojectiles_.erase(opponentprojectiles_.begin() + i);
    }
  }
  for (int i = playerprojectiles_.size() - 1; i >= 0; i--) {
    if (playerprojectiles_[i]->GetIsActive() == false) {
      playerprojectiles_.erase(playerprojectiles_.begin() + i);
    }
  }
}
