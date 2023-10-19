#include <iostream>
#include <memory>

#include "cpputils/graphics/image.h"
#include "game.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"

int main() {
  graphics::Image game_screen_;
  game_screen_.Initialize(800, 600);
  Game Game1;
  Game1.Init();
  Game1.UpdateScreen();
  Game1.Start();
}
