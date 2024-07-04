# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

# Features added

## Checkered background
The background has been changed to a checkered pattern instead of the a plain black background. 
I made this change to make it easier for the player to determine when the snake is in the same row or column as the food. I found the early part of the original game frustrating, it was difficult to line up the snake with the food from a long distance when the food was not close to the edges. Adding this geometric pattern makes it easier to line up the snake.
The coloured backround also makes the game more visually appealing. 

# Rubric
## Loops, Functions, I/O
### The project demonstrates an understanding of C++ functions and control structures
The implementation of the checkered pattern demonstrates the understanding of c++ functions and control structures in a few different ways.
* An understanding of functions is demonstrated in the introduction of the two new functions `InitGrid` and `RenderGrid`. These functions can be found on lines 44 and 106 of renderer.cpp. The `InitGrid` function was created to perform the, one-time-only, work of caching the co-ordinates of the rectangles that are rendered to create the checkered pattern background. The `RenderGrid` function encapsulates the logic of looping over the rectangles' co-ordinates, alternating the colors and rendering the rectangles on the background, each loop of the game engine.
* An understanding of c++'s control structures is demonstrated in the two new functions `InitGrid` and `RenderGrid`. The `InitGrid` function uses a nested **for loop** to enumerate the co-ordinates of the rectangles that will be rendered to the screen, and store them in an array. This code can be found on lines 49 - 56 of renderer.cpp. The `RenderGrid` function uses both a **for loop** and an **if-else statement** to implement the logic required to render the correctly colored rectangle to the screen. This code can be found on lines 110 - 119 of renderer.cpp.
### The project uses data structures and immutable variables. 
The implementation of the checkered pattern demonstrates the use of arrays and constant values.
* The `grid_rectangles` and `total_num_rect_in_grid` variables are constants defined in renderer.h. The `total_num_rect_in_grid` variable holds the calculated number of rectangles needed to form the checkered pattern of the background; which is used to initialize the `grid_rectangles` array. The `total_num_rect_in_grid` variable is set as part of the `Renderer` constructor's member initialization list in renderer.cpp, on line 10. The `grid_rectangles` array is populated in the `Renderer` constructor when the `InitGrid` function is called on line 35 in renderer.cpp.
## Memory Management
### The project uses destructors appropriately.
* The `Renderer` class' destructor has been updated to delete the dynamically, heap allocated array `grid_rectangles`. This addition can be found on line 41 of renderer.cpp.