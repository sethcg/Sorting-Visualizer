#ifndef SORT_H
#define SORT_H

#include <cstdlib>
#include <memory>

#include <SDL3/SDL.h>

#include <List.hpp>
#include <Rect.hpp>

struct SortStep {
    int value;
    rgb_color rect_color;
};

struct SortSequence {
    int stepCount = 0;
    SortStep* steps = nullptr;

    // DECONSTRUCTOR
    ~SortSequence() { std::free(steps); }
};

void UpdateSequence(int sortId, Rectangle* items, SortSequence* sequence);

bool IncrementStep(int stepIndex, SortSequence* sequence, Rectangle* items);

#endif