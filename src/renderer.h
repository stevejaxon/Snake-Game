#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "interactable.h"
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::shared_ptr<Snake> const snake, std::shared_ptr<std::unordered_map<Location, std::shared_ptr<Interactable>>> const objects);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  void InitGrid(const int screen_width, const int screen_height,
           const int grid_width, const int grid_height);
  void RenderGrid(SDL_Renderer *renderer, const int screen_width, const int grid_width);

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  const SDL_Rect * grid_rectangles;
  const int total_num_rect_in_grid;
};

#endif