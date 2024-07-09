#ifndef FOOD_H
#define FOOD_H

#include "interactable.h"
#include "SDL.h"

class Food : public Interactable {
  public:
    static constexpr SDL_Color kColor{0xFF, 0xCC, 0x00, 0xFF};
    static constexpr int kScore = 1;

    Food(const int x, const int y) : Interactable(SDL_Point{x, y}, kColor, true, kScore) {}
    Food(const SDL_Point _location) : Interactable(_location, kColor, true, kScore) {}
};

#endif