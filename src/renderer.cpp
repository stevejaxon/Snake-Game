#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height), 
      total_num_rect_in_grid((screen_width / grid_width) * (screen_height / grid_height)) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize the points along the grid lines
  InitGrid(screen_width, screen_height, grid_width, grid_height);
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
  delete[] grid_rectangles;
}

void Renderer::InitGrid(const int screen_width, const int screen_height,
                        const int grid_width, const int grid_height) {
  SDL_Rect* gridRects = new SDL_Rect[total_num_rect_in_grid];
  int columnsInRow = screen_width / grid_width;
  int rowsInGrid = screen_height / grid_height;
  for (int i = 0; i < rowsInGrid; i++) {
    for (int j = 0; j < columnsInRow; j++) {
      int index = (i * columnsInRow) + j;
      int x = grid_width * j;
      int y = grid_height * i;
      gridRects[index] = SDL_Rect{x, y, grid_width, grid_height};
    }
  }
  grid_rectangles = gridRects;
}

void Renderer::Render(std::shared_ptr<Snake> const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render the grid
  RenderGrid(sdl_renderer, screen_width, grid_width);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake->body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake->head_x) * block.w;
  block.y = static_cast<int>(snake->head_y) * block.h;
  if (snake->alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderGrid(SDL_Renderer *renderer, const int screen_width, const int grid_width) {
  int columnsInRow = screen_width / grid_width;
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
  bool isEvenRow = true;
  for (int i = 0; i < total_num_rect_in_grid; i++) {
    int rowNum = i / columnsInRow;
    rowNum % 2 == 0 ? isEvenRow = true: isEvenRow = false;
    if (isEvenRow && i % 2 == 0 || !isEvenRow && i % 2 == 1) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x47, 0x74, 0x37, 0x40);      
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0x69, 0xAB, 0x51, 0x40);
    }
    SDL_RenderFillRect(sdl_renderer, grid_rectangles + i);
  }
}