#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <atomic>
#include <vector>

#include <imgui.h>
#include <imgui_internal.h>

#include <App.hpp>
#include <AppContext.hpp>

namespace UserInterface {

    inline void SetCustomTheme() {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = style.Colors;
        ImGui::StyleColorsDark();

        // ROUNDING
        style.WindowRounding = 4.0f;
        style.FrameRounding = 4.0f;
        style.ChildRounding = 6.0f;
        style.PopupRounding = 4.0f;
        style.GrabRounding = 4.0f;
        style.ScrollbarRounding = 6.0f;

        // WINDOW
        style.WindowBorderSize = 0.0f;
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);    // WINDOW TITLE CENTERED
        
        style.ItemSpacing = ImVec2(8.0f, 6.0f);
        style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
        style.ScrollbarSize = 18.0f;
        style.FramePadding = ImVec2(10.0f, 6.0f);
        style.FrameBorderSize = 0.0f;
        style.GrabMinSize = 10.0f;

        // TITLE (PANEL)
        colors[ImGuiCol_TitleBg]                    = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
        colors[ImGuiCol_TitleBgActive]              = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]           = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
    }

    void CreateShuffleButton(Application::AppContext* appContext);

    void CreateSortButton(Application::AppContext* appContext);

    void CreateSortSelectionDropdown(Application::AppContext* appContext);

    void RenderGUI(Application::AppContext* appContext);

}

#endif