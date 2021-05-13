#include <iostream>
#include <vector>

#include "cpputils/graphics/image.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H



class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  // constructors
  Game() : Game(800, 600) {}
  Game(int width, int height)
      : width_(width), height_(height), gamescreen_(width, height) {}
  // accessors
  graphics::Image &GetGameScreen() { return gamescreen_; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponents_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponentprojectiles_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return playerprojectiles_;
  }
  Player &GetPlayer() { return player_; }

  int GetScore() { return playerScore; }
  bool HasLost() { return !isPlaying; } 

  // member functions
  void CreateOpponents() {
    std::unique_ptr<Opponent> enemy = std::make_unique<Opponent>();
    enemy->SetX(400);
    enemy->SetY(300);
    opponents_.push_back(std::move(enemy));
  }

  /*void CreateOpponentProjectiles() {
    std::unique_ptr<OpponentProjectile> oProjectile = std::make_unique<OpponentProjectile>();
    opponentprojectiles_.push_back(std::move(oProjectile));
  }

  void CreatePlayerProjectiles() {
    std::unique_ptr<PlayerProjectile> pProjectile = std::make_unique<PlayerProjectile>();
    playerprojectiles_.push_back(std::move(pProjectile));
  }
  */

  void Init() {
    player_.SetX(400);
    player_.SetY(500);

    /*CreateOpponents();
    CreateOpponentProjectiles();
    CreatePlayerProjectiles();*/

    gamescreen_.AddMouseEventListener(*this);
    gamescreen_.AddAnimationEventListener(*this);
  }

  void UpdateScreen();

  void Start() { gamescreen_.ShowUntilClosed(); }

  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent &object) override;

  void LaunchProjectiles();
  void RemoveInactive();

 private:
   int playerScore =0;
   bool isPlaying = true;

  int width_;
  int height_;
  graphics::Image gamescreen_;
  std::vector<std::unique_ptr<Opponent>> opponents_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponentprojectiles_;
  std::vector<std::unique_ptr<PlayerProjectile>> playerprojectiles_;
  Player player_;
};


#endif
