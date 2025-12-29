#include <array>
#include <functional>
#include <memory>

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

void UpdateSequence(int sortId, Rectangle* items, SortSequence* sequence) {
    static const std::array<std::function<void(Rectangle*, SortSequence*)>, 8> sorts = {
        BubbleSort::SetSequence,
        CocktailSort::SetSequence,
        HeapSort::SetSequence,
        InsertionSort::SetSequence,
        MergeSort::SetSequence,
        QuickSort::SetSequence,
        RadixSort::SetSequence,
        SelectionSort::SetSequence
    };

    if (sortId >= 0 && sortId < static_cast<int>(sorts.size())) {
        sorts[sortId](items, sequence);
    }
}

bool IncrementStep(int stepIndex, SortSequence* sequence, Rectangle* items) {
    // RETURN TRUE WHEN SORT IS COMPLETE
    if(stepIndex >= sequence->stepCount) {
        return true;
    }

    // SWAP THE VALUES TO THAT OF THE CURRENT STEP SNAPSHOT
    int offset;
    for (int i = 0; i < LIST_SIZE; i++) {
        offset = (stepIndex * LIST_SIZE) + i;
        items[i].value = sequence->steps[offset].value;
        items[i].rect_color = sequence->steps[offset].rect_color;
    }
    return false;
}