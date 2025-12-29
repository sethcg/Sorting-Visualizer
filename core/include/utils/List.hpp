#ifndef LIST_H
#define LIST_H

#include <SDL3/SDL.h>

#include <Rect.hpp>

#define LIST_SIZE 32

#define LIST_MARGIN_MINIMUM 24
#define LIST_RECT_PADDING 2

void CreateList(Rectangle* items, int window_width, int window_height);

void ResizeList(Rectangle* items, int window_width, int window_height);

void ShuffleList(Rectangle* items);

void DrawList(SDL_Renderer *renderer, Rectangle* items, int window_width, int window_height);

void DrawRect(SDL_Renderer *renderer, Rectangle* items, int index);

#endif