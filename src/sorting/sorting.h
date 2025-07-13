#ifndef SORTING_H
#define SORTING_H

#include "../model/model.h"
#include "area.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

struct SortingCase;

typedef bool (*SortFunction)(struct SortingCase *scase, SDL_Renderer *renderer);

typedef struct SortingCase {
  Nodes *nodes;
  Area *area;
  SortFunction sort;
} SortingCase;

typedef struct SortingCaseNode {
  SortingCase *scase;
  struct SortingCaseNode *next;
} SortingCaseNode;

typedef struct SortingCases {
  SortingCaseNode *home;
  SortingCaseNode *tail;
} SortingCases;

SortingCase *newSortingCase(Nodes *nodes, Area *area, SortFunction sort);

void destroySortingCase(SortingCase *scase);

SortingCaseNode *newSortingCaseNode(SortingCase *scase);

void destroySortingCaseNode(SortingCaseNode *node);

SortingCases *newSortingCases();

void addSortingCase(SortingCases *cases, SortingCase *scase);

void destroySortingCases(SortingCases *cases);

bool proceedSortingCases(SortingCases *cases, SDL_Renderer *renderer);

#endif