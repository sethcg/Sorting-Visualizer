#include <memory>

#include <gtest/gtest.h>

#include <TestUtils.hpp>

#include <List.hpp>
#include <Rect.hpp>

TEST(List_Test, CreateList_ValueAssigned) {
    // ARRANGE
    std::unique_ptr<Rectangle[]> itemPtr = std::make_unique<Rectangle[]>(LIST_SIZE);
    Rectangle* items = itemPtr.get();

    // ACT
    CreateList(items, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ASSERT
    for (int i = 0; i < LIST_SIZE; i++) {
        EXPECT_EQ(items[i].value, (i + 1));
    }
}