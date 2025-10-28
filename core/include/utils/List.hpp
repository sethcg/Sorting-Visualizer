#ifndef LIST_H
#define LIST_H

#include <SDL3/SDL.h>
#include <Rect.hpp>

#define LIST_SIZE 32

#define LIST_MARGIN_MINIMUM 24

#define LIST_RECT_PADDING 2
#define LIST_RECT_COLOR 90    // COLOR NUMBER: [0-255]

void DrawList(SDL_Renderer *renderer, rectangle* items, int window_width, int window_height);

static void DrawRect(SDL_Renderer *renderer, rectangle* items, int index, int window_width, int window_height);

#endif