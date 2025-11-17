#include <stdlib.h>
#include <SDL3/SDL.h>

#include <HeapSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

namespace HeapSort {

    void GetHeapifyCount(Rectangle* array, int size, int index, int* stepCount) {
        int largest = index;
        
        // IF LEFT CHILD IS LARGER, SET AS LARGEST
        int left = 2 * index + 1;
        if (left < size && array[left].value > array[largest].value) {
            largest = left;
        }

        // IF RIGHT CHILD IS LARGER, SET AS LARGEST
        int right = 2 * index + 2;
        if (right < size && array[right].value > array[largest].value) {
            largest = right;
        }

        // IF LARGEST IS NOT THE ROOT, SWAP AND CONTINUE
        if (largest != index) {
            Swap(array, index, largest);

            // INCREMENT STEP COUNTER
            (*stepCount)++;

            // RECURSIVELY HEAPIFY THE AFFECTED SUB-TREE
            GetHeapifyCount(array, size, largest, stepCount);
        }
    }

    int GetStepCount(Rectangle* items) {
        Rectangle* array = CopyArray(items);
        
        int* stepCount = (int*) calloc(1, sizeof(int));

        // BUILD INITIAL HEAP
        for (int i = LIST_SIZE / 2 - 1; i >= 0; i--) {
            GetHeapifyCount(array, LIST_SIZE, i, stepCount);
        }

        // EXTRACT EACH ELEMENT FROM THE HEAP
        for (int i = LIST_SIZE - 1; i > 0; i--) {
            // MOVE CURRENT ROOT TO THE END
            Swap(array, 0, i);

            // INCREMENT THE STEP COUNTER
            (*stepCount)++;

            // CALL HEAPIFY ON THE REDUCED SIZE HEAP
            GetHeapifyCount(array, i, 0, stepCount);
        }

        // INCREMENT FOR FINAL STEP
        (*stepCount)++;

        free(array);
        int test = stepCount[0];
        return stepCount[0];
    }

    void Heapify(Rectangle* array, int size, int index, int* currentStep, SortSequence sort) {
        int largest = index;
                
        // IF LEFT CHILD IS LARGER, SET AS LARGEST
        int left = 2 * index + 1;
        if (left < size && array[left].value > array[largest].value) {
            largest = left;
        }

        // IF RIGHT CHILD IS LARGER, SET AS LARGEST
        int right = 2 * index + 2;
        if (right < size && array[right].value > array[largest].value) {
            largest = right;
        }

        // IF LARGEST IS NOT THE ROOT, SWAP AND CONTINUE
        if (largest != index) {
            Swap(array, index, largest);

            // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
            int offset;
            for (int i = 0; i < LIST_SIZE; i++) {
                offset = ((*currentStep) * LIST_SIZE) + i;
                sort.steps[offset].value = array[i].value;
                
                // SET RECTANGLE COLOR VALUE
                bool isOrdered = i >= size;
                sort.steps[offset].rect_color = GetRectangleColor(isOrdered, false, false);
            }
            (*currentStep)++;

            // RECURSIVELY HEAPIFY THE AFFECTED SUB-TREE
            Heapify(array, size, largest, currentStep, sort);
        }
    }

    SortSequence GetSequence(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        // INITIALLY RUN THE SORT TO CALCULATE THE TOTAL NUMBER OF STEPS
        int stepCount = GetStepCount(items);

        SortSequence sort = create_sort_sequence(stepCount);
        sort.steps = (SortStep*) malloc(LIST_SIZE * stepCount * sizeof(SortStep));

        int offset;
        int* currentStep = (int*) calloc(1, sizeof(int));

        // BUILD INITIAL HEAP
        for (int index = LIST_SIZE / 2 - 1; index >= 0; index--) {
            Heapify(array, LIST_SIZE, index, currentStep, sort);
        }

        // EXTRACT EACH ELEMENT FROM THE HEAP
        for (int index = LIST_SIZE - 1; index > 0; index--) {
            // MOVE CURRENT ROOT TO THE END
            Swap(array, 0, index);

            // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
            for (int i = 0; i < LIST_SIZE; i++) {
                offset = (currentStep[0] * LIST_SIZE) + i;
                sort.steps[offset].value = array[i].value;

                // SET RECTANGLE COLOR VALUE
                bool isOrdered = i >= index;
                sort.steps[offset].rect_color = GetRectangleColor(isOrdered, false, false);
            }
            (*currentStep)++;
            
            // CALL HEAPIFY ON THE REDUCED SIZE HEAP
            Heapify(array, index, 0, currentStep, sort);
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