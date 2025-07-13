#include "../../model/model.h"
#include "../sorting.h"
#include "../visual.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <wchar.h>

Node *split(Node *head) {
  Node *slow = head;
  Node *fast = head->next;

  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
  }

  Node *mid = slow->next;
  slow->next = NULL;
  if (mid)
    mid->prev = NULL;
  return mid;
}

Node *merge(Node *a, Node *b) {
  if (!a)
    return b;
  if (!b)
    return a;

  if (a->value <= b->value) {
    a->next = merge(a->next, b);
    if (a->next)
      a->next->prev = a;
    a->prev = NULL;
    return a;
  } else {
    b->next = merge(a, b->next);
    if (b->next)
      b->next->prev = b;
    b->prev = NULL;
    return b;
  }
}

Node *merge_and_sort(Node *head, SortingCases *cases, SDL_Renderer *renderer) {
  if (!head || !head->next)
    return head;

  Node *mid = split(head);
  Node *left = merge_and_sort(head, cases, renderer);
  Node *right = merge_and_sort(mid, cases, renderer);
  renderAreas(cases, renderer);

  return merge(left, right);
}

void updateNodesMetadata(Nodes *nodes) {
  Node *tail = nodes->head;
  int count = 0;
  while (tail && tail->next) {
    tail = tail->next;
    count++;
  }
  nodes->tail = tail;
  nodes->length = count + 1;
}

void merge_sort_nodes(Nodes *nodes, SortingCases *cases,
                      SDL_Renderer *renderer) {
  if (!nodes || !nodes->head)
    return;
  nodes->head = merge_and_sort(nodes->head, cases, renderer);
  updateNodesMetadata(nodes);
}

bool merge_sort(SortingCases *cases, SortingCase *scase,
                SDL_Renderer *renderer) {
  if (scase->area->data.last) {
    return true;
  }
  merge_sort_nodes(scase->nodes, cases, renderer);
  renderAreas(cases, renderer);
  scase->area->data.last = scase->nodes->head;
  return true;
}

SortingCase *createMergeSortingCase(int length, int width, int height, int left,
                                    int top) {
  Nodes *nodes = newNodesList(length);
  if (!nodes) {
    return NULL;
  }
  printf("nodes length = %i\n", nodes->length);
  Area *area = newArea("merge", nodes->length, width, height, left, top, nodes);
  if (!area) {
    destroyNodesList(nodes);
    return NULL;
  }
  SortingCase *scase = newSortingCase(nodes, area, merge_sort);
  if (!scase) {
    destroyNodesList(nodes);
    destroyArea(area);
    return NULL;
  }
  return scase;
}