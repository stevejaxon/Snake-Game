#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "location.h"
#include "SDL.h"

enum class Type {
    food,
    poison
};

class Interactable {
public:
  Interactable(const int x, const int y, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a, const bool _edible, const int _score)
      : location(Location{x, y}), color(SDL_Color{r, g, b, a}), edible(_edible), score(_score) {}
  Interactable(const Location _location, const SDL_Color _color, const bool _edible, const int _score)
      : location(_location), color(_color), edible(_edible), score(_score) {}

  virtual Type GetType() const = 0;

  const Location location;
  const bool edible;
  const SDL_Color color;
  const int score;
};

#endif