#ifndef BUBBLE_H
#define BUBBLE_H

#include "../sorting.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

SortingCase *createBubbleSortingCase(int length, int width, int height,
                                     int left, int top);
#endif