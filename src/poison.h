#ifndef POISON_H
#define POISON_H

#include "interactable.h"
#include "SDL.h"

class Poison : public Interactable {
  public:
    static constexpr SDL_Color kColor{0x40, 0xFD, 0x14, 0xFF};
    static constexpr int kScore = -1;

    Poison(const int x, const int y) : Interactable(SDL_Point{x, y}, kColor, true, kScore) {}
    Poison(const SDL_Point _location) : Interactable(_location, kColor, true, kScore) {}
};

#endif