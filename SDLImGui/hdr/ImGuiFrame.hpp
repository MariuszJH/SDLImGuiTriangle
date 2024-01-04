#pragma once
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "SDL.h"
#include "ImGuiView.hpp"
#include "ImGuiFonts.hpp"

namespace SDLImGui
{
   
class OpenGLContext;

class ImGuiFrame final
{
public:
    ImGuiFrame(SDL_Window* sdlWindow, OpenGLContext* openGLContext);
    ~ImGuiFrame();

    void PreRender();
    void Render(OpenGLContext *openGLContext);
    void PostRender();

private:
    void ApplyGenericSettings();
    void PrintImGuiVersion();

private:
    ImGuiFonts imGuiFonts;
    ImGuiView imguiView {imGuiFonts};
};

} // ~namespace SDLImGui
