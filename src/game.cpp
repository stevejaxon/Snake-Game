#include "game.h"
#include <iostream>
#include <thread>
#include "SDL.h"
#include "food.h"
#include "poison.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  snake = std::make_shared<Snake>(grid_width, grid_height);
  PlaceFood();
  PlacePoison();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  auto latest_input = std::make_shared<UserInput>(UserInput::none);
  std::thread snake_thread = std::thread(&Snake::Update, snake, std::ref(last_tick_mutex), std::ref(last_tick_cv), last_tick, latest_input);
  snake_thread.detach();

  std::unique_lock<std::mutex> lg(last_tick_mutex, std::defer_lock);
  while (running) {
    frame_start = SDL_GetTicks();

    lg.lock();
    *last_tick = frame_start;
    lg.unlock();

    // Input, Update, Render - the main game loop.
    *latest_input = controller.HandleInput();
    if (*latest_input == UserInput::quit) {
      running = false;
      continue;
    }
    Update();
    // Notify the threads (such as the snake) of the new frame
    last_tick_cv.notify_all();
    renderer.Render(snake, objects);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  PlaceInteractable<Food>(std::ref(engine), objects);
}

void Game::PlacePoison() {
  PlaceInteractable<Poison>(std::ref(engine), objects);
}

void Game::Update() {
  if (!snake->alive) return;

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);

  // Check if there's food in the same grid location as the snake head's new location
  Location location{new_x, new_y};
  auto iter = objects->find(location);
  // location does not exist in the objects map i.e. it is empty
  if (iter == objects->end()) {
    return;
  }
  auto object = iter->second;
  if (object->edible) {
    score = score + object->score;
    objects->erase(iter);
    if (object->GetType() == Type::food) {
      // Grow snake and increase speed.
      snake->GrowBody();
      snake->speed += 0.02;
      PlaceFood();
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }

bool Game::IsLocationOccupied(Location location) {
  auto object = objects->find(location);
  return (object != objects->end() || snake->SnakeCell(location.x, location.y));
}