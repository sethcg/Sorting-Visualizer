#ifndef RADIX_SORT_H
#define RADIX_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace RadixSort {

    int GetMaxValue(Rectangle* array);

    void GetCountSortCount(Rectangle* array, int exponent, int* stepCount);

    void GetRadixSortCount(Rectangle* array, int* stepCount);

    int GetStepCount(Rectangle* items);

    void CountSort(Rectangle* array, int exponent, int* currentStep, SortSequence* sort);

    void RadixSort(Rectangle* array, int* currentStep, SortSequence* sort);

    void SetSequence(Rectangle* items, SortSequence* sequence);

}

#endif