#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "SDL.h"

class Interactable {
public:
  Interactable(const int x, const int y, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a, const bool _edible, const int _score)
      : location(SDL_Point{x, y}), color(SDL_Color{r, g, b, a}), edible(_edible), score(_score) {}
  Interactable(const SDL_Point _location, const SDL_Color _color, const bool _edible, const int _score)
      : location(_location), color(_color), edible(_edible), score(_score) {}

  const SDL_Point location;
  const bool edible;
  const SDL_Color color;
  const int score;
};

#endif