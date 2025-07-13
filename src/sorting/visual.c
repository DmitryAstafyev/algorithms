#include "visual.h"
#include "../model/model.h"
#include "sorting.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

AreaPosition newAreaPosition(int left, int top) {
  AreaPosition position = {.left = left, .top = top};
  return position;
}

AreaSize newAreaSize(int width, int height) {
  AreaSize size = {.height = height, .width = width};
  return size;
}

AreaData newAreaData(char *name) {
  AreaData data = {.name = strdup(name),
                   .shifts = 0,
                   .swaps = 0,
                   .last = NULL,
                   .swaped = {NULL, NULL}};
  return data;
}

AreaScale newAreaScale(int length, int width, int height, Nodes *nodes) {
  int maxY = getMaxValue(nodes);

  AreaScale scale = {.length = length,
                     .colsPerPx = (float)length / (float)width,
                     .ratioByX = (float)width / (float)length,
                     .ratioByY = (float)height / (float)maxY};
  printf("maxY = %i\n", maxY);
  printf("length = %i\n", length);
  printf("width = %i\n", width);
  printf("colsPerPx = %f\n", scale.colsPerPx);
  printf("ratioByX = %f\n", scale.ratioByX);
  printf("ratioByY = %f\n", scale.ratioByY);
  return scale;
}

Area *newArea(char *name, int length, int width, int height, int left, int top,
              Nodes *nodes) {
  Area *area = malloc(sizeof(Area));
  area->position = newAreaPosition(left, top);
  area->size = newAreaSize(width, height);
  area->data = newAreaData(name);
  area->scale = newAreaScale(length, width, height, nodes);
  return area;
}

void destroyArea(Area *area) {
  if (!area) {
    return;
  }
  free(area->data.name);
  free(area);
}

void renderArea(SortingCase *scase, SDL_Renderer *renderer) {
  if (!scase || !scase->nodes || !scase->area) {
    return;
  }
  Nodes *nodes = scase->nodes;
  Area *area = scase->area;
  Node *node = nodes->head;
  int idx = 0;
  int gidx = 0;
  int maxY = -1;
  float x = 0;
  while (node) {
    if (maxY < node->value) {
      maxY = node->value;
    }
    idx++;
    if (idx >= area->scale.colsPerPx) {
      float width = area->scale.colsPerPx > 1 ? 1 : (1 / area->scale.colsPerPx);
      float height = maxY * area->scale.ratioByY;
      SDL_Rect bar = {.x = x + area->position.left,
                      .y = area->position.top - height,
                      .w = width,
                      .h = height};
      if (area->data.swaped[0] == node || area->data.swaped[1] == node) {
        SDL_SetRenderDrawColor(renderer, 250, 20, 20, 255);
      } else {
        SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);
      }
      SDL_RenderFillRect(renderer, &bar);
      x += width;
      maxY = -1;
      idx = 0;
    }
    gidx++;
    node = node->next;
  }
}

void renderAreas(SortingCases *cases, SDL_Renderer *renderer) {
  if (!cases) {
    return;
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SortingCaseNode *node = cases->home;
  while (node) {
    renderArea(node->scase, renderer);
    node = node->next;
  }
  SDL_RenderPresent(renderer);
}
