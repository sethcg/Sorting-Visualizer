#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace InsertionSort {

    int GetStepCount(Rectangle* items);

    void SetSequence(Rectangle* items, SortSequence* sequence);

}

#endif