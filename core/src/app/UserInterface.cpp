#include <imgui.h>
#include <imgui_internal.h>

#include <App.hpp>
#include <AppContext.hpp>

namespace UserInterface {

    char* sortOptions[8] = {
        (char*) "Bubble",
        (char*) "Cocktail",
        (char*) "Heap",
        (char*) "Insertion",
        (char*) "Merge",
        (char*) "Quick",
        (char*) "Radix",
        (char*) "Selection"
    };

    void RenderGUI(Application::AppContext* appContext, int width, int height) {
        Rectangle* items = appContext->items.get();

        ImGui::SetNextWindowSize(ImVec2(136, 0));
        ImGui::SetNextWindowPos(ImVec2(24, 24), ImGuiCond_Once);
        ImGui::Begin("Control Panel", NULL, ImGuiWindowFlags_NoCollapse);

        if (ImGui::Button("Shuffle", ImVec2(120, 20))) {
            appContext->isSorting = false;
            appContext->elapsedTime = 0.0f;
            appContext->stepIndex = 0;
            ShuffleList(items);
        }

        if (ImGui::Button("Sort", ImVec2(120, 20))) {
            if (!appContext->isSorting) {
                try {
                    appContext->sequence = std::make_unique<SortSequence>();
                    UpdateSequence(appContext->sortId, items, appContext->sequence.get());
                    appContext->stepIndex = 0;
                    appContext->isSorting = true;
                } 
                catch (const std::exception& e) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create sort sequence: %s", e.what());
                }
                catch (...) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unknown error occurred while creating sort sequence.");
                }
            }
        }

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
    }

}