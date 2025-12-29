#pragma once

#include <memory>

#include <Rect.hpp>
#include <Sort.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MINIMUM_WINDOW_WIDTH 400
#define MINIMUM_WINDOW_HEIGHT 400

#define DEFAULT_SORTING_DELAY_SECONDS 0.1f

namespace Application {

    struct AppContext {
        std::unique_ptr<Rectangle[]> items;

        float elapsedTime;  // ELAPSED TIME SINCE LAST ITERATION STEP (SECONDS)
        float delayTime;    // ITERATION DELAY TIME (SECONDS)

        bool isSorting = false;
        int sortId = 0;
        int stepIndex = 0;
        std::unique_ptr<SortSequence> sequence;

        AppContext() {
            elapsedTime = 0.0f;
            delayTime = DEFAULT_SORTING_DELAY_SECONDS;
        }
    };

}
