#include "game.h"

#include <iostream>

#include "cpputils/graphics/image.h"
//#include "cpputils/graphics/image_mouse_event.h"

Game::Game() {
  game_screen_.Initialize(800, 600);
  score_ = 0;
  lost_ = false;
}
Game::Game(int width, int height) { game_screen_.Initialize(width, height); }

graphics::Image& Game::GetGameScreen() { return game_screen_; }
std::vector<std::unique_ptr<Opponent>>& Game::GetOpponents() {
  return game_opponents_;
}
std::vector<std::unique_ptr<OpponentProjectile>>&
Game::GetOpponentProjectiles() {
  return opponent_projectiles_;
}
std::vector<std::unique_ptr<PlayerProjectile>>& Game::GetPlayerProjectiles() {
  return player_projectiles_;
}
Player& Game::GetPlayer() { return game_player_; }

void Game::CreateOpponents() {
  int x = 200;
  int y = 50;

  std::unique_ptr<Opponent> rmd_opponent = std::make_unique<Opponent>(x, y);
  game_opponents_.push_back(std::move(rmd_opponent));
}

/*void Game::CreateOpponentProjectiles() {
  OpponentProjectile rmd_opponentpro(200, 100);
  opponent_projectiles_.push_back(rmd_opponentpro);
}

void Game::CreatePlayerProjectiles() {
  PlayerProjectile rmd_playerpro(250, 300);
  player_projectiles_.push_back(rmd_playerpro);
}*/

void Game::Init() {
  game_player_.SetX(50);
  game_player_.SetY(50);
  game_screen_.AddMouseEventListener(*this);
  game_screen_.AddAnimationEventListener(*this);
  CreateOpponents();
  // CreateOpponentProjectiles();
  // CreatePlayerProjectiles();
}

void Game::UpdateScreen() {
  game_screen_.DrawRectangle(0, 0, game_screen_.GetWidth(),
                             game_screen_.GetHeight(), 0, 0, 0);
  game_player_.Draw(game_screen_);

  std::string message = "SCORE: " + std::to_string(score_);
  game_screen_.DrawText(1, 1, message, 30, 255, 255, 255);

  for (int i = 0; i < player_projectiles_.size(); i++) {
    player_projectiles_[i]->Draw(game_screen_);
  }
  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    opponent_projectiles_[i]->Draw(game_screen_);
  }
  for (int i = 0; i < game_opponents_.size(); i++) {
    game_opponents_[i]->Draw(game_screen_);
  }
  if (HasLost()) {
    std::string game_over = "GAME OVER";
    game_screen_.DrawText(300, 300, game_over, 50, 255, 255, 255);
  }
}

void Game::Start() { game_screen_.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < game_opponents_.size(); i++) {
    if (game_opponents_[i]->GetIsActive() == true) {
      game_opponents_[i]->Move(game_screen_);
    }
  }

  for (int i = 0; i < opponent_projectiles_.size(); i++) {
    if (opponent_projectiles_[i]->GetIsActive() == true) {
      opponent_projectiles_[i]->Move(game_screen_);
    }
  }

  for (int i = 0; i < player_projectiles_.size(); i++) {
    if (player_projectiles_[i]->GetIsActive() == true) {
      player_projectiles_[i]->Move(game_screen_);
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < game_opponents_.size(); i++) {
    if (game_opponents_[i]->IntersectsWith(&game_player_) &&
        game_opponents_[i]->GetIsActive() && game_player_.GetIsActive()) {
      lost_ = true;
      game_player_.SetIsActive(false);
      game_opponents_[i]->SetIsActive(false);
    }
    for (int j = 0; j < player_projectiles_.size(); j++) {
      if (player_projectiles_[j]->IntersectsWith(game_opponents_[j].get()) &&
          player_projectiles_[j]->GetIsActive() &&
          game_opponents_[i]->GetIsActive()) {
        player_projectiles_[j]->SetIsActive(false);
        game_opponents_[i]->SetIsActive(false);
      }
      if (game_player_.GetIsActive() &&
          player_projectiles_[j]->IntersectsWith(game_opponents_[i].get())) {
        score_++;
      }
    }

    for (int i = 0; i < opponent_projectiles_.size(); i++) {
      if (opponent_projectiles_[i]->IntersectsWith(&game_player_) &&
          opponent_projectiles_[i]->GetIsActive() &&
          game_player_.GetIsActive()) {
        opponent_projectiles_[i]->SetIsActive(false);
        game_player_.SetIsActive(false);
        lost_ = true;
      }
    }
  }
}

void Game::OnAnimationStep() {
  if (game_opponents_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  game_screen_.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent& mouse_event) {
  if ((mouse_event.GetMouseAction() == graphics::MouseAction::kMoved ||
       mouse_event.GetMouseAction() == graphics::MouseAction::kDragged) &&
      (mouse_event.GetX() > 0 &&
       mouse_event.GetX() < game_screen_.GetWidth()) &&
      (mouse_event.GetY() > 0 &&
       mouse_event.GetY() < game_screen_.GetHeight())) {
    game_player_.SetX(mouse_event.GetX() - game_player_.GetWidth() / 2);
    game_player_.SetY(mouse_event.GetY() - game_player_.GetWidth() / 2);
  }
  if (mouse_event.GetMouseAction() == graphics::MouseAction::kDragged ||
      mouse_event.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> player_projectiles_ptr =
        std::make_unique<PlayerProjectile>(mouse_event.GetX(),
                                           mouse_event.GetY());
    player_projectiles_.push_back(std::move(player_projectiles_ptr));
  }

  if (HasLost() &&
      mouse_event.GetMouseAction() == graphics::MouseAction::kPressed) {
    Game Game1;
    Game1.Init();
    Game1.UpdateScreen();
    Game1.Start();
  }
}

int Game::GetScore() const { return score_; }
bool Game::HasLost() { return lost_; }

void Game::LaunchProjectiles() {
  for (int i = 0; i < game_opponents_.size(); i++) {
    if (game_opponents_[i]->GetIsActive()) {
      std::unique_ptr<OpponentProjectile> Opponent_unique_ptr;
      Opponent_unique_ptr = game_opponents_[i]->LaunchProjectile();
      if (Opponent_unique_ptr != nullptr) {
        opponent_projectiles_.push_back(std::move(Opponent_unique_ptr));
      }
    }
  }
}

void Game::RemoveInactive() {
  for (int i = game_opponents_.size() - 1; i >= 0; i--) {
    if (game_opponents_[i]->GetIsActive() == false) {
      game_opponents_.erase(game_opponents_.end() -
                            (game_opponents_.size() - i));
    }
  }
  for (int i = opponent_projectiles_.size() - 1; i >= 0; i--) {
    if (opponent_projectiles_[i]->GetIsActive() == false) {
      opponent_projectiles_.erase(opponent_projectiles_.end() -
                                  (opponent_projectiles_.size() - i));
    }
  }
  for (int i = player_projectiles_.size() - 1; i >= 0; i--) {
    if (player_projectiles_[i]->GetIsActive() == false) {
      player_projectiles_.erase(player_projectiles_.end() -
                                (player_projectiles_.size() - i));
    }
  }
}
