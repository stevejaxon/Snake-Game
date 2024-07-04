#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

UserInput Controller::HandleInput() const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return UserInput::quit;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          return UserInput::up;
        case SDLK_DOWN:
          return UserInput::down;
        case SDLK_LEFT:
          return UserInput::left;
        case SDLK_RIGHT:
          return UserInput::right;
        case SDLK_ESCAPE:
          return UserInput::quit;
      }
    }
  }
  return UserInput::none;
}