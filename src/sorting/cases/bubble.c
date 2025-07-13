#include "../../model/model.h"
#include "../sorting.h"
#include "../visual.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <wchar.h>

Node *bubble_sorting(SortingCases *cases, SortingCase *scase,
                     SDL_Renderer *renderer) {
  if (!scase || !scase->nodes || !scase->area) {
    return NULL;
  }
  Node *node = scase->nodes->head;
  Node *updated = NULL;
  Node *last = scase->area->data.last;
  scase->area->data.swaped[0] = NULL;
  scase->area->data.swaped[1] = NULL;
  while (node && node->next) {
    if (last && node->next == last) {
      break;
    }
    if (node->value > node->next->value) {
      int tmp = node->value;
      node->value = node->next->value;
      node->next->value = tmp;
      updated = node->next;
      scase->area->data.swaped[0] = node;
      scase->area->data.swaped[1] = node->next;
      scase->area->data.swaps++;
      renderAreas(cases, renderer);
    }
    node = node->next;
    scase->area->data.shifts++;
  }
  return updated;
}

bool bubble_sort(SortingCases *cases, SortingCase *scase,
                 SDL_Renderer *renderer) {
  scase->area->data.last = bubble_sorting(cases, scase, renderer);
  renderAreas(cases, renderer);
  return !scase->area->data.last;
}

SortingCase *createBubbleSortingCase(int length, int width, int height,
                                     int left, int top) {
  Nodes *nodes = newNodesList(length);
  if (!nodes) {
    return NULL;
  }
  printf("nodes length = %i\n", nodes->length);
  Area *area =
      newArea("bubble", nodes->length, width, height, left, top, nodes);
  if (!area) {
    destroyNodesList(nodes);
    return NULL;
  }
  SortingCase *scase = newSortingCase(nodes, area, bubble_sort);
  if (!scase) {
    destroyNodesList(nodes);
    destroyArea(area);
    return NULL;
  }
  return scase;
}