#include "player.h"

#include <iostream>
#include <memory>

Player::Player() : GameElement(0, 0, 50, 50) {}
Player::Player(int x, int y) : GameElement(x, y, 50, 50) {}

/*bool Player::IntersectsWith(OpponentProjectile& projectile) {
  return !(GetX() > projectile.GetX() + projectile.GetWidth() ||
           projectile.GetX() > GetX() + GetWidth() ||
           GetY() > projectile.GetY() + projectile.GetHeight() ||
           projectile.GetY() > GetY() + GetHeight());
}

bool Player::IntersectsWith(Opponent& opponent) {
  return !(GetX() > opponent.GetX() + opponent.GetWidth() ||
           opponent.GetX() > GetX() + GetWidth() ||
           GetY() > opponent.GetY() + opponent.GetHeight() ||
           opponent.GetY() > GetY() + GetHeight());
}*/

void Player::Draw(graphics::Image& player_image) {
  /*graphics::Image player;
  player.Load("player.bmp");
  for (int i = 0; i < player.GetWidth(); i++) {
    for (int j = 0; j < player.GetHeight(); j++) {
      // graphics::Color color = player.GetColor(x, y);
      // const int null_x = (this->GetX() + x) % my_image.GetWidth();
      // const int null_y = (this->GetY() + y) % my_image.GetHeight();

      my_image.SetColor(GetX() + i, GetY() + j, player.GetColor(i, j));
    }
  }*/
  player_image.Initialize(50, 50);
  player_image.DrawRectangle(GetX() + 0, GetY() + 0, 30, 30, 6, 90, 150);
  player_image.DrawRectangle(GetX() + 2, GetY() + 2, 26, 26, 255, 255, 255);
  player_image.DrawRectangle(GetX() + 3, GetY() + 3, 24, 24, 0, 0, 0);
}

void Player::Move(const graphics::Image& moving) {}

PlayerProjectile::PlayerProjectile() : GameElement(0, 0, 50, 50) {}
PlayerProjectile::PlayerProjectile(int x, int y) : GameElement(x, y, 50, 50) {}

/*bool PlayerProjectile::IntersectsWith(Opponent& opponent) {
  return !(GetX() > opponent.GetX() + opponent.GetWidth() ||
           opponent.GetX() > GetX() + GetWidth() ||
           GetY() > opponent.GetY() + opponent.GetHeight() ||
           opponent.GetY() > GetY() + GetHeight());
}*/

void PlayerProjectile::Draw(graphics::Image& player_image_pro) {
  /*graphics::Image playerProjectile;
  playerProjectile.Load("p_projectile.bmp");
  for (int i = 0; i < playerProjectile.GetWidth(); i++) {
    for (int j = 0; j < playerProjectile.GetHeight(); j++) {
      // graphics::Color color = playerProjectile.GetColor(x, y);
      // const int null_x = (this->GetX() + x) % my_image.GetWidth();
      // const int null_y = (this->GetY() + y) % my_image.GetHeight();

      my_image.SetColor(GetX() + i, GetY() + j,
                        playerProjectile.GetColor(i, j));
    }
  }*/
  player_image_pro.Initialize(50, 50);
  player_image_pro.DrawRectangle(GetX() + 0, GetY() + 0, 30, 30, 6, 90, 150);
  player_image_pro.DrawRectangle(GetX() + 2, GetY() + 2, 26, 26, 255, 255, 255);
  player_image_pro.DrawRectangle(GetX() + 3, GetY() + 3, 24, 24, 0, 0, 0);
}

void PlayerProjectile::Move(const graphics::Image& moving) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(moving)) {
    SetIsActive(false);
  }
}
