#ifndef MERGE_H
#define MERGE_H

#include "../sorting.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

SortingCase *createMergeSortingCase(int length, int width, int height, int left,
                                    int top);
#endif