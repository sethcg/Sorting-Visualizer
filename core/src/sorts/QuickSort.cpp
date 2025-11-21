#include <stdlib.h>
#include <SDL3/SDL.h>

#include <QuickSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

namespace QuickSort {

    rgb_color GetRectangleColor(bool isOrdered, bool isPivot, bool isSelected) {
        return 
            isOrdered ? rect_green_color :
            isPivot ? rect_red_color : 
            isSelected ? rect_blue_color : rect_base_color;
    }

    int GetPartitionCount(Rectangle* array, int low, int high, int* stepCount) {
        int pivot_value = array[high].value;
    
        // INDEX OF THE SMALLER ELEMENT
        // INDICATES THE RIGHT POSITION OF THE PIVOT (SO FAR)
        int i = low - 1;

        // TRAVERSE MOVING ALL SMALLER ELEMENTS TO THE LEFT SIDE
        for (int j = low; j <= high - 1; j++) {

            // INCREMENT STEP COUNTER
            (*stepCount)++;

            if (array[j].value < pivot_value) {
                i++;
                Swap(array, i, j);

                // INCREMENT STEP COUNTER
                (*stepCount)++;
            }
        }

        // MOVE PIVOT AFTER SMALLER ELEMENTS,
        // THEN RETURN NEW PIVOT INDEX
        Swap(array, i + 1, high);
        return i + 1;
    }

    void GetQuickSortCount(Rectangle* array, int low, int high, int* stepCount) {
        if (low < high) {
            // PARTITION RETURNS THE PIVOT INDEX
            int pivot_index = GetPartitionCount(array, low, high, stepCount);

            // RECURSIVE CALLS FOR SMALLER, GREATER, OR EQUAL ELEMENTS
            GetQuickSortCount(array, low, pivot_index - 1, stepCount);
            GetQuickSortCount(array, pivot_index + 1, high, stepCount);
        }
    }

    int GetStepCount(Rectangle* items) {
        int* stepCount = (int*) calloc(1, sizeof(int));
        
        // COPY ARRAY TO AVOID CHANGING UNDERLYING DATA
        Rectangle* array = CopyArray(items);

        GetQuickSortCount(array, 0, LIST_SIZE - 1, stepCount);

        // INCREMENT STEP COUNTER (ORDERED LIST)
        (*stepCount)++;

        free(array);
        return stepCount[0];
    }

    int Partition(Rectangle* array, int low, int high, int* currentStep, SortSequence sort) {
        // THIS IS THE LOMUTO PARTITION ALGORITHM
        int offset;

        // USING HIGH AS THE PIVOT INDEX (RANDOM WOULD BE OPTIMIZED)
        int pivot_index = high;
        int pivot_value = array[pivot_index].value;
    
        // INDEX OF THE SMALLER ELEMENT
        // INDICATES THE RIGHT POSITION OF THE PIVOT (SO FAR)
        int i = low - 1;

        // TRAVERSE MOVING ALL SMALLER ELEMENTS TO THE LEFT SIDE
        for (int j = low; j <= high - 1; j++) {

            // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
            for (int index = 0; index < LIST_SIZE; index++) {
                offset = (currentStep[0] * LIST_SIZE) + index;
                sort.steps[offset].value = array[index].value;

                // SET RECTANGLE COLOR VALUE
                bool isOrdered = index < low;
                bool isPivot = index == pivot_index;
                bool isSelected = index == i || index == j;
                sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isPivot, isSelected);
            }
            (*currentStep)++;

            if (array[j].value < pivot_value) {
                i++;
                Swap(array, i, j);

                // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
                for (int index = 0; index < LIST_SIZE; index++) {
                    offset = (currentStep[0] * LIST_SIZE) + index;
                    sort.steps[offset].value = array[index].value;

                    // SET RECTANGLE COLOR VALUE
                    bool isOrdered = index < low;
                    bool isPivot = index == pivot_index;
                    bool isSelected = index == i || index == j;
                    sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isPivot, isSelected);
                }
                (*currentStep)++;
            }
        }

        // MOVE PIVOT AFTER SMALLER ELEMENTS,
        // THEN RETURN NEW PIVOT INDEX
        Swap(array, i + 1, high);
        return i + 1;
    }

    void QuickSort(Rectangle* array, int low, int high, int* currentStep, SortSequence sort) {
        if (low < high) {
            // PARTITION RETURNS THE PIVOT INDEX
            int pivot_index = Partition(array, low, high, currentStep, sort);
            
            // RECURSIVE CALLS FOR SMALLER, GREATER, OR EQUAL ELEMENTS
            QuickSort(array, low, pivot_index - 1, currentStep, sort);
            QuickSort(array, pivot_index + 1, high, currentStep, sort);
        }
    }

    SortSequence GetSequence(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        // RUN THE SORT TO CALCULATE THE TOTAL NUMBER OF STEPS
        int stepCount = GetStepCount(items);

        SortSequence sort = create_sort_sequence(stepCount);
        sort.steps = (SortStep*) malloc(LIST_SIZE * stepCount * sizeof(SortStep));

        int* currentStep = (int*) calloc(1, sizeof(int));

        QuickSort(array, 0, LIST_SIZE - 1, currentStep, sort);

        // RECORD FINAL STEP (ORDERED LIST)
        int offset;
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (currentStep[0] * LIST_SIZE) + i;
            sort.steps[offset].value = array[i].value;
            sort.steps[offset].rect_color = rect_green_color;
        }
        
        free(array);
        return sort;
    }

}