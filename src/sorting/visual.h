#ifndef VISUAL_H
#define VISUAL_H

#include "../model/model.h"
#include "./sorting.h"
#include "area.h"
#include <SDL2/SDL.h>

Area *newArea(char *name, int length, int width, int height, int left, int top,
              Nodes *nodes);
void destroyArea(Area *area);

void renderAreas(SortingCases *cases, SDL_Renderer *renderer);

#endif