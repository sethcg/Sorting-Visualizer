#include <gtest/gtest.h>
#include <SDL3/SDL.h>

#include <TestUtils.hpp>

#include <List.hpp>
#include <Rect.hpp>

TEST(List_Test, CreateList_ValueAssigned) {
    // ARRANGE
    SDL_Renderer* renderer = (SDL_Renderer*) malloc(sizeof(Rectangle));
    Rectangle* items = (Rectangle*) malloc(LIST_SIZE * sizeof(Rectangle));

    // ACT
    CreateList(items, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ASSERT
    for (int i = 0; i < LIST_SIZE; i++) {
        EXPECT_EQ(items[i].value, (i + 1));
    }
}