#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace BubbleSort {

    int GetStepCount_BubbleSort(Rectangle* items);

    SortSequence GetSequence_BubbleSort(Rectangle* items);

}

#endif