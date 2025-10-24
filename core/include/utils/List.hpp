#ifndef LIST_H
#define LIST_H

#include <SDL3/SDL.h>
#include <Rect.hpp>

#define LIST_SIZE 32

#define LIST_PADDING_SIZE 24
#define LIST_RECT_SPACING_SIZE 2

#define LIST_RECT_COLOR 50    // COLOR NUMBER: [0-255]

void CreateList(SDL_Renderer *renderer, rectangle* items, int window_width, int window_height);

void DrawList(SDL_Renderer *renderer, rectangle* items);

static void DrawRect(SDL_Renderer *renderer, rectangle* items, int index);

#endif