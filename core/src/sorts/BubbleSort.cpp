#include <stdlib.h>
#include <SDL3/SDL.h>

#include <BubbleSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

namespace BubbleSort {

    int GetStepCount(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        int stepCount = 1;

        bool swapped;
        for (int i = 0; i < LIST_SIZE - 1; i++) {
            swapped = false;
            for (int j = 0; j < LIST_SIZE - i - 1; j++) {
                if (array[j].value > array[j + 1].value) {
                    Swap(array, j, (j + 1));
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

    void SetSequence(Rectangle* items, SortSequence* sequence) {
        Rectangle* array = CopyArray(items);

        // INITIALLY RUN THE SORT TO CALCULATE THE TOTAL NUMBER OF STEPS
        sequence->stepCount = GetStepCount(items);
        sequence->steps = (SortStep*) malloc(LIST_SIZE * sequence->stepCount * sizeof(SortStep));

        int currentStep = 0;
        int offset;
        bool swapped;
        for (int index = 0; index < LIST_SIZE - 1; index++) {
            swapped = false;
            for (int j = 0; j < LIST_SIZE - index - 1; j++) {
                if (array[j].value > array[j + 1].value) {
                    Swap(array, j, (j + 1));
                    swapped = true;

                    // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
                    for (int i = 0; i < LIST_SIZE; i++) {
                        offset = (currentStep * LIST_SIZE) + i;
                        sequence->steps[offset].value = array[i].value;

                        // SET RECTANGLE COLOR VALUE
                        bool isOrdered = i >= (LIST_SIZE - index);
                        bool isCurrent = i == j;
                        bool isChecking = i == (j + 1);
                        sequence->steps[offset].rect_color = GetRectangleColor(isOrdered, isCurrent, isChecking);
                    }
                    currentStep++;
                }
            }

            // BREAK WHEN NO ELEMENTS SWAPPED (OPTIMIZED)
            if (!swapped) break;
        }

        // RECORD FINAL STEP (ORDERED LIST)
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (currentStep * LIST_SIZE) + i;
            sequence->steps[offset].value = array[i].value;
            sequence->steps[offset].rect_color = rect_green_color;
        }
        free(array);
    }

}