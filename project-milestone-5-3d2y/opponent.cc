#include "opponent.h"

#include <iostream>
#include <memory>

#include "cpputils/graphics/image.h"

Opponent::Opponent() {}
Opponent::Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

void Opponent::Draw(graphics::Image& opp_image) {
  /*graphics::Image opponent;
  opponent.Load("opponent.bmp");
  for (int i = 0; i < opponent.GetWidth(); i++) {
    for (int j = 0; j < opponent.GetHeight(); j++) {
      // graphics::Color color = opponent.GetColor(i, j);
      // const int null_x = (this->GetX() + i) % my_image.GetWidth();
      // const int null_y = (this->GetY() + j) % my_image.GetHeight();
      graphics::Color color = opponent.GetColor(i, j);
      opp_image.SetColor(GetX() + i, GetY() + j, color);
    }
  }*/
  opp_image.Initialize(50, 50);
  opp_image.DrawRectangle(GetX() + 0, GetY() + 0, 30, 30, 200, 4, 200);
  opp_image.DrawRectangle(GetX() + 2, GetY() + 2, 26, 26, 255, 255, 255);
  opp_image.DrawRectangle(GetX() + 3, GetY() + 3, 24, 24, 0, 0, 0);
}

void Opponent::Move(const graphics::Image& my_image) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(my_image)) {
    SetIsActive(false);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  counter++;
  if (counter % 10) {
    return nullptr;
  } else {
    return std::make_unique<OpponentProjectile>(Opponent::GetX(),
                                                Opponent::GetY());
  }
}

OpponentProjectile::OpponentProjectile() : GameElement(0, 0, 50, 50) {}
OpponentProjectile::OpponentProjectile(int x, int y)
    : GameElement(x, y, 50, 50) {}

void OpponentProjectile::Draw(graphics::Image& opp_image_pro) {
  /*graphics::Image opponentProjectile;
  opponentProjectile.Load("o_projectile.bmp");
  for (int i = 0; i < opponentProjectile.GetWidth(); i++) {
    for (int j = 0; j < opponentProjectile.GetHeight(); j++) {
      // graphics::Color color = opponentProjectile.GetColor(i, j);
      // const int null_x = (this->GetX() + i) % my_image.GetWidth();
      // const int null_y = (this->GetY() + j) % my_image.GetHeight();
      graphics::Color color = my_image.GetColor(i, j);
      my_image.SetColor(GetX() + i, GetY() + j, color);
    }
  }*/
  opp_image_pro.Initialize(50, 50);
  opp_image_pro.DrawRectangle(GetX() + 0, GetY() + 0, 30, 30, 200, 4, 200);
  opp_image_pro.DrawRectangle(GetX() + 2, GetY() + 2, 26, 26, 255, 255, 255);
  opp_image_pro.DrawRectangle(GetX() + 3, GetY() + 3, 24, 24, 0, 0, 0);
}

void OpponentProjectile::Move(const graphics::Image& my_image) {
  SetX(GetX() + 5);
  SetY(GetY() + 5);
  if (IsOutOfBounds(my_image)) {
    SetIsActive(false);
  }
}
