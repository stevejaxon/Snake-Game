#include "snake.h"
#include <cmath>
#include <thread>
#include <iostream>

void Snake::HandleInput(UserInput input) {
  if (input != UserInput::none && (!IsOpositeDirection(direction, input) || size == 1)) direction = input;
}

void Snake::Update(std::mutex& latest_tick_mtx, std::condition_variable& last_tick_cv, std::shared_ptr<Uint32> last_tick) {
  std::unique_lock<std::mutex> tick_mtx_lock(latest_tick_mtx, std::defer_lock);
  while (alive) {
    last_tick_cv.wait(tick_mtx_lock);

    // Check for spurious wakeups
    if (*last_tick > last_tick_time) {
      last_tick_time = *last_tick;
    } else {
      continue;
    }

    SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(
            head_y)};  // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)};  // Capture the head's cell after updating.

    // Update all of the body vector items if the snake head has moved to a new
    // cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
      UpdateBody(current_cell, prev_cell);
    }

    // sleep at every iteration to reduce CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case UserInput::up:
      head_y -= speed;
      break;

    case UserInput::down:
      head_y += speed;
      break;

    case UserInput::left:
      head_x -= speed;
      break;

    case UserInput::right:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

bool Snake::IsOpositeDirection(UserInput previous, UserInput latest) const {
  switch (previous)
  {
  case up:
    return latest == UserInput::down;
  case right:
    return latest == UserInput::left;
  case down:
    return latest == UserInput::up;
  case left:
    return latest == UserInput::right;
  default:
    return false;
  }
}