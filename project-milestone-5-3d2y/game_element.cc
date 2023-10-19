#include "game_element.h"

#include "cpputils/graphics/image.h"

GameElement::GameElement() : x_(0), y_(0), width_(50), height_(50) {}
GameElement::GameElement(int x, int y, int width, int height)
    : x_(x), y_(y), width_(width), height_(height), is_active(true) {}

int GameElement::GetX() const { return x_; }
int GameElement::GetY() const { return y_; }
int GameElement::GetWidth() { return width_; }
int GameElement::GetHeight() { return height_; }
bool GameElement::GetIsActive() { return is_active; }

void GameElement::SetX(int x) { x_ = x; }
void GameElement::SetY(int y) { y_ = y; }
void GameElement::SetIsActive(bool isActive) { is_active = isActive; }

// void GameElement::Draw(graphics::Image& my_image) {}
// void GameElement::Move(graphics::Image& my_image_moving) {}

bool GameElement::IntersectsWith(GameElement* game_element_image) {
  return !(
      GetX() > game_element_image->GetX() + game_element_image->GetWidth() ||
      game_element_image->GetX() > GetX() + GetWidth() ||
      GetY() > game_element_image->GetY() + game_element_image->GetHeight() ||
      game_element_image->GetY() > GetY() + GetHeight());
}

bool GameElement::IsOutOfBounds(const graphics::Image& moving) {
  if (GetX() > moving.GetWidth() || GetY() > moving.GetHeight() || GetX() < 0 ||
      GetY() < 0) {
    return true;
  } else {
    return false;
  }
}