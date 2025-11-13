#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <imgui.h>

#include <Rect.hpp>
#include <Sort.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MINIMUM_WINDOW_WIDTH 400
#define MINIMUM_WINDOW_HEIGHT 400

typedef struct {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    ImDrawData* data;
    Rectangle* items;

    bool isSorting;

    int sortId;
    int stepIndex;
    int lastTime;
    int delayInMilliseconds;
    SortSequence sequence;
} AppContext;

char* sortOptions[8] = {
    (char*) "Bubble",
    (char*) "Cocktail",
    (char*) "Heap",
    (char*) "Insertion",
    (char*) "Merge",
    (char*) "Quick",
    (char*) "Radix",
    (char*) "Selection"
};

#endif