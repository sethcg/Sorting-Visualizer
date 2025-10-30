#define SDL_MAIN_USE_CALLBACKS 1 // USE CALLBACKS INSTEAD OF THE "main()" FUNCTION

#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <List.hpp>
#include <Rect.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

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

// THIS FUNCTION RUNS ONCE AT STARTUP
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // SETUP APP STATE
    AppContext* appContext = (AppContext*) SDL_malloc(sizeof(AppContext));
    appContext->items = (rectangle*) malloc(LIST_SIZE * sizeof(rectangle));
    if (appContext == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    appContext->sortId = 0;
    appContext->sortOptions[0] = (char*) "Bubble";
    appContext->sortOptions[1] = (char*) "Cocktail";
    appContext->sortOptions[2] = (char*) "Heap";
    appContext->sortOptions[3] = (char*) "Insertion";
    appContext->sortOptions[4] = (char*) "Merge";
    appContext->sortOptions[5] = (char*) "Quick";
    appContext->sortOptions[6] = (char*) "Radix";
    appContext->sortOptions[7] = (char*) "Selection";
    appContext->width = WINDOW_WIDTH;
    appContext->height = WINDOW_HEIGHT;
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

    SDL_SetWindowResizable(appContext->window, true);

    // CREATE LIST AND CALCULATE INITIAL WIDTH/HEIGHT OF RECTANGLES
    CreateList(appContext->renderer, appContext->items, appContext->width, appContext->height);

    return SDL_APP_CONTINUE;
}

// THIS FUNCTION RUNS WHEN A NEW EVENT OCCURS (MOUSE INPUT, KEY PRESS, ETC.)
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* event) {
    AppContext* appContext = (AppContext*) appstate;
    
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_WINDOW_RESIZED:
            // RESIZE WIDTH/HEIGHT OF RECTANGLES
            SDL_GetWindowSize(appContext->window, &appContext->width, &appContext->height);
            CreateList(appContext->renderer, appContext->items, appContext->width, appContext->height);
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

    // TODO: ADD SORT FUNCTIONALITY WHEN THIS IS PRESSED
    if (ImGui::Button("Sort", ImVec2(120, 20))) {
        // IterateSort(appContext->sortId);
        switch(appContext->sortId) {
            case 0:
                SDL_Log("Bubble Sort...");
                break;
            case 1:
                SDL_Log("Cocktail Sort...");
                break;
            case 2:
                SDL_Log("Heap Sort...");
                break;
            case 3:
                SDL_Log("Insertion Sort...");
                break;
            case 4:
                SDL_Log("Merge Sort...");
                break;
            case 5:
                SDL_Log("Quick Sort...");
                break;
            case 6:
                SDL_Log("Radix Sort...");
                break;
            case 7:
                SDL_Log("Selection Sort...");
                break;
        }
    }

    // TODO: FIX THIS TO SET THE SORTING ALGORITHM
    ImGui::SetNextItemWidth(120);
    if(ImGui::BeginCombo("##Select_Sort", appContext->sortOptions[appContext->sortId], ImGuiComboFlags_NoArrowButton)) {
        for(int i = 0; i < sizeof(appContext->sortOptions) / sizeof(char*); i++) {
            if(ImGui::Selectable(appContext->sortOptions[i], (appContext->sortId == i))) {
                appContext->sortId = i;
            }
        }
        ImGui::EndCombo();
    }
    
    ImGui::End();

    // RENDERING
    ImGui::Render();
    DrawList(appContext->renderer, appContext->items);
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