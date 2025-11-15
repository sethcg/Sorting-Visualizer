#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>

#include <List.hpp>
#include <Rect.hpp>

void Swap(Rectangle* items, int index_one, int index_two);

rgb_color GetRectangleColor(bool isOrdered, bool isCurrent, bool isChecking);

#endif