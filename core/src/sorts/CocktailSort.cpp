#include <stdlib.h>
#include <SDL3/SDL.h>

#include <CocktailSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

namespace CocktailSort {

    int GetStepCount(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        int temp;
        int stepCount = 0;

        bool swapped = true;
        int start = 0;
        int end = LIST_SIZE - 1;

        while (swapped) {
            // RESET SWAPPED FLAG
            swapped = false;

            // FROM LEFT TO RIGHT, BUBBLE THE HIGHEST VALUE TO THE END
            for (int index = start; index < end; ++index) {
                if (array[index].value > array[index + 1].value) {
                    Swap(array, index, (index + 1));
                    swapped = true;

                    // INCREMENT THE STEP COUNTER
                    stepCount++;
                }
            }

            // BREAK WHEN NO ELEMENTS SWAPPED (OPTIMIZED)
            if (!swapped) break;

            // RESET SWAPPED FLAG
            swapped = false;

            // MOVE END POINT BACK ONCE, 
            // BECAUSE THAT INDEX IS SORTED
            --end;

            // FROM RIGHT TO LEFT, BUBBLE THE LOWEST VALUE TO THE START
            for (int index = end - 1; index >= start; --index) {
                if (array[index].value > array[index + 1].value) {
                    Swap(array, index, (index + 1));
                    swapped = true;

                    // INCREMENT THE STEP COUNTER
                    stepCount++;
                }
            }

            // MOVE START POINT FORWARD ONCE, 
            // BECAUSE THAT INDEX IS NOW SORTED
            ++start;
        }

        // INCREMENT FOR FINAL STEP
        stepCount++; 

        free(array);
        return stepCount;
    }

    SortSequence GetSequence(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        // INITIALLY RUN THE SORT TO CALCULATE THE TOTAL NUMBER OF STEPS
        int stepCount = GetStepCount(items);

        SortSequence sort = create_sort_sequence(stepCount);
        sort.steps = (SortStep*) malloc(LIST_SIZE * stepCount * sizeof(SortStep));

        int currentStep = 0;
        int temp, offset;

        bool swapped = true;
        int start = 0;
        int end = LIST_SIZE - 1;

        while (swapped) {
            // RESET SWAPPED FLAG
            swapped = false;

            // FROM LEFT TO RIGHT, BUBBLE THE HIGHEST VALUE TO THE END
            for (int index = start; index < end; ++index) {
                if (array[index].value > array[index + 1].value) {
                    Swap(array, index, (index + 1));
                    swapped = true;

                    // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
                    for (int i = 0; i < LIST_SIZE; i++) {
                        offset = (currentStep * LIST_SIZE) + i;
                        sort.steps[offset].value = array[i].value;

                        // SET RECTANGLE COLOR VALUE
                        bool isOrdered = i > end || i < start;
                        bool isCurrent = i == index;
                        bool isChecking = i == (index + 1);
                        sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isCurrent, isChecking);
                    }
                    currentStep++;
                }
            }

            // BREAK WHEN NO ELEMENTS SWAPPED (OPTIMIZED)
            if (!swapped) break;

            // RESET SWAPPED FLAG
            swapped = false;

            // MOVE END POINT BACK ONCE, 
            // BECAUSE THAT INDEX IS SORTED
            --end;

            // FROM RIGHT TO LEFT, BUBBLE THE LOWEST VALUE TO THE START
            for (int index = end - 1; index >= start; --index) {
                if (array[index].value > array[index + 1].value) {
                    Swap(array, index, (index + 1));
                    swapped = true;

                    // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
                    for (int i = 0; i < LIST_SIZE; i++) {
                        offset = (currentStep * LIST_SIZE) + i;
                        sort.steps[offset].value = array[i].value;

                        // SET RECTANGLE COLOR
                        bool isOrdered = i > end || i < start;
                        bool isCurrent = i == (index + 1);
                        bool isChecking = i == index;
                        sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isCurrent, isChecking);
                    }
                    currentStep++;
                }
            }

            // MOVE START POINT FORWARD ONCE, 
            // BECAUSE THAT INDEX IS NOW SORTED
            ++start;
        }

        // RECORD FINAL STEP (ORDERED LIST)
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (currentStep * LIST_SIZE) + i;
            sort.steps[offset].value = array[i].value;
            sort.steps[offset].rect_color = rect_green_color;
        }
    
        free(array);
        return sort;
    }

}