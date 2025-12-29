#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

namespace HeapSort {

    void GetHeapifyCount(Rectangle* array, int size, int index, int* stepCount);

    int GetStepCount(Rectangle* items);

    void Heapify(Rectangle* array, int size, int index, int* currentStep, SortSequence* sort);

    void SetSequence(Rectangle* items, SortSequence* sequence);

}

#endif