#include "sorting.h"
#include "../model/model.h"
#include "visual.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

SortingCase *newSortingCase(Nodes *nodes, Area *area, SortFunction sort) {
  SortingCase *scase = malloc(sizeof(SortingCase));
  scase->area = area;
  scase->nodes = nodes;
  scase->sort = sort;
  return scase;
}

void destroySortingCase(SortingCase *scase) {
  if (!scase) {
    return;
  }
  destroyNodesList(scase->nodes);
  destroyArea(scase->area);
  free(scase);
}

SortingCaseNode *newSortingCaseNode(SortingCase *scase) {
  if (!scase) {
    return NULL;
  }
  SortingCaseNode *node = malloc(sizeof(SortingCaseNode));
  node->scase = scase;
  node->next = NULL;
  return node;
}

void destroySortingCaseNode(SortingCaseNode *node) {
  if (!node) {
    return;
  }
  destroySortingCase(node->scase);
  free(node);
}

SortingCases *newSortingCases() {
  SortingCases *cases = malloc(sizeof(SortingCases));
  cases->home = NULL;
  cases->tail = NULL;
  return cases;
}

void addSortingCase(SortingCases *cases, SortingCase *scase) {
  if (!cases || !scase) {
    return;
  }
  SortingCaseNode *node = newSortingCaseNode(scase);
  if (!node) {
    return;
  }
  if (!cases->home) {
    cases->home = node;
    cases->tail = node;
  } else {
    cases->tail->next = node;
    cases->tail = node;
  }
}

void destroySortingCases(SortingCases *cases) {
  if (!cases) {
    return;
  }
  SortingCaseNode *node = cases->home;
  while (node) {
    SortingCaseNode *next = node->next;
    destroySortingCaseNode(node);
    node = next;
  }
  free(cases);
}

bool proceedSortingCases(SortingCases *cases, SDL_Renderer *renderer) {
  if (!cases) {
    return true;
  }
  SortingCaseNode *node = cases->home;
  bool done = true;
  while (node) {
    if (!node->scase->sort(node->scase, renderer)) {
      done = false;
    }
    node = node->next;
  }
  return done;
}