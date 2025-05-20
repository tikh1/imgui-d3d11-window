#pragma once
#include <d3d11.h>
#include "../imgui/imgui.h"

namespace ui {
    inline DWORD  window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    void init(ID3D11Device*);
    void render();

    inline ID3D11Device* dev;
    inline const char* window_title = "Simple ImGui D3DX11 Window";
    inline const wchar_t* window_title_wide = L"Simple ImGui D3DX11 Window";
}