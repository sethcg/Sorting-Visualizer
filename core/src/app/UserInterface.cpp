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
        float maxWidth = 150.0f;
        float availableWidth = ImGui::GetContentRegionAvail().x;
        float comboWidth = (availableWidth > maxWidth) ? maxWidth : availableWidth;
        ImGui::SetNextItemWidth(comboWidth);

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
        float maxWidth = 150.0f;
        float availableWidth = ImGui::GetContentRegionAvail().x;
        float sliderWidth = (availableWidth > maxWidth) ? maxWidth : availableWidth;
        ImGui::SetNextItemWidth(sliderWidth);

        // USER ADJUSTED VALUE, DETERMINES SORT SPEED (0 = SLOWEST, 1 = FASTEST)
        ImGui::SliderFloat("##SORT_SPEED", &appContext->delayTimeNormalized, 0.0f, 1.0f);
    }

    void RenderGUI(Application::AppContext* appContext) {
        // NUMBER OF ITEMS IN THE PANEL (SHUFFLE, SORT, ...)
        int itemCount = 4;
        ImGuiStyle& style = ImGui::GetStyle();

        float itemHeight = ImGui::GetFrameHeight();                             // BASE ITEM HEIGHT
        float itemFramePadding = itemCount * (style.FramePadding.y * 2.0f);     // TOP/BOTTOM FRAME PADDING
        float itemSpacing = (itemCount - 1) * style.ItemSpacing.y;              // VERTICAL SPACING BETWEEN ITEMS
        float windowPadding = style.WindowPadding.y * 2.0f;                     // TOP/BOTTOM WINDOW PADDING
        float minHeight = windowPadding + itemFramePadding + itemSpacing + (itemCount * itemHeight);

        float minWidth = 120.0f;
        ImVec2 minSize(minWidth, minHeight);
        ImVec2 maxSize(minWidth * 2.0f, float(MINIMUM_WINDOW_HEIGHT) / 2.0f);
        ImGui::SetNextWindowSize(minSize, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
        ImGui::Begin("##CONTROL_PANEL", nullptr, ImGuiWindowFlags_NoCollapse);

        CreateShuffleButton(appContext);
        CreateSortButton(appContext);
        CreateSortSelectionDropdown(appContext);
        CreateSortSpeedSlider(appContext);

        ImGui::End();
    }

}