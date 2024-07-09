#ifndef LOCATION_H
#define LOCATION_H

#include <cstddef>
#include <memory>

class Location {
public:
  Location(int _x, int _y) : x(_x), y(_y) {}
  bool operator==(Location other) const {
    return x == other.x && y == other.y;
  }
  const int x;
  const int y;
};

template <>
struct std::hash<Location>
{
  std::size_t operator()(const Location& l) const noexcept {
    std::size_t h1 = std::hash<int>{}(l.x);
    std::size_t h2 = std::hash<int>{}(l.y);
    return h1 ^ (h2 << 1);
  }
};

#endif