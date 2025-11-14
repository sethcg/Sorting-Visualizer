#include <stdlib.h>
#include <algorithm>

#include <SDL3/SDL.h>

#include <BubbleSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>

namespace BubbleSort {

    int GetStepCount_BubbleSort(Rectangle* items) {
        Rectangle* array = (Rectangle*) malloc(LIST_SIZE * sizeof(Rectangle));
        memcpy(array, items, LIST_SIZE * sizeof(Rectangle));

        int stepCount = 0;

        int temp;
        bool swapped;
        for (int i = 0; i < LIST_SIZE - 1; i++) {
            swapped = false;
            for (int j = 0; j < LIST_SIZE - i - 1; j++) {
                if (array[j].value > array[j + 1].value) {
                    temp = array[j].value;
                    array[j].value = array[j + 1].value;
                    array[j + 1].value = temp;
                    swapped = true;

                    // INCREMENT THE STEP COUNTER
                    stepCount++;
                }
            }
            if (!swapped) break;
        }

        free(array);
        return stepCount;
    }

    SortSequence GetSequence_BubbleSort(Rectangle* items) {
        // INITIALLY RUN THE BUBBLE SORT CALCULATING THE TOTAL NUMBER OF STEPS
        int stepCount = GetStepCount_BubbleSort(items);

        SortSequence sort = create_sort_sequence(stepCount);
        sort.steps = (int*) malloc(LIST_SIZE * stepCount * sizeof(int));

        Rectangle* array = (Rectangle*) malloc(LIST_SIZE * sizeof(Rectangle));
        memcpy(array, items, LIST_SIZE * sizeof(Rectangle));

        int currentStep = 0;
        int temp, offset;
        bool swapped;
        for (int index = 0; index < LIST_SIZE - 1; index++) {
            swapped = false;
            for (int j = 0; j < LIST_SIZE - index - 1; j++) {
                if (array[j].value > array[j + 1].value) {
                    // SWAP VALUES
                    temp = array[j].value;
                    array[j].value = array[j + 1].value;
                    array[j + 1].value = temp;
                    swapped = true;

                    // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
                    for (int i = 0; i < LIST_SIZE; i++) {
                        offset = (currentStep * LIST_SIZE) + i;
                        sort.steps[offset] = array[i].value;
                    }
                    currentStep++;
                }
            }

            // BREAK WHEN NO ELEMENTS SWAPPED (OPTIMIZED)
            if (!swapped) break;
        }

        free(array);
        return sort;
    }

    bool IncrementStep_BubbleSort(int index, SortSequence sequence, Rectangle* items) {
        // RETURN TRUE WHEN SORT IS COMPLETE
        if(index >= sequence.stepCount) return true;

        // SWAP THE VALUES TO THAT OF THE CURRENT STEP SNAPSHOT
        int offset;
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (index * LIST_SIZE) + i;
            items[i].value = sequence.steps[offset];
        }
        return false;
    }

}