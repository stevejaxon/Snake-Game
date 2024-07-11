#ifndef CONTROLLER_H
#define CONTROLLER_H

enum UserInput {
    quit,
    up,
    right,
    down,
    left,
    none
};

class Controller {
 public:
  UserInput HandleInput() const;
};

#endif