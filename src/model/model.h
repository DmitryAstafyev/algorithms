#ifndef MODEL_H
#define MODEL_H

typedef struct Node {
  struct Node *prev;
  struct Node *next;
  int value;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  int length;
} Nodes;

void destroyNodesList(Nodes *nodes);

Nodes *newNodesList(int len);

int getMaxValue(Nodes *nodes);

#endif