#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  void InitGrid(const int screen_width, const int screen_height,
           const int grid_width, const int grid_height);
  void RenderGrid(SDL_Renderer *renderer);

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  const SDL_Point * kGridLines;
  const int num_horizontal_grid_lines;
  const int num_vertical_grid_lines;
  const int total_num_grid_lines;
};

#endif