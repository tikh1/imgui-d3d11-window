#include "ui.hh"
#include "../globals.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

void ui::render() {
    if (!globals.active) return;

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::Begin(window_title, &globals.active, window_flags);
    {
        static char inputbuffer[256] = "";
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImGui::Text("Window size: %.1f x %.1f", windowSize.x, windowSize.y);

        float inputWidth = 200.0f;
        float inputHeight = ImGui::GetTextLineHeightWithSpacing();
        float centerX = (windowSize.x - inputWidth) * 0.5f;
        float centerY = (windowSize.y - inputHeight) * 0.5f;

        ImGui::SetCursorPos(ImVec2(centerX, centerY - 65));
        ImGui::Text("Username");

        ImGui::SetCursorPos(ImVec2(centerX, centerY - 50));
        ImGui::PushItemWidth(inputWidth);
        ImGui::InputText("##username", globals.user_name, IM_ARRAYSIZE(globals.user_name));

        ImGui::SetCursorPos(ImVec2(centerX, centerY - 25));
        ImGui::Text("Password");

        ImGui::SetCursorPos(ImVec2(centerX, centerY - 10));
        ImGui::InputText("##password", globals.pass_word, IM_ARRAYSIZE(globals.pass_word), ImGuiInputTextFlags_Password);
        ImGui::PopItemWidth();

        // Login button
        float button_width = 120.0f;
        centerX = (windowSize.x - button_width) * 0.5f;
        ImGui::SetCursorPos(ImVec2(centerX, centerY + 20));
        if (ImGui::Button("Login", ImVec2(button_width, 0))) {
            // You can do your login logic here
        }
    }
    ImGui::End();
}

void ui::init(ID3D11Device* device) {
    dev = device;
    // colors
    ImGui::StyleColorsDark();

    if (window_pos.x == 0) {
        RECT screen_rect{};
        GetWindowRect(GetDesktopWindow(), &screen_rect);
        screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
        // init images here
    }
}