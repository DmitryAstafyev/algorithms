#include "../../model/model.h"
#include "../sorting.h"
#include "../visual.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <wchar.h>

Node *selection_sorting(SortingCase *scase, SDL_Renderer *renderer) {
  if (!scase || !scase->nodes || !scase->area) {
    return NULL;
  }
  Node *from =
      !scase->area->data.last ? scase->nodes->head : scase->area->data.last;
  Node *node = from;
  Node *min = from;
  while (node) {
    if (node->value < min->value) {
      min = node;
    }
    node = node->next;
    scase->area->data.shifts++;
  }
  int tmp = from->value;
  from->value = min->value;
  min->value = tmp;
  scase->area->data.swaped[0] = from;
  scase->area->data.swaped[1] = min;
  scase->area->data.swaps++;
  return from->next;
}

bool selection_sort(SortingCases *cases, SortingCase *scase,
                    SDL_Renderer *renderer) {
  scase->area->data.last = selection_sorting(scase, renderer);
  renderAreas(cases, renderer);
  return !scase->area->data.last;
}

SortingCase *createSelectionSortingCase(int length, int width, int height,
                                        int left, int top) {
  printf("nodes length = %i\n", length);

  Nodes *nodes = newNodesList(length);
  if (!nodes) {
    return NULL;
  }
  printf("nodes length = %i\n", nodes->length);
  Area *area =
      newArea("selection", nodes->length, width, height, left, top, nodes);
  if (!area) {
    destroyNodesList(nodes);
    return NULL;
  }
  SortingCase *scase = newSortingCase(nodes, area, selection_sort);
  if (!scase) {
    destroyNodesList(nodes);
    destroyArea(area);
    return NULL;
  }
  return scase;
}