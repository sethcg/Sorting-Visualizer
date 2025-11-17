#define SDL_MAIN_USE_CALLBACKS 1 // USE CALLBACKS INSTEAD OF THE "main()" FUNCTION

#include <stdlib.h>
#include <time.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <App.hpp>
#include <List.hpp>
#include <Rect.hpp>
#include <Sort.hpp>

// THIS FUNCTION RUNS ONCE AT STARTUP
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    srand(time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // SETUP APP STATE
    AppContext* appContext = (AppContext*) SDL_malloc(sizeof(AppContext));
    appContext->items = (Rectangle*) malloc(LIST_SIZE * sizeof(Rectangle));
    if (appContext == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    appContext->sortId = 0;
    appContext->width = WINDOW_WIDTH;
    appContext->height = WINDOW_HEIGHT;
    appContext->isSorting = false;
    appContext->lastTime = 0;
    appContext->delayInMilliseconds = DEFAULT_SORTING_DELAY_MILLISECONDS;
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
    SDL_SetWindowMinimumSize(appContext->window, MINIMUM_WINDOW_WIDTH, MINIMUM_WINDOW_HEIGHT);

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
            ResizeList(appContext->renderer, appContext->items, appContext->width, appContext->height);
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
    ImGui::SetNextWindowPos(ImVec2(24, 24), ImGuiCond_Once);
    ImGui::Begin("Control Panel", NULL, ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Shuffle", ImVec2(120, 20))) {
        appContext->isSorting = false;
        appContext->lastTime = 0;
        appContext->stepIndex = 0;
        ShuffleList(appContext->items);
        ResizeList(appContext->renderer, appContext->items, appContext->width, appContext->height);
    }

    // TODO: ADD SORT FUNCTIONALITY WHEN THIS IS PRESSED
    if (ImGui::Button("Sort", ImVec2(120, 20))) {
        if(!appContext->isSorting) {
            appContext->sequence = GetSortSequence(appContext->sortId, appContext->items);
            appContext->stepIndex = 0;
            appContext->isSorting = true;
        }
    }

    // TODO: FIX THIS TO SET THE SORTING ALGORITHM
    ImGui::SetNextItemWidth(120);
    if(ImGui::BeginCombo("##Select_Sort", sortOptions[appContext->sortId], ImGuiComboFlags_NoArrowButton)) {
        for(int i = 0; i < sizeof(sortOptions) / sizeof(char*); i++) {
            if(ImGui::Selectable(sortOptions[i], (appContext->sortId == i))) {
                if(!appContext->isSorting) appContext->sortId = i;
            }
        }
        ImGui::EndCombo();
    }
    
    ImGui::End();

    // RENDERING EACH SORT'S ITERATION
    if(appContext->isSorting) {
        // DELAY ITERATING THE SORTING STEP
        static SDL_Time current = 0;
        SDL_GetCurrentTime(&current);
        int currentTime = abs((int) SDL_NS_TO_MS(current));
        int elapsedTime = abs(currentTime - appContext->lastTime);
        if(elapsedTime > appContext->delayInMilliseconds) {
            if(IncrementStep(appContext->stepIndex, appContext->sequence, appContext->items)) {
                appContext->isSorting = false;
                appContext->lastTime = 0;
                appContext->stepIndex = 0;
            } else {
                appContext->lastTime = currentTime;
                appContext->stepIndex++;
            }
            ResizeList(appContext->renderer, appContext->items, appContext->width, appContext->height);
        }
    }

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