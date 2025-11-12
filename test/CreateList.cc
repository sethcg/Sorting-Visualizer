#include <gtest/gtest.h>
#include <SDL3/SDL.h>

#include <TestUtils.hpp>
#include <List.hpp>
#include <Rect.hpp>

TEST(CoreTest, CreateListValueAssigned) {
    // ARRANGE
    SDL_Renderer* renderer = (SDL_Renderer*) malloc(sizeof(rectangle));
    rectangle* items = (rectangle*) malloc(LIST_SIZE * sizeof(rectangle));

    // ACT
    CreateList(renderer, items, WINDOW_WIDTH, WINDOW_HEIGHT);

    // ASSERT
    for (int i = 0; i < LIST_SIZE; i++) {
        EXPECT_EQ(items[i].value, (i + 1));
    }
}