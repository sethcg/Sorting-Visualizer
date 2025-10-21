#define SDL_MAIN_USE_CALLBACKS 1 // USE CALLBACKS INSTEAD OF THE "main()" FUNCTION

#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct AppContext {
    SDL_Window* window;
    SDL_Renderer* renderer;

    ImDrawData *data;
} AppContext;

// THIS FUNCTION RUNS ONCE AT STARTUP
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // SETUP APP STATE
    AppContext* appContext = (AppContext*) SDL_malloc(sizeof(AppContext));
    if (appContext == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    *appstate = appContext;

    if (!SDL_CreateWindowAndRenderer("Sorting Visualizer", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &appContext->window, &appContext->renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // SETUP IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.LogFilename = NULL;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(appContext->window, appContext->renderer);
    ImGui_ImplSDLRenderer3_Init(appContext->renderer);

    return SDL_APP_CONTINUE;
}

// THIS FUNCTION RUNS WHEN A NEW EVENT OCCURS (MOUSE INPUT, KEY PRESS, ETC.)
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* event) {
    AppContext* appContext = (AppContext*) appstate;
    
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
    }

    ImGui_ImplSDL3_ProcessEvent(event);

    return SDL_APP_CONTINUE;
}

// THIS FUNCTION RUNS ONCE PER FRAME
SDL_AppResult SDL_AppIterate(void *appstate) {
    AppContext* appContext = (AppContext*) appstate;

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(136, 0));
    ImGui::Begin("Control Panel", NULL, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Sort", ImVec2(120, 20))) {
        SDL_Log("Sorting...");
    }

    ImGui::End();

    // RENDERING
    ImGui::Render();

    SDL_SetRenderDrawColor(appContext->renderer, 30, 30, 30, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(appContext->renderer);

    appContext->data = ImGui::GetDrawData();
    ImGui_ImplSDLRenderer3_RenderDrawData(appContext->data, appContext->renderer);
    SDL_RenderPresent(appContext->renderer);
    
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    AppContext* appContext = (AppContext*) appstate;

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(appContext->renderer);
    SDL_DestroyWindow(appContext->window);
    SDL_Quit();

    SDL_free(appContext);
}