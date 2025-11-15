#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

#include <BubbleSort.hpp>
#include <CocktailSort.hpp>

SortSequence GetSortSequence(int sortId, Rectangle* items) {
    switch(sortId) {
        case 0:
            return BubbleSort::GetSequence_BubbleSort(items);
        case 1:
            return CocktailSort::GetSequence_CocktailSort(items);
        case 2:
            SDL_Log("Start Heap Sort...");
            break;
        case 3:
            SDL_Log("Start Insertion Sort...");
            break;
        case 4:
            SDL_Log("Start Merge Sort...");
            break;
        case 5:
            SDL_Log("Start Quick Sort...");
            break;
        case 6:
            SDL_Log("Start Radix Sort...");
            break;
        case 7:
            SDL_Log("Start Selection Sort...");
            break;
    }
    return { };
}

bool IncrementStep(int stepIndex, SortSequence sequence, Rectangle* items) {
    // RETURN TRUE WHEN SORT IS COMPLETE
    if(stepIndex >= sequence.stepCount) return true;

    // SWAP THE VALUES TO THAT OF THE CURRENT STEP SNAPSHOT
    int offset;
    for (int i = 0; i < LIST_SIZE; i++) {
        offset = (stepIndex * LIST_SIZE) + i;
        items[i].value = sequence.steps[offset].value;
        items[i].rect_color = sequence.steps[offset].rect_color;
    }
    return false;
}