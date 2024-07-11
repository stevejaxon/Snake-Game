#ifndef POISON_H
#define POISON_H

#include "interactable.h"
#include "location.h"

class Poison : public Interactable {
  public:
    static constexpr SDL_Color kColor{0x40, 0xFD, 0x14, 0xFF};
    static constexpr int kScore = -1;

    Type GetType() const override {
      return Type::poison;
    }

    Poison(const int x, const int y) : Interactable(Location{x, y}, kColor, true, kScore) {}
    Poison(const Location _location) : Interactable(_location, kColor, true, kScore) {}
};

#endif