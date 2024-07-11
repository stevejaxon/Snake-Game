#ifndef GAME_H
#define GAME_H

#include <condition_variable>
#include <memory>
#include <random>
#include <unordered_map>
#include "controller.h"
#include "location.h"
#include "renderer.h"
#include "interactable.h"
#include "SDL.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  std::shared_ptr<Snake> snake;
  std::shared_ptr<std::unordered_map<Location, std::shared_ptr<Interactable>>> objects = std::make_shared<std::unordered_map<Location, std::shared_ptr<Interactable>>>();
  std::shared_ptr<Uint32> last_tick = std::make_shared<Uint32>(0);
  std::mutex last_tick_mutex;
  std::condition_variable last_tick_cv;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlacePoison();
  void Update();
  bool IsLocationOccupied(Location location);
  template <typename T> void PlaceInteractable();
};

template <typename T>
void Game::PlaceInteractable() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing an interactable object.
    Location location{x, y};
    if (!IsLocationOccupied(location)) {
      objects->emplace(location, std::make_shared<T>(location));
      return;
    }
  }
}

#endif