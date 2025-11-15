#ifndef SORT_H
#define SORT_H

#include <SDL3/SDL.h>

#include <List.hpp>
#include <Rect.hpp>

typedef struct {
    int value;
    rgb_color rect_color;
} SortStep;

typedef struct {
    int stepCount;
    SortStep* steps;
} SortSequence;

#define create_sort_sequence(count) { .stepCount = count };

SortSequence GetSortSequence(int sortId, Rectangle* items);

bool IncrementStep(int sortId, int stepIndex, SortSequence sequence, Rectangle* items);

#endif