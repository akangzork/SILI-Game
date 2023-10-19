#ifndef OPPONENT_H
#define OPPONENT_H

#include <iostream>
#include <memory>

#include "cpputils/graphics/image.h"
#include "game_element.h"

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile();
  OpponentProjectile(int x, int y);
  void Draw(graphics::Image& my_image) override;
  void Move(const graphics::Image& my_image) override;
};

class Opponent : public GameElement {
 public:
  Opponent();
  Opponent(int x, int y);
  void Draw(graphics::Image& opp_image) override;
  void Move(const graphics::Image& my_image) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();

 private:
  int counter;
};

#endif
