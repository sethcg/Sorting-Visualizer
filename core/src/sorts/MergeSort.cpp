#include <stdlib.h>
#include <SDL3/SDL.h>

#include <MergeSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

#define min(a, b) (((a) < (b)) ? (a) : (b))

#define rect_red_color rgb_color { .r = 200, .g = 60, .b = 40 }

namespace MergeSort {

    rgb_color GetRectangleColor(bool isSelected, bool inGrouping) {
        return 
            isSelected ? rect_red_color : 
            inGrouping ? rect_blue_color : rect_base_color;
    }

    void GetMergeCount(Rectangle* array, int left, int middle, int right, int* stepCount) {
        const int left_size = middle - left + 1;
        const int right_size = right - middle;

        int* left_array = (int*) malloc(left_size * sizeof(int));
        int* right_array = (int*) malloc(right_size * sizeof(int));

        // COPY DATA INTO TEMP LEFT/RIGHT ARRAYS
        for (int i = 0; i < left_size; i++) {
            left_array[i] = array[left + i].value;
        }
        for (int j = 0; j < right_size; j++) {
            right_array[j] = array[middle + 1 + j].value;
        }

        int offset;
        int i = 0, r = 0;
        int index = left;

        // MERGE THE LEFT/RIGHT ARRAYS
        while (i < left_size && r < right_size) {

            // INCREMENT STEP COUNT
            (*stepCount)++;

            if (left_array[i] <= right_array[r]) {
                array[index].value = left_array[i];
                i++;
            } else {
                array[index].value = right_array[r];
                r++;
            }
            index++;
        }

        // COPY REMAINING ELEMENTS FROM THE LEFT ARRAY
        while (i < left_size) {
            array[index].value = left_array[i];
            i++;
            index++;
        }

        // COPY REMAINING ELEMENTS FROM THE RIGHT ARRAY
        while (r < right_size) {
            array[index].value = right_array[r];
            r++;
            index++;
        }

        // INCREMENT STEP COUNT
        (*stepCount)++;
    }
    
    int GetMergeSortCount(Rectangle* items) {
        int* stepCount = (int*) calloc(1, sizeof(int));
        
        // COPY ARRAY TO AVOID CHANGING UNDERLYING DATA
        Rectangle* array = CopyArray(items);

        // ITERATE THROUGH THE SUBARRAYS
        for (int currentSize = 1; currentSize <= LIST_SIZE - 1; currentSize = 2 * currentSize) {
            // PICK THE STARTING POINT OF DIFFERENT SUBARRAYS
            for (int leftStart = 0; leftStart < LIST_SIZE - 1; leftStart += 2 * currentSize) {

                // FIND THE ENDPOINTS OF THE SUBARRAYS GETTING MERGED
                int mid = min(leftStart + currentSize - 1, LIST_SIZE - 1);
                int rightEnd = min(leftStart + 2 * currentSize - 1, LIST_SIZE - 1);
                
                // MERGE THE SUBARRAYS
                GetMergeCount(array, leftStart, mid, rightEnd, stepCount);
            }
        }

        // INCREMENT STEP COUNT (ORDERED LIST)
        (*stepCount)++;

        return stepCount[0];
    }

    void Merge(Rectangle* array, int left, int middle, int right, int* currentStep, SortSequence sort, int currentSize) {
        const int left_size = middle - left + 1;
        const int right_size = right - middle;

        int* left_array = (int*) malloc(left_size * sizeof(int));
        int* right_array = (int*) malloc(right_size * sizeof(int));

        // COPY DATA INTO TEMP LEFT/RIGHT ARRAYS
        for (int i = 0; i < left_size; i++) {
            left_array[i] = array[left + i].value;
        }
        for (int j = 0; j < right_size; j++) {
            right_array[j] = array[middle + 1 + j].value;
        }

        int offset;
        int l_index = 0, r_index = 0;
        int index = left;

        // MERGE THE LEFT/RIGHT ARRAYS
        while (l_index < left_size && r_index < right_size) {

            for (int i = 0; i < LIST_SIZE; i++) {
                offset = (currentStep[0] * LIST_SIZE) + i;
                sort.steps[offset].value = array[i].value;
                sort.steps[offset].rect_color = rect_base_color;

                bool inGrouping = i >= left && i <= right;
                bool isSelected = (left + l_index) == i || (right - r_index) == i;
                sort.steps[offset].rect_color = GetRectangleColor(isSelected, inGrouping);
            }
            (*currentStep)++;

            if (left_array[l_index] <= right_array[r_index]) {
                array[index].value = left_array[l_index];
                l_index++;
            } else {
                array[index].value = right_array[r_index];
                r_index++;
            }
            index++;
        }

        // COPY REMAINING ELEMENTS FROM THE LEFT ARRAY
        while (l_index < left_size) {
            array[index].value = left_array[l_index];
            l_index++;
            index++;
        }

        // COPY REMAINING ELEMENTS FROM THE RIGHT ARRAY
        while (r_index < right_size) {
            array[index].value = right_array[r_index];
            r_index++;
            index++;
        }

        // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (currentStep[0] * LIST_SIZE) + i;
            sort.steps[offset].value = array[i].value;

            bool inGrouping = i >= left && i <= right;
            bool isSelected = (left + l_index) == i || (right - r_index) == i;
            sort.steps[offset].rect_color = GetRectangleColor(isSelected, inGrouping);
        }
        (*currentStep)++;
    }

    SortSequence GetSequence(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        // RUN THE SORT TO CALCULATE THE TOTAL NUMBER OF STEPS
        int stepCount = GetMergeSortCount(items);

        SortSequence sort = create_sort_sequence(stepCount);
        sort.steps = (SortStep*) malloc(LIST_SIZE * stepCount * sizeof(SortStep));

        int offset;
        int* currentStep = (int*) calloc(1, sizeof(int));

        // ITERATE THROUGH THE SUBARRAYS (BOTTOM-UP* MERGE SORT)
        for (int currentSize = 1; currentSize <= LIST_SIZE - 1; currentSize = 2 * currentSize) {
            // PICK THE STARTING POINT OF DIFFERENT SUBARRAYS
            for (int leftStart = 0; leftStart < LIST_SIZE - 1; leftStart += 2 * currentSize) {

                // FIND THE ENDPOINTS OF THE SUBARRAYS GETTING MERGED
                int mid = min(leftStart + currentSize - 1, LIST_SIZE - 1);
                int rightEnd = min(leftStart + 2 * currentSize - 1, LIST_SIZE - 1);
                
                // MERGE THE SUBARRAYS
                Merge(array, leftStart, mid, rightEnd, currentStep, sort, currentSize);
            }
        }

        // RECORD FINAL STEP (ORDERED LIST)
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (currentStep[0] * LIST_SIZE) + i;
            sort.steps[offset].value = array[i].value;
            sort.steps[offset].rect_color = rect_green_color;
        }
        
        free(array);
        return sort;
    }

}