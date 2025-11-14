#include <SDL3/SDL.h>

#include <Rect.hpp>
#include <Sort.hpp>

#include <BubbleSort.hpp>

SortSequence GetSortSequence(int sortId, Rectangle* items) {
    switch(sortId) {
        case 0:
            return BubbleSort::GetSequence_BubbleSort(items);
            break;
        case 1:
            SDL_Log("Start Cocktail Sort...");
            break;
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

bool IncrementStep(int sortId, int stepIndex, SortSequence sequence, Rectangle* items) {
    switch(sortId) {
        case 0:
            return BubbleSort::IncrementStep_BubbleSort(stepIndex, sequence, items);
        case 1:
            SDL_Log("Iterate Cocktail Sort...");
            break;
        case 2:
            SDL_Log("Iterate Heap Sort...");
            break;
        case 3:
            SDL_Log("Iterate Insertion Sort...");
            break;
        case 4:
            SDL_Log("Iterate Merge Sort...");
            break;
        case 5:
            SDL_Log("Iterate Quick Sort...");
            break;
        case 6:
            SDL_Log("Iterate Radix Sort...");
            break;
        case 7:
            SDL_Log("Iterate Selection Sort...");
            break;
    }
    return true;
}