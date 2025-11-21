#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace QuickSort {

    rgb_color GetRectangleColor(bool isOrdered, bool isPivot, bool isSelected);

    int GetPartitionCount(Rectangle* array, int low, int high, int* stepCount);

    void GetQuickSortCount(Rectangle* array, int low, int high, int* stepCount);

    int GetStepCount(Rectangle* items);

    int Partition(Rectangle* array, int low, int high, int* currentStep, SortSequence sort);

    void QuickSort(Rectangle* array, int low, int high, int* currentStep, SortSequence sort);

    SortSequence GetSequence(Rectangle* items);

}

#endif