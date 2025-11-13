#include <stdlib.h>
#include <SDL3/SDL.h>
#include <List.hpp>
#include <Rect.hpp>

void CreateList(SDL_Renderer *renderer, Rectangle* items, int window_width, int window_height) {
    int drawable_width = window_width - (LIST_MARGIN_MINIMUM * 2);

    int height_offset = ((window_height - (LIST_MARGIN_MINIMUM * 2)) / 10);
    int drawable_height = window_height - (LIST_MARGIN_MINIMUM * 2) - height_offset;

    int rect_width = (drawable_width - (LIST_RECT_PADDING * (LIST_SIZE - 1))) / LIST_SIZE;
    int width_offset = (drawable_width - (LIST_SIZE * (rect_width + LIST_RECT_PADDING))) / 2;

    for (int i = 0; i < LIST_SIZE; i++) {
        int rect_height = (i + 1) * (drawable_height / LIST_SIZE);

        items[i].value = i + 1;
        items[i].width = rect_width;
        items[i].height = (i + 1) * (drawable_height / LIST_SIZE);
        items[i].start_x = LIST_MARGIN_MINIMUM + (i * (rect_width + LIST_RECT_PADDING)) + width_offset;
        items[i].start_y = LIST_MARGIN_MINIMUM + (drawable_height - rect_height) + height_offset;
    }
}

void ResizeList(SDL_Renderer *renderer, Rectangle* items, int window_width, int window_height) {
    int drawable_width = window_width - (LIST_MARGIN_MINIMUM * 2);

    int height_offset = ((window_height - (LIST_MARGIN_MINIMUM * 2)) / 10);
    int drawable_height = window_height - (LIST_MARGIN_MINIMUM * 2) - height_offset;

    int rect_width = (drawable_width - (LIST_RECT_PADDING * (LIST_SIZE - 1))) / LIST_SIZE;
    int width_offset = (drawable_width - (LIST_SIZE * (rect_width + LIST_RECT_PADDING))) / 2;

    for (int i = 0; i < LIST_SIZE; i++) {
        int rect_height = (items[i].value) * (drawable_height / LIST_SIZE);

        items[i].width = rect_width;
        items[i].height = (items[i].value) * (drawable_height / LIST_SIZE);
        items[i].start_x = LIST_MARGIN_MINIMUM + (i * (rect_width + LIST_RECT_PADDING)) + width_offset;
        items[i].start_y = LIST_MARGIN_MINIMUM + (drawable_height - rect_height) + height_offset;
    }
}

void ShuffleList(Rectangle* items) {
    // FISHER-YATES SHUFFLE
    int j, temp = 0;
    for (int i = LIST_SIZE - 1; i > 0; i--) {
        j = rand() % (i + 1);

        // SWAP VALUES
        temp = items[i].value;
        items[i].value = items[j].value;
        items[j].value = temp;
    }
}

void DrawList(SDL_Renderer *renderer, Rectangle* items) {
    // DRAW BACKGROUND COLOR
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    for (int i = 0; i < LIST_SIZE; i++) {
        DrawRect(renderer, items, i);
    }
}

static void DrawRect(SDL_Renderer *renderer, Rectangle* items, int index) {
    SDL_FRect rect_item = {
        .x = (float) items[index].start_x,
        .y = (float) items[index].start_y,
        .w = (float) items[index].width,
        .h = (float) items[index].height,
    };

    // DRAW Rectangle
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderFillRect(renderer, &rect_item);
}