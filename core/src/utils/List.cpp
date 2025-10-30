#include <SDL3/SDL.h>
#include <List.hpp>
#include <Rect.hpp>

void CreateList(SDL_Renderer *renderer, rectangle* items, int window_width, int window_height) {
    float drawable_width = window_width - (LIST_MARGIN_MINIMUM * 2);
    float drawable_height = window_height - (LIST_MARGIN_MINIMUM * 2);

    float rect_width = (drawable_width - (LIST_RECT_PADDING * (LIST_SIZE - 1))) / LIST_SIZE;
    float rect_total_width = rect_width + LIST_RECT_PADDING;

    float window_width_padding = LIST_MARGIN_MINIMUM + ((drawable_width - (rect_total_width * LIST_SIZE)) / 2);

    float rect_height = 0;
    for (int i = 0; i < LIST_SIZE; i++) {
        rect_height = (i * 10) + 30;

        items[i].index = i;
        items[i].value = i + 1;
        items[i].height = rect_height;
        items[i].width = rect_width;
        items[i].start_x = (i * rect_total_width) + window_width_padding;
        items[i].start_y = (window_height - LIST_MARGIN_MINIMUM) - rect_height;
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
        .w = (float) items[index].width,
        .h = (float) items[index].height,
    };

    // DRAW RECTANGLE
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderFillRect(renderer, &rect_item);
}