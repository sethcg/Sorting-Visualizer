#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include <Heap.hpp>
#include <Sort.hpp>
#include <TestSort.hpp>

TEST(HeapSort_Test, ProducesNonEmptySequence) {
    // ARRANGE
    Heap sort;

    // ACT
    SortSequence sequence = TestSort::GenerateSequence(&sort);

    // ASSERT
    EXPECT_GT(sequence.stepCount, 0);
}

TEST(HeapSort_Test, FinalStepIsSorted) {
    // ARRANGE
    Heap sort;

    // ACT
    SortSequence sequence = TestSort::GenerateSequence(&sort);

    // ASSERT
    const std::vector<Rect::Rectangle>& lastStep = *(sequence.steps->at(sequence.stepCount - 1).rects);
    for (int i = 0; i < TestSort::LIST_SIZE; ++i) {
        EXPECT_EQ(lastStep[i].value, i + 1);
        EXPECT_EQ(lastStep[i].state, Rect::State::ORDERED);
    }
}