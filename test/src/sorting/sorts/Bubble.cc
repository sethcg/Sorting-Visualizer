#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include <Bubble.hpp>
#include <Sort.hpp>
#include <TestSort.hpp>

TEST(BubbleSort_Test, ProducesNonEmptySequence) {
    // ARRANGE
    Bubble sort;

    // ACT
    SortSequence sequence = TestSort::GenerateSequence(&sort);

    // ASSERT
    EXPECT_GT(sequence.stepCount, 0);
}

TEST(BubbleSort_Test, FinalStepIsSorted) {
    // ARRANGE
    Bubble sort;

    // ACT
    SortSequence sequence = TestSort::GenerateSequence(&sort);

    // ASSERT
    const std::vector<Rect::Rectangle>& lastStep = *(sequence.steps->at(sequence.stepCount - 1).rects);
    for (int i = 0; i < TestSort::LIST_SIZE; ++i) {
        EXPECT_EQ(lastStep[i].value, i + 1);
        EXPECT_EQ(lastStep[i].state, Rect::State::ORDERED);
    }
}