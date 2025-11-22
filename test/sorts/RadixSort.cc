#include <gtest/gtest.h>
#include <SDL3/SDL.h>

#include <TestUtils.hpp>

#include <RadixSort.hpp>
#include <List.hpp>
#include <Rect.hpp>

using namespace RadixSort;

TEST(RadixSort_Test, GetStepCount_GreaterThanOne) {
    // ARRANGE
    SDL_Renderer* renderer = (SDL_Renderer*) malloc(sizeof(Rectangle));
    Rectangle* items = (Rectangle*) malloc(LIST_SIZE * sizeof(Rectangle));

    CreateList(renderer, items, WINDOW_WIDTH, WINDOW_HEIGHT);
    ShuffleList(items);

    // ACT
    int stepCount = GetStepCount(items);

    // ASSERT
    EXPECT_TRUE(stepCount > 1);
}

TEST(RadixSort_Test, GetSequence_CorrectOrder) {
    // ARRANGE
    SDL_Renderer* renderer = (SDL_Renderer*) malloc(sizeof(Rectangle));
    Rectangle* items = (Rectangle*) malloc(LIST_SIZE * sizeof(Rectangle));

    CreateList(renderer, items, WINDOW_WIDTH, WINDOW_HEIGHT);
    ShuffleList(items);

    // ACT
    SortSequence sequence = GetSequence(items);

    // ASSERT
    EXPECT_TRUE(sequence.stepCount > 0);

    int lastStep = sequence.stepCount - 1;
    int offset;
    for (int i = 0; i < LIST_SIZE; i++) {
        offset = (lastStep * LIST_SIZE) + i;
        EXPECT_EQ(sequence.steps[offset].value, (i + 1));
    }
}