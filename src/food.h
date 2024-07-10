#ifndef FOOD_H
#define FOOD_H

#include "interactable.h"
#include "location.h"

class Food : public Interactable {
  public:
    static constexpr SDL_Color kColor{0xFF, 0xCC, 0x00, 0xFF};
    static constexpr int kScore = 1;

    Type GetType() const {
      return Type::food;
    }

    Food(const int x, const int y) : Interactable(Location{x, y}, kColor, true, kScore) {}
    Food(const Location _location) : Interactable(_location, kColor, true, kScore) {}
};

#endif