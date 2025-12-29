#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace BubbleSort {

    int GetStepCount(Rectangle* items);

    void SetSequence(Rectangle* items, SortSequence* sequence);

}

#endif