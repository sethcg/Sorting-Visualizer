#include <stdlib.h>
#include <SDL3/SDL.h>

#include <InsertionSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

namespace InsertionSort {

    int GetStepCount(Rectangle* items) {
        Rectangle* array = CopyArray(items);

        int stepCount = 1;

        for (int index = 1; index < LIST_SIZE; ++index) {
            int key = array[index].value;
            int j = index - 1;

            while (j >= 0 && array[j].value > key) {
                array[j + 1].value = array[j].value;
                j = j - 1;

                // INCREMENT THE STEP COUNTER (CHECKING)
                stepCount++;
            }
            array[j + 1].value = key;

            // INCREMENT THE STEP COUNTER
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

        for (int index = 1; index < LIST_SIZE; ++index) {
            int key = array[index].value;
            int j = index - 1;

            while (j >= 0 && array[j].value > key) {
                array[j + 1].value = array[j].value;
                j = j - 1;

                // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
                for (int i = 0; i < LIST_SIZE; i++) {
                    offset = (currentStep * LIST_SIZE) + i;
                    sort.steps[offset].value = array[i].value;

                    // SET RECTANGLE COLOR VALUE
                    bool isCurrent = i == (index - 1);
                    bool isChecking = i == j;
                    bool isOrdered = !isCurrent && !isChecking && i < index;
                    sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isCurrent, isChecking);
                }
                currentStep++;
            }
            array[j + 1].value = key;

            // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
            for (int i = 0; i < LIST_SIZE; i++) {
                offset = (currentStep * LIST_SIZE) + i;
                sort.steps[offset].value = array[i].value;

                // SET RECTANGLE COLOR VALUE
                bool isCurrent = i == (index - 1);
                bool isChecking = i == j;
                bool isOrdered = !isCurrent && !isChecking && i < index;
                sort.steps[offset].rect_color = GetRectangleColor(isOrdered, isCurrent, isChecking);
            }
            currentStep++;
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