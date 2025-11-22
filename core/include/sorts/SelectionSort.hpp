#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace SelectionSort {

    rgb_color GetRectangleColor(bool isOrdered, bool isMinimum, bool isSelected);

    int GetStepCount(Rectangle* items);

    SortSequence GetSequence(Rectangle* items);

}

#endif