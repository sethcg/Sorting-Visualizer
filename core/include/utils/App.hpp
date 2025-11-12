#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <imgui.h>

#include <Rect.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MINIMUM_WINDOW_WIDTH 400
#define MINIMUM_WINDOW_HEIGHT 400

typedef struct AppContext {
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    ImDrawData* data;

    int sortId;
    char* sortOptions[8];
    rectangle* items;
} AppContext;

#endif