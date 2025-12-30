#ifndef APP_CONTEXT_H
#define APP_CONTEXT_H

#include <atomic>
#include <memory>
#include <vector>

#include <ListManager.hpp>
#include <Renderer.hpp>
#include <SortManager.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define WINDOW_FLAGS SDL_WINDOW_RESIZABLE

#define MINIMUM_WINDOW_WIDTH 400
#define MINIMUM_WINDOW_HEIGHT 400

namespace Application {

    struct AppContext {
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<SortManager> sortManager;
        std::unique_ptr<ListManager> listManager;

        std::atomic<bool> isSortingFlag { false };

        float elapsedTime;          // ELAPSED TIME SINCE LAST ITERATION STEP (SECONDS)
        float delayTimeNormalized;  // NORMALIZED ITERATION DELAY TIME (SECONDS)

        AppContext() {
            elapsedTime = 0.0f;
            delayTimeNormalized = 0.75f;
        }
    };

}

#endif