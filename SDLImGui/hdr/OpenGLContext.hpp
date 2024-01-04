#pragma once
#include <SDL.h>
#include <iostream>

namespace SDLImGui
{

class ImGuiView;

class OpenGLContext final
{
public:
    OpenGLContext(SDL_Window* sdlWindow);
    ~OpenGLContext();

    void DrawOpenGLPrimitiveTriangle();

private:
    void PrintOpenGLVersion();

private:
    SDL_GLContext glContext {nullptr};

    bool isShowTriangle {true};
    float rescaleSize {1.0F};
    float triangleShift[2] = {0.0, 0.0};
    float rotationAngleDeg {0};
    float triangleColour[3] = {1.0F, 1.0F, 0.0F};

    struct Vertex
    {
        Vertex(float x, float y, float rescaleSize = 1.0F)
            : x(x * rescaleSize)
            , y(y * rescaleSize)
        {}

        float x {0.0};
        float y {0.0};
    };

    friend class ImGuiView;
};

} // ~namespace SDLImGui
