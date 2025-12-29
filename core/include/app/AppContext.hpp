#pragma once

#include <Rect.hpp>
#include <Sort.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MINIMUM_WINDOW_WIDTH 400
#define MINIMUM_WINDOW_HEIGHT 400

#define DEFAULT_SORTING_DELAY_MILLISECONDS 100

// #define WINDOW_WIDTH 1280
// #define WINDOW_HEIGHT 720
// #define WINDOW_FLAGS SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE

// #define MINIMUM_WINDOW_WIDTH 640
// #define MINIMUM_WINDOW_HEIGHT 360

// #define GLSL_VERSION "#version 330"

namespace Application {

    struct AppContext {
        Rectangle* items;

        bool isSorting;

        int sortId;
        int stepIndex;
        int lastTime;
        int delayInMilliseconds;
        SortSequence sequence;
    };

}
