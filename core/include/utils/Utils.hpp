#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>

#include <List.hpp>
#include <Rect.hpp>

Rectangle* CopyArray(Rectangle* items);

void Swap(Rectangle* array, int index_one, int index_two);

rgb_color GetRectangleColor(bool isOrdered, bool isCurrent, bool isChecking);

#endif