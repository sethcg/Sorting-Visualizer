#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>

#include <AppContext.hpp>
#include <UserInterface.hpp>

namespace Application {

    class App {
        public:
            AppContext appContext;

            SDL_AppResult Init(int argc, char** argv);
            SDL_AppResult ProcessEvent(SDL_Event* event);
            SDL_AppResult Frame();
            void Shutdown();
            
            // SETUP APP INSTANCE (SINGLETON)
            static App& Instance() {
                static App instance;
                return instance;
            }

            // PREVENT COPYING/DELETING OPERATIONS (SINGLETON)
            App(const App&) = delete;
            App(App&&) = delete;
            App& operator=(const App&) = delete;
            App& operator=(App&&) = delete;

        private:
            // PREVENT CONSTRUCT/DESTRUCTION (SINGLETON)
            App() = default;
            ~App() = default;

            bool CreateWindowAndRenderer(const char* title);
            void RenderScene(float deltaTime);

            int width = WINDOW_WIDTH;
            int height = WINDOW_HEIGHT;

            SDL_Window* window = nullptr;
            SDL_Renderer* renderer = nullptr;

            float deltaTime = 0.0f;
            uint64_t lastTime = 0;
    };

}

#endif