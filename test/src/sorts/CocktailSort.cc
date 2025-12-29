#include <memory>

#include <gtest/gtest.h>

#include <TestUtils.hpp>

#include <CocktailSort.hpp>
#include <List.hpp>
#include <Rect.hpp>

using namespace CocktailSort;

TEST(CocktailSort_Test, GetStepCount_One) {
    // ARRANGE
    std::unique_ptr<Rectangle[]> itemPtr = std::make_unique<Rectangle[]>(LIST_SIZE);
    
    Rectangle* items = itemPtr.get();

    CreateList(items, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ACT
    int stepCount = GetStepCount(items);

    // ASSERT
    EXPECT_EQ(stepCount, 1);
}

TEST(CocktailSort_Test, GetStepCount_GreaterThanOne) {
    // ARRANGE
    std::unique_ptr<Rectangle[]> itemPtr = std::make_unique<Rectangle[]>(LIST_SIZE);

    Rectangle* items = itemPtr.get();

    CreateList(items, WINDOW_WIDTH, WINDOW_HEIGHT);
    ShuffleList(items);

    // ACT
    int stepCount = GetStepCount(items);

    // ASSERT
    EXPECT_TRUE(stepCount > 1);
}

TEST(CocktailSort_Test, SetSequence_CorrectOrder) {
    // ARRANGE
    std::unique_ptr<Rectangle[]> itemPtr = std::make_unique<Rectangle[]>(LIST_SIZE);
    std::unique_ptr<SortSequence> sequencePtr = std::make_unique<SortSequence>();

    Rectangle* items = itemPtr.get();
    SortSequence* sequence = sequencePtr.get();

    CreateList(items, WINDOW_WIDTH, WINDOW_HEIGHT);
    ShuffleList(items);

    // ACT
    SetSequence(items, sequence);

    // ASSERT
    ASSERT_NE(sequence, nullptr);
    EXPECT_TRUE(sequence->stepCount > 0);

    int lastStep = sequence->stepCount - 1;
    int offset;
    for (int i = 0; i < LIST_SIZE; i++) {
        offset = (lastStep * LIST_SIZE) + i;
        EXPECT_EQ(sequence->steps[offset].value, (i + 1));
    }
}