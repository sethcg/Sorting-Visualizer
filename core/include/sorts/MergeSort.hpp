#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace MergeSort {

    rgb_color GetRectangleColor(bool isSelected, bool inGrouping);

    void GetMergeCount(Rectangle* array, int left, int middle, int right, int* stepCount);

    int GetStepCount(Rectangle* array);

    void Merge(Rectangle* array, int left, int middle, int right, int* currentStep, SortSequence sort, int currentSize);

    SortSequence GetSequence(Rectangle* items);

}

#endif