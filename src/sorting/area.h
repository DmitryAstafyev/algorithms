#ifndef AREA_H
#define AREA_H

#include "../model/model.h"

typedef struct {
  int width;
  int height;
} AreaSize;

typedef struct {
  int top;
  int left;
} AreaPosition;

typedef struct {
  float ratioByY;
  float ratioByX;
  float colsPerPx;
  int length;
} AreaScale;

typedef struct {
  int swaps;
  int shifts;
  Node *swaped[2];
  Node *last;
  char *name;
} AreaData;

typedef struct {
  AreaData data;
  AreaSize size;
  AreaPosition position;
  AreaScale scale;
} Area;

#endif