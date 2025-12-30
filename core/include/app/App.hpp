#ifndef APP_H
#define APP_H

#include <memory>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <AppContext.hpp>
#include <ListManager.hpp>
#include <Renderer.hpp>
#include <SortManager.hpp>
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

            SDL_Window* window = nullptr;
            SDL_Renderer* sdl_renderer = nullptr;

            float deltaTime = 0.0f;
            float lastFrameTime = 0.0f;
    };

}

#endif