#ifndef LIST_H
#define LIST_H

#include <SDL3/SDL.h>
#include <Rect.hpp>

#define LIST_SIZE 32

#define LIST_MARGIN_MINIMUM 24
#define LIST_RECT_PADDING 2

void CreateList(SDL_Renderer *renderer, rectangle* items, int window_width, int window_height);

void ResizeList(SDL_Renderer *renderer, rectangle* items, int window_width, int window_height);

void ShuffleList(SDL_Renderer *renderer, rectangle* items);

void DrawList(SDL_Renderer *renderer, rectangle* items);

static void DrawRect(SDL_Renderer *renderer, rectangle* items, int index);

#endif