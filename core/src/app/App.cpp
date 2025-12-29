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
#include <List.hpp>
#include <Sort.hpp>
#include <UserInterface.hpp>

namespace Application {

    bool App::CreateWindowAndRenderer(const char* title) {
        SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);

        SDL_CreateWindowAndRenderer("Sorting Visualizer", 
            WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer
        );
        return window != nullptr && renderer != nullptr;
    }

    SDL_AppResult App::Init(int argc, char** argv) {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) return SDL_APP_FAILURE;
        if (!CreateWindowAndRenderer("Sorting Visualizer")) return SDL_APP_FAILURE;

        srand(time(NULL));
        appContext.items = std::make_unique<Rectangle[]>(LIST_SIZE);

        // SETUP IMGUI
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.IniFilename = NULL;
        io.LogFilename = NULL;
        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer3_Init(renderer);

        SDL_SetWindowResizable(window, true);
        SDL_SetWindowMinimumSize(window, MINIMUM_WINDOW_WIDTH, MINIMUM_WINDOW_HEIGHT);

        // CREATE LIST AND CALCULATE INITIAL WIDTH/HEIGHT OF RECTANGLES
        CreateList(appContext.items.get(), width, height);

        return SDL_APP_CONTINUE;
    }

    SDL_AppResult App::ProcessEvent(SDL_Event* event) {
        switch (event->type) {
            case SDL_EVENT_QUIT:
                return SDL_APP_SUCCESS;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                width = event->window.data1;
                height = event->window.data2;
                break;
        }
        ImGui_ImplSDL3_ProcessEvent(event);
        return SDL_APP_CONTINUE;
    }

    void App::RenderScene(float deltaTime) {
        Rectangle* items = appContext.items.get();

        if (appContext.isSorting) {
            appContext.elapsedTime += deltaTime;

            if (appContext.elapsedTime >= appContext.delayTime) {
                if (IncrementStep(appContext.stepIndex, appContext.sequence.get(), items)) {
                    appContext.isSorting = false;
                    appContext.stepIndex = 0;
                } else {
                    appContext.stepIndex++;
                }
                appContext.elapsedTime = 0.0f;
            }
        }

        // RENDER LIST (EACH FRAME)
        DrawList(renderer, items, width, height);
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
        UserInterface::RenderGUI(&appContext, width, height);

        // RENDER SCENE
        RenderScene(deltaTime);

        ImGui::Render();

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
        return SDL_APP_CONTINUE;
    }

    void App::Shutdown() {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}
