#include <stdlib.h>
#include <SDL3/SDL.h>

#include <SelectionSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

namespace SelectionSort {

    rgb_color GetRectangleColor(bool isOrdered, bool isMinimum, bool isSelected) {
        return 
            isOrdered ? rect_green_color :
            isMinimum ? rect_red_color : 
            isSelected ? rect_blue_color : rect_base_color;
    }

    int GetStepCount(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        int stepCount = 1;

        for (int i = 0; i < LIST_SIZE - 1; ++i) {
            int minimum_index = i;

            // ITERATE THROUGH UNSORTED VALUES TO FIND MINIMUM
            for (int j = i + 1; j < LIST_SIZE; ++j) {

                // INCREMENT STEP COUNT (COMPARE)
                stepCount++;

                if (array[j].value < array[minimum_index].value) {
                    minimum_index = j; 
                }
            }

            Swap(array, i, minimum_index);
            
            // INCREMENT STEP COUNT (SWAP)
            stepCount++;
        }

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
        int offset;

        for (int i = 0; i < LIST_SIZE - 1; ++i) {
            int minimum_index = i;

            // ITERATE THROUGH UNSORTED VALUES TO FIND MINIMUM
            for (int j = i + 1; j < LIST_SIZE; ++j) {

                // RECORD THE SORTING STEP (COMPARE)
                for (int index = 0; index < LIST_SIZE; index++) {
                    offset = (currentStep * LIST_SIZE) + index;
                    sort.steps[offset].value = array[index].value;

                    // SET RECTANGLE COLOR VALUE
                    bool isOrdered = index < i;
                    bool isMinimum = index == minimum_index;
                    bool isSelected = index == j;
                    sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isMinimum, isSelected);
                }
                currentStep++;

                if (array[j].value < array[minimum_index].value) {
                    minimum_index = j; 
                }
            }

            Swap(array, i, minimum_index);
            
            // RECORD THE SORTING STEP (SWAP)
            for (int index = 0; index < LIST_SIZE; index++) {
                offset = (currentStep * LIST_SIZE) + index;
                sort.steps[offset].value = array[index].value;

                // SET RECTANGLE COLOR VALUE
                bool isOrdered = index < i;
                bool isMinimum = index == minimum_index;
                bool isSelected = index == i;
                sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isMinimum, isSelected);
            }
            currentStep++;
        }

        // RECORD THE SORTING STEP (ORDERED LIST)
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (currentStep * LIST_SIZE) + i;
            sort.steps[offset].value = array[i].value;
            sort.steps[offset].rect_color = rect_green_color;
        }

        free(array);
        return sort;
    }

}