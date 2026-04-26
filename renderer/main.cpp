#include "pipeline.hpp"
#include "mesh.hpp"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

namespace {
constexpr int kRenderWidth = 800;
constexpr int kRenderHeight = 600;

float clamp01(float value) {
    return std::max(0.0f, std::min(1.0f, value));
}

Matrix4 makeRotationX(float angle) {
    return Matrix4(
        1.0f, 0.0f,             0.0f,            0.0f,
        0.0f, std::cos(angle), -std::sin(angle), 0.0f,
        0.0f, std::sin(angle),  std::cos(angle), 0.0f,
        0.0f, 0.0f,             0.0f,            1.0f
    );
}

Matrix4 makeRotationY(float angle) {
    return Matrix4(
         std::cos(angle), 0.0f, std::sin(angle), 0.0f,
         0.0f,            1.0f, 0.0f,            0.0f,
        -std::sin(angle), 0.0f, std::cos(angle), 0.0f,
         0.0f,            0.0f, 0.0f,            1.0f
    );
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param) {
    switch (message) {
    case WM_ERASEBKGND:
        return 1;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, message, w_param, l_param);
    }
}

void presentFramebuffer(HWND hwnd,
                        const Framebuffer& framebuffer,
                        std::vector<std::uint32_t>& pixel_buffer,
                        const std::string& fps_text) {
    const int width = framebuffer.getWidth();
    const int height = framebuffer.getHeight();

    if (pixel_buffer.size() != static_cast<std::size_t>(width * height)) {
        pixel_buffer.resize(static_cast<std::size_t>(width * height));
    }

    for (int i = 0; i < width * height; ++i) {
        const Vector3& color = framebuffer.colors[i];
        const std::uint8_t r = static_cast<std::uint8_t>(clamp01(color.r()) * 255.0f);
        const std::uint8_t g = static_cast<std::uint8_t>(clamp01(color.g()) * 255.0f);
        const std::uint8_t b = static_cast<std::uint8_t>(clamp01(color.b()) * 255.0f);
        pixel_buffer[static_cast<std::size_t>(i)] =
            (static_cast<std::uint32_t>(r) << 16) |
            (static_cast<std::uint32_t>(g) << 8) |
             static_cast<std::uint32_t>(b);
    }

    BITMAPINFO bitmap_info = {};
    bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_info.bmiHeader.biWidth = width;
    bitmap_info.bmiHeader.biHeight = -height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;

    RECT client_rect = {};
    GetClientRect(hwnd, &client_rect);

    HDC dc = GetDC(hwnd);
    StretchDIBits(dc,
                  0,
                  0,
                  client_rect.right - client_rect.left,
                  client_rect.bottom - client_rect.top,
                  0,
                  0,
                  width,
                  height,
                  pixel_buffer.data(),
                  &bitmap_info,
                  DIB_RGB_COLORS,
                  SRCCOPY);

    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(0, 0, 0));
    TextOutA(dc, 11, 11, fps_text.c_str(), static_cast<int>(fps_text.size()));
    SetTextColor(dc, RGB(255, 255, 255));
    TextOutA(dc, 10, 10, fps_text.c_str(), static_cast<int>(fps_text.size()));
    ReleaseDC(hwnd, dc);
}
}

int main() {
    HINSTANCE instance = GetModuleHandle(nullptr);

    WNDCLASSA window_class = {};
    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = instance;
    window_class.lpszClassName = "SoftRender3DWindow";
    window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClassA(&window_class);

    RECT window_rect = {0, 0, kRenderWidth, kRenderHeight};
    AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindowA(
        window_class.lpszClassName,
        "soft_render3d",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        window_rect.right - window_rect.left,
        window_rect.bottom - window_rect.top,
        nullptr,
        nullptr,
        instance,
        nullptr);

    if (hwnd == nullptr) {
        return 1;
    }

    Pipeline pipeline(kRenderWidth, kRenderHeight);
    Mesh cube = Mesh::createCube();
    std::vector<std::uint32_t> pixel_buffer(static_cast<std::size_t>(kRenderWidth * kRenderHeight));

    using clock = std::chrono::steady_clock;
    const auto start_time = clock::now();
    auto fps_window_start = start_time;
    int frames_in_window = 0;
    float fps = 0.0f;

    MSG message = {};
    bool running = true;
    while (running) {
        while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
            if (message.message == WM_QUIT) {
                running = false;
                break;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        if (!running) {
            break;
        }

        const auto now = clock::now();
        const float elapsed = std::chrono::duration<float>(now - start_time).count();

        Matrix4 model_matrix = makeRotationY(elapsed * 0.9f) * makeRotationX(elapsed * 0.55f);
        pipeline.render(cube, model_matrix, Vector3(0.0f, 0.0f, 3.0f), Vector3(0.4f, 0.8f, 1.0f));

        ++frames_in_window;
        const float fps_elapsed = std::chrono::duration<float>(now - fps_window_start).count();
        if (fps_elapsed >= 0.5f) {
            fps = frames_in_window / fps_elapsed;
            frames_in_window = 0;
            fps_window_start = now;
        }

        char fps_buffer[32] = {};
        std::snprintf(fps_buffer, sizeof(fps_buffer), "FPS: %.1f", fps);
        presentFramebuffer(hwnd, pipeline.getFramebuffer(), pixel_buffer, fps_buffer);
    }

    return 0;
}
