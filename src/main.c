#include "./sorting/cases/bubble.h"
#include "./sorting/cases/merge.h"
#include "./sorting/cases/selection.h"
#include "./sorting/sorting.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow(
      "Sorting Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    fprintf(stderr, "CreateWindow error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    fprintf(stderr, "CreateRenderer error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SortingCases *cases = newSortingCases();
  if (!cases) {
    fprintf(stderr, "Memory error\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  addSortingCase(cases, createBubbleSortingCase(WINDOW_WIDTH - 1, WINDOW_WIDTH,
                                                200, 0, 200));
  addSortingCase(cases, createSelectionSortingCase(WINDOW_WIDTH - 1,
                                                   WINDOW_WIDTH, 200, 0, 400));
  addSortingCase(cases, createMergeSortingCase(WINDOW_WIDTH - 1, WINDOW_WIDTH,
                                               200, 0, 600));

  SDL_Event e;
  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = 1;
    }
    if (proceedSortingCases(cases, renderer)) {
      break;
    }
    SDL_Delay(20);
  }

  destroySortingCases(cases);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
