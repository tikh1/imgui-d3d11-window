﻿#include "main.hpp"
#include "ui/ui.hh"
#include "globals.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      ui::window_title_wide, NULL };
    RegisterClassEx(&wc);

    g_hWnd = CreateWindowExW(WS_EX_TRANSPARENT,
        wc.lpszClassName, ui::window_title_wide, 
        WS_POPUP, globals.window_pos_x, globals.window_pos_y, globals.width, globals.height,
        NULL, NULL, wc.hInstance, NULL);

    // Set window position to middle of the screen
    RECT rc;
    GetWindowRect(g_hWnd, &rc);
    int winWidth = rc.right - rc.left;
    int winHeight = rc.bottom - rc.top;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    SetWindowPos(g_hWnd, HWND_TOP,
        (screenWidth - winWidth) / 2,
        (screenHeight - winHeight) / 2,
        0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_SHOWWINDOW);

    // Initialize Direct3D
    if (!CreateDeviceD3D(g_hWnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(g_hWnd, SW_SHOWNORMAL);
    UpdateWindow(g_hWnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplWin32_Init(g_hWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // ImGui Window
        ui::render();
        //ImGui::Begin("Hello, ImGui!");
        //ImGui::Text("This is a DirectX11 + ImGui application.");
        //ImGui::End();

        // Rendering
        ImGui::Render();
        const float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0); // Vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    DestroyWindow(g_hWnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONDOWN:
        {
            POINTS points = MAKEPOINTS(lParam);
            globals.position = points;
            SetCapture(hWnd);
        }
        break;

    case WM_LBUTTONUP:
        ReleaseCapture();
        break;

    case WM_MOUSEMOVE:
        if (wParam == MK_LBUTTON)
        {
            POINTS points = MAKEPOINTS(lParam);
            RECT rect;
            GetWindowRect(hWnd, &rect);
            
            int newX = rect.left + (points.x - globals.position.x);
            int newY = rect.top + (points.y - globals.position.y);
            
            SetWindowPos(
                hWnd,
                HWND_TOPMOST,
                newX,
                newY,
                0, 0,
                SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
            );
        }
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
