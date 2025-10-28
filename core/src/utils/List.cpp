#include <SDL3/SDL.h>
#include <List.hpp>
#include <Rect.hpp>

void DrawList(SDL_Renderer *renderer, rectangle* items, int window_width, int window_height) {
    // DRAW BACKGROUND COLOR
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    for (int i = 0; i < LIST_SIZE; i++) {
        DrawRect(renderer, items, i, window_width, window_height);
    }
}

static void DrawRect(SDL_Renderer *renderer, rectangle* items, int index, int window_width, int window_height) {
    float drawable_width = window_width - (LIST_MARGIN_MINIMUM * 2);
    
    // TODO: FIX HEIGHT TO ALSO BE ADJUSTABLE
    // float drawable_height = window_height - (LIST_MARGIN_MINIMUM * 2);

    float rect_width = (drawable_width - (LIST_RECT_PADDING * (LIST_SIZE - 1))) / LIST_SIZE;
    float rect_total_width = rect_width + LIST_RECT_PADDING;

    // TODO: MAKE HEIGHT MORE RESPONSIVE
    float rect_height = (index * 10) + 30;

    float window_width_padding = LIST_MARGIN_MINIMUM + ((drawable_width - (rect_total_width * LIST_SIZE)) / 2);
    SDL_FRect rect_item = {
        .x = (index * rect_total_width) + window_width_padding,
        .y = (window_height - LIST_MARGIN_MINIMUM) - rect_height,
        .w = rect_width,
        .h = rect_height
    };

    // DRAW RECTANGLE
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderFillRect(renderer, &rect_item);
}