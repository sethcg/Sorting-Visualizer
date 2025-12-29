#include <stdlib.h>
#include <SDL3/SDL.h>

#include <RadixSort.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>
#include <Utils.hpp>

namespace RadixSort {

    int GetMaxValue(Rectangle* array) {
        int max_value = array[0].value;
        for (int i = 1; i < LIST_SIZE; i++)
            if (array[i].value > max_value) {
                max_value = array[i].value;
            }
        return max_value;
    }

    void GetCountSortCount(Rectangle* array, int exponent, int* stepCount) {
        int* output = (int*) calloc(LIST_SIZE, sizeof(int));

        // ARRAY CONTAINING COUNT OF DIGITS [0 - 9] (SO SIZE OF 10)
        int* count = (int*) calloc(10, sizeof(int));

        // STORE COUNT OCCURENCES
        for (int i = 0; i < LIST_SIZE; i++) {
            count[(array[i].value / exponent) % 10]++;
        }
        
        // CALCULATE ROLLING SUMMATION OF THE COUNT ARRAY,
        // USED FOR NEXT POSITIONS
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // BUILD THE OUTPUT ARRAY
        for (int i = LIST_SIZE - 1; i >= 0; i--) {
            output[count[(array[i].value / exponent) % 10] - 1] = array[i].value;
            
            // DECREMENT DIGIT COUNT
            count[(array[i].value / exponent) % 10]--;
        }

        // OUTPUT IS NOW SORTED BY THE CURRENT DIGIT,
        // COPY OUTPUT TO ARRAY
        for (int i = 0; i < LIST_SIZE; i++) {
            array[i].value = output[i];

            // INCREMENT STEP COUNTER
            (*stepCount)++;
        }
    }

    void GetRadixSortCount(Rectangle* array, int* stepCount) {
        int max_value = GetMaxValue(array);

        // DO COUNT SORT FOR EACH DIGIT
        for (int exponent = 1; max_value / exponent > 0; exponent *= 10) {
            GetCountSortCount(array, exponent, stepCount);
        }
    }

    int GetStepCount(Rectangle* items) {
        int* stepCount = (int*) calloc(1, sizeof(int));
        
        // COPY ARRAY TO AVOID CHANGING UNDERLYING DATA
        Rectangle* array = CopyArray(items);

        GetRadixSortCount(array, stepCount);

        // INCREMENT STEP COUNTER (ORDERED LIST)
        (*stepCount)++;

        free(array);
        return stepCount[0];
    }

    void CountSort(Rectangle* array, int exponent, int* currentStep, SortSequence* sequence) {
        int* output = (int*) calloc(LIST_SIZE, sizeof(int));

        // ARRAY CONTAINING COUNT OF DIGITS [0 - 9] (SO SIZE OF 10)
        int* count = (int*) calloc(10, sizeof(int));

        // STORE COUNT OCCURENCES
        for (int i = 0; i < LIST_SIZE; i++) {
            count[(array[i].value / exponent) % 10]++;
        }
        
        // CALCULATE ROLLING SUMMATION OF THE COUNT ARRAY,
        // USED FOR NEXT POSITIONS
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // BUILD THE OUTPUT ARRAY
        for (int i = LIST_SIZE - 1; i >= 0; i--) {
            output[count[(array[i].value / exponent) % 10] - 1] = array[i].value;
            
            // DECREMENT DIGIT COUNT
            count[(array[i].value / exponent) % 10]--;
        }

        // OUTPUT IS NOW SORTED BY THE CURRENT DIGIT,
        // COPY OUTPUT TO ARRAY
        int previous_index;
        for (int i = 0; i < LIST_SIZE; i++) {

            // GET PREVIOUS VALUE TO BETTER VISUAL SWAPPING
            for (int j = 0; j < LIST_SIZE; j++) {
                if(output[i] == array[j].value) {
                    previous_index = j;
                    break;
                }
            }
            array[previous_index].value = array[i].value;
            array[i].value = output[i];
            
            // RECORD THE SORTING STEP (SNAPSHOT OF THE ARRAY)
            int offset;
            for (int index = 0; index < LIST_SIZE; index++) {
                offset = (currentStep[0] * LIST_SIZE) + index;
                sequence->steps[offset].value = array[index].value;
                sequence->steps[offset].rect_color = rect_base_color;
            }
            (*currentStep)++;
        }
    }

    void RadixSort(Rectangle* array, int* currentStep, SortSequence* sequence) {
        int max_value = GetMaxValue(array);

        // DO COUNT SORT FOR EACH DIGIT
        for (int exponent = 1; max_value / exponent > 0; exponent *= 10) {
            CountSort(array, exponent, currentStep, sequence);
        }
    }

    void SetSequence(Rectangle* items, SortSequence* sequence) {
        Rectangle* array = CopyArray(items);

        // RUN THE SORT TO CALCULATE THE TOTAL NUMBER OF STEPS
        sequence->stepCount = GetStepCount(items);
        sequence->steps = (SortStep*) malloc(LIST_SIZE * sequence->stepCount * sizeof(SortStep));

        int* currentStep = (int*) calloc(1, sizeof(int));

        RadixSort(array, currentStep, sequence);

        // RECORD FINAL STEP (ORDERED LIST)
        int offset;
        for (int i = 0; i < LIST_SIZE; i++) {
            offset = (currentStep[0] * LIST_SIZE) + i;
            sequence->steps[offset].value = array[i].value;
            sequence->steps[offset].rect_color = rect_green_color;
        }
        
        free(array);
    }

}