#pragma once
#include <d3d11.h>
#include "../imgui/imgui.h"

namespace ui {
    void init(ID3D11Device*);
    void render();
}

namespace ui {
    inline ID3D11Device* dev;
    inline const char* window_title = "Simple ImGui D3DX11 Window";
    inline const wchar_t* window_title_wide = L"Simple ImGui D3DX11 Window";
}

namespace ui {
    inline ImVec2 screen_res{ 000, 000 };
    inline ImVec2 window_pos{ 0, 0 };
    inline ImVec2 window_size{ 400, 300 };
    inline DWORD  window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
}
