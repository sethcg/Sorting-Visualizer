#include <SDL3/SDL.h>

#include <Rect.hpp>

typedef struct AppContext {
    SDL_Renderer* renderer;
    rectangle* items;
} AppContext;