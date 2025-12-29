#pragma once

#include <imgui.h>
#include <imgui_internal.h>

#include <App.hpp>
#include <AppContext.hpp>

namespace UserInterface {

    void RenderGUI(Application::AppContext* appContext, int width, int height);

}