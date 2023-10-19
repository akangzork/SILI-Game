#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>

#include "cpputils/graphics/image.h"
#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

class Game : public graphics::AnimationEventListener,
             graphics::MouseEventListener {
 public:
  Game();
  Game(int width, int height);

  graphics::Image& GetGameScreen();
  std::vector<std::unique_ptr<Opponent>>& GetOpponents();
  std::vector<std::unique_ptr<OpponentProjectile>>& GetOpponentProjectiles();
  std::vector<std::unique_ptr<PlayerProjectile>>& GetPlayerProjectiles();
  Player& GetPlayer();

  void MoveGameElements();
  void FilterIntersections();

  void CreateOpponents();
  // void CreateOpponentProjectiles();
  // void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start();

  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent& mouse_event) override;

  int GetScore() const;
  bool HasLost();
  void LaunchProjectiles();
  void RemoveInactive();

 private:
  graphics::Image game_screen_;
  std::vector<std::unique_ptr<Opponent>> game_opponents_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponent_projectiles_;
  std::vector<std::unique_ptr<PlayerProjectile>> player_projectiles_;
  Player game_player_;
  int score_ = 0;
  bool lost_ = false;
  int height_;
  int width_;
};

#endif
