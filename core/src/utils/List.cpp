#include <SDL3/SDL.h>
#include <List.hpp>
#include <Rect.hpp>

void CreateList(SDL_Renderer *renderer, rectangle* items, int window_width, int window_height) {
    for (int i = 0; i < LIST_SIZE; i++) {
        // ADD DYNAMIC DATA TO RECTANGLE (INDEX, SIZE, ...)
        int rect_height = (i * 10) + 30;
        items[i].index = i;
        items[i].start_x = (i * (RECT_WIDTH + LIST_RECT_SPACING_SIZE)) + LIST_PADDING_SIZE;
        items[i].start_y = (window_height - LIST_PADDING_SIZE) - rect_height;
        items[i].height = rect_height;

        // DRAW CELL SQUARE
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE_FLOAT);
        DrawRect(renderer, items, i);
    }
}

void DrawList(SDL_Renderer *renderer, rectangle* items) {
    // DRAW BACKGROUND COLOR
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    for (int i = 0; i < LIST_SIZE; i++) {
        DrawRect(renderer, items, i);
    }
}

static void DrawRect(SDL_Renderer *renderer, rectangle* items, int index) {
    SDL_FRect rect_item = {
        .x = (float) items[index].start_x,
        .y = (float) items[index].start_y,
        .w = (float) RECT_WIDTH,
        .h = (float) items[index].height
    };
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderFillRect(renderer, &rect_item);
}