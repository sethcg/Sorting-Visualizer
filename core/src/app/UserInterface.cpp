#include <atomic>
#include <vector>

#include <imgui.h>
#include <imgui_internal.h>

#include <App.hpp>
#include <AppContext.hpp>

namespace UserInterface {

    void CreateShuffleButton(Application::AppContext* appContext) {
        if (ImGui::Button("Shuffle", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
            appContext->isSortingFlag.store(false, std::memory_order_release);
            appContext->elapsedTime = 0.0f;
            appContext->sortManager->stepIndex = 0;
            appContext->listManager->Shuffle();
            appContext->sortManager->GenerateSequence(appContext->listManager->GetItems());
        }
    }

    void CreateSortButton(Application::AppContext* appContext) {
        if (ImGui::Button("Sort", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
            if (!appContext->isSortingFlag.load(std::memory_order_acquire)) {
                appContext->isSortingFlag.store(true, std::memory_order_release);
                appContext->sortManager->stepIndex = 0;
            }
        }
    }

    void CreateSortSelectionDropdown(Application::AppContext* appContext) {
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        int sortId = appContext->sortManager->currentSortId;
        if (ImGui::BeginCombo("##Select_Sort", appContext->sortManager->GetSortName(sortId), ImGuiComboFlags_NoArrowButton)) {
            int sortCount = appContext->sortManager->GetSortCount();
            for (int i = 0; i < sortCount; i++) {
                if (ImGui::Selectable(appContext->sortManager->GetSortName(i), sortId == i)) {
                    if (!appContext->isSortingFlag.load(std::memory_order_acquire)) {
                        appContext->sortManager->currentSortId = i;
                        appContext->sortManager->SetSort(i);
                        appContext->sortManager->GenerateSequence(appContext->listManager->GetItems());
                    }
                }
            }
            ImGui::EndCombo();
        }
    }

    void CreateSortSpeedSlider(Application::AppContext* appContext) {
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);

        // USER ADJUSTED VALUE, DETERMINES SORT SPEED (0 = SLOWEST, 1 = FASTEST)
        ImGui::SliderFloat("##SORT_SPEED", &appContext->delayTimeNormalized, 0.0f, 1.0f);
    }

    void RenderGUI(Application::AppContext* appContext) {
        // NUMBER OF ITEMS IN THE PANEL (SHUFFLE, SORT, ...)
        int itemCount = 4;
        ImGuiStyle& style = ImGui::GetStyle();

        float itemHeight = ImGui::GetFrameHeight();                                     // BASE ITEM HEIGHT
        float itemFramePadding = (itemCount - 0.5) * (style.FramePadding.y * 2.0f);     // TOP/BOTTOM FRAME PADDING
        float itemSpacing = (itemCount - 1) * style.ItemSpacing.y;                      // VERTICAL SPACING BETWEEN ITEMS
        float minHeight = itemFramePadding + itemSpacing + (itemCount * itemHeight);

        const float minWidth = float(MINIMUM_WINDOW_WIDTH) / 2.5f;
        const ImVec2 minSize(minWidth, minHeight);
        ImGui::SetNextWindowSize(minSize, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSizeConstraints(minSize, minSize);
        ImGui::Begin("##CONTROL_PANEL", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        CreateShuffleButton(appContext);
        CreateSortButton(appContext);
        CreateSortSpeedSlider(appContext);
        CreateSortSelectionDropdown(appContext);

        ImGui::End();
    }

}