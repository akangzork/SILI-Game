#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <iostream>

#include "cpputils/graphics/image.h"

class GameElement {
  // private:
  // int x_;
  // int y_;
  // int width_;
  // int height_;
  // bool is_active = true;

 public:
  GameElement();
  GameElement(int x_, int y_, int width_, int height);
  int GetX() const;
  int GetY() const;
  int GetWidth();
  int GetHeight();
  bool GetIsActive();

  void SetX(int x);
  void SetY(int y);
  void SetIsActive(bool isActive);

  virtual void Draw(graphics::Image& my_image) = 0;
  virtual void Move(const graphics::Image& my_image) = 0;

  bool IntersectsWith(GameElement* game_element_image);
  bool IsOutOfBounds(const graphics::Image& moving);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active = true;
};

#endif
