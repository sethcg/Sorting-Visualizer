#include <atomic>
#include <memory>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <App.hpp>
#include <AppContext.hpp>
#include <ListManager.hpp>
#include <Renderer.hpp>
#include <SortManager.hpp>
#include <UserInterface.hpp>

namespace Application {

    bool App::CreateWindowAndRenderer(const char* title) {
        SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);

        SDL_CreateWindowAndRenderer("Sorting Visualizer", 
            WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS, &window, &sdl_renderer
        );
        return window != nullptr && sdl_renderer != nullptr;
    }

    SDL_AppResult App::Init(int argc, char** argv) {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) return SDL_APP_FAILURE;
        if (!CreateWindowAndRenderer("Sorting Visualizer")) return SDL_APP_FAILURE;

        srand(time(NULL));
        appContext.renderer = std::make_unique<Renderer>(sdl_renderer);
        appContext.sortManager = std::make_unique<SortManager>();
        appContext.listManager = std::make_unique<ListManager>(WINDOW_WIDTH, WINDOW_HEIGHT);

        // SETUP IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.IniFilename = NULL;
        io.LogFilename = NULL;
        UserInterface::SetCustomTheme();

        ImGui_ImplSDL3_InitForSDLRenderer(window, sdl_renderer);
        ImGui_ImplSDLRenderer3_Init(sdl_renderer);

        SDL_SetWindowResizable(window, true);
        SDL_SetWindowMinimumSize(window, MINIMUM_WINDOW_WIDTH, MINIMUM_WINDOW_HEIGHT);

        return SDL_APP_CONTINUE;
    }

    SDL_AppResult App::ProcessEvent(SDL_Event* event) {
        switch (event->type) {
            case SDL_EVENT_QUIT:
                return SDL_APP_SUCCESS;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                int32_t width = event->window.data1;
                int32_t height = event->window.data2;
                appContext.listManager->Resize(width, height);
                break;
        }
        ImGui_ImplSDL3_ProcessEvent(event);
        return SDL_APP_CONTINUE;
    }

    void App::RenderScene(float deltaTime) {
        std::vector<Rect::Rectangle>& rects = appContext.listManager->GetItems();

        if (appContext.isSortingFlag.load(std::memory_order_acquire)) {
            appContext.elapsedTime += deltaTime;

            constexpr float delayMin = 0.01f;
            constexpr float delayMax = 0.25f;
            float speed = appContext.delayTimeNormalized;
            float delayTime = delayMax - (delayMax - delayMin) * (speed * speed);

            // STEP AT MOST ONCE PER FRAME
            if (appContext.elapsedTime >= delayTime) {
                if (appContext.sortManager->IncrementStep(rects)) {
                    appContext.isSortingFlag.store(false, std::memory_order_release);
                    appContext.sortManager->stepIndex = 0;
                    appContext.elapsedTime = 0.0f;
                }
                appContext.elapsedTime -= delayTime;
            }
        }
        appContext.renderer->DrawList(rects, *appContext.listManager);
    }

    SDL_AppResult App::Frame() {
        // UPDATE DELTA TIME
        uint64_t currentTime = SDL_GetPerformanceCounter();
        float deltaTime = float(currentTime - lastFrameTime) / SDL_GetPerformanceFrequency();
        lastFrameTime = currentTime;

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        // RENDER GUI
        UserInterface::RenderGUI(&appContext);

        // RENDER SCENE
        RenderScene(deltaTime);

        ImGui::Render();

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), sdl_renderer);
        SDL_RenderPresent(sdl_renderer);
        return SDL_APP_CONTINUE;
    }

    void App::Shutdown() {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(sdl_renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}
