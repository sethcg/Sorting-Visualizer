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
        ImGui::SetNextWindowSize(ImVec2(136, 0));
        ImGui::SetNextWindowPos(ImVec2(24, 24), ImGuiCond_Once);
        ImGui::Begin("Control Panel", NULL, ImGuiWindowFlags_NoCollapse);

        if (ImGui::Button("Shuffle", ImVec2(120, 20))) {
            appContext->isSorting = false;
            appContext->lastTime = 0;
            appContext->stepIndex = 0;
            ShuffleList(appContext->items);
            ResizeList(appContext->items, width, height);
        }

        if (ImGui::Button("Sort", ImVec2(120, 20))) {
            if(!appContext->isSorting) {
                appContext->sequence = GetSortSequence(appContext->sortId, appContext->items);
                appContext->stepIndex = 0;
                appContext->isSorting = true;
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