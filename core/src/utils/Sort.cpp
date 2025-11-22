#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

#include <BubbleSort.hpp>
#include <CocktailSort.hpp>
#include <HeapSort.hpp>
#include <InsertionSort.hpp>
#include <MergeSort.hpp>
#include <QuickSort.hpp>
#include <RadixSort.hpp>
#include <SelectionSort.hpp>

SortSequence GetSortSequence(int sortId, Rectangle* items) {
    switch(sortId) {
        case 0:
            return BubbleSort::GetSequence(items);
        case 1:
            return CocktailSort::GetSequence(items);
        case 2:
            return HeapSort::GetSequence(items);
        case 3:
            return InsertionSort::GetSequence(items);
        case 4:
            return MergeSort::GetSequence(items);
        case 5:
            return QuickSort::GetSequence(items);
        case 6:
            return RadixSort::GetSequence(items);
        case 7:
            return SelectionSort::GetSequence(items);
    }
    return { };
}

bool IncrementStep(int stepIndex, SortSequence sequence, Rectangle* items) {
    // RETURN TRUE WHEN SORT IS COMPLETE
    if(stepIndex >= sequence.stepCount) {
        return true;
    }

    // SWAP THE VALUES TO THAT OF THE CURRENT STEP SNAPSHOT
    int offset;
    for (int i = 0; i < LIST_SIZE; i++) {
        offset = (stepIndex * LIST_SIZE) + i;
        items[i].value = sequence.steps[offset].value;
        items[i].rect_color = sequence.steps[offset].rect_color;
    }
    return false;
}