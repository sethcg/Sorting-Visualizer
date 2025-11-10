#include <gtest/gtest.h>

#include <SDL3/SDL.h>

#include <Utils.hpp>

#include <List.hpp>
#include <Rect.hpp>

TEST(CoreTest, CreateListTest) {
    // ARRANGE
    srand(time(NULL));
    AppContext* appContext = (AppContext*) SDL_malloc(sizeof(AppContext));
    appContext->items = (rectangle*) malloc(LIST_SIZE * sizeof(rectangle));
    
    // ACT
    CreateList(appContext->renderer, appContext->items, 800, 800);

    // ASSERT
    for (int i = 0; i < LIST_SIZE; i++) {
        EXPECT_EQ(appContext->items[i].value, (i + 1));
    }
}