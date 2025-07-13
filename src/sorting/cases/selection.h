#ifndef SELECTION_H
#define SELECTION_H

#include "../sorting.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

SortingCase *createSelectionSortingCase(int length, int width, int height,
                                        int left, int top);
#endif