#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <memory>

#include "cpputils/graphics/image.h"
#include "game_element.h"
#include "opponent.h"

class Player : public GameElement {
 public:
  Player();
  Player(int x, int y);
  // bool IntersectsWith(OpponentProjectile& projectile);
  // bool IntersectsWith(Opponent& opponent);
  void Draw(graphics::Image& player_image) override;
  void Move(const graphics::Image& moving) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile();
  PlayerProjectile(int x, int y);
  // bool IntersectsWith(Opponent& opponent);
  void Draw(graphics::Image& player_image_pro) override;
  void Move(const graphics::Image& moving) override;
};

#endif
