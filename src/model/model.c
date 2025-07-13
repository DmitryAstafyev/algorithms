#include "./model.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Node *newNode(Node *prev) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    return NULL;
  }
  node->value = rand();
  node->prev = prev;
  node->next = NULL;
  return node;
}

void destroyNodesList(Nodes *nodes) {
  if (!nodes) {
    return;
  }
  Node *node = nodes->head;
  while (node) {
    Node *next = node->next;
    free(node);
    node = next;
  }
  free(nodes);
}

Nodes *newNodesList(int len) {
  Nodes *nodes = malloc(sizeof(Nodes));
  if (!nodes) {
    return NULL;
  }
  nodes->head = NULL;
  nodes->tail = NULL;
  nodes->length = 0;
  Node *prev = NULL;
  for (int idx = 0; idx < len; idx++) {
    Node *node = newNode(prev);
    if (!node) {
      destroyNodesList(nodes);
      return NULL;
    }
    if (!nodes->head) {
      nodes->head = node;
    }
    if (nodes->tail) {
      nodes->tail->next = node;
    }
    nodes->tail = node;
    prev = node;
    nodes->length++;
  }
  return nodes;
}

int getMaxValue(Nodes *nodes) {
  if (!nodes) {
    fprintf(stderr, "[Model] nodes doesn't exist\n");
    exit(EXIT_FAILURE);
  }
  int max = -1;
  Node *node = nodes->head;
  while (node) {
    if (max < node->value) {
      max = node->value;
    }
    node = node->next;
  }
  return max;
}