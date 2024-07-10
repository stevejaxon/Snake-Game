#ifndef SNAKE_H
#define SNAKE_H

#include <condition_variable>
#include <memory>
#include <mutex>
#include <vector>
#include "SDL.h"
#include "controller.h"

const SDL_Color kSnakeBodyColors[] {
  SDL_Color{0xFF, 0xFF, 0xFF, 0xFF},
  SDL_Color{0xc1, 0x04, 0xf0, 0xFF},
  SDL_Color{0x74, 0x02, 0x90, 0xFF},
  SDL_Color{0x2a, 0x01, 0x34, 0xFF},
  SDL_Color{0x06, 0x00, 0x08, 0xFF}
};

class Snake {
 public:
  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update(std::mutex& latest_tick_mtx, std::condition_variable& last_tick_cv, const std::shared_ptr<Uint32> last_tick, std::shared_ptr<UserInput> latest_input);

  void GrowBody();
  bool SnakeCell(int x, int y);

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  const int max_poison_ingestion = 4;
  int amount_of_poison_ingested = 0;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  bool IsOpositeDirection(UserInput previous, UserInput latest) const;
  void HandleInput(UserInput direction);

  UserInput direction = UserInput::up;
  bool growing{false};
  int grid_width;
  int grid_height;
  Uint32 last_tick_time;
};

#endif