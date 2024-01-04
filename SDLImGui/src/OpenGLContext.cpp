#include <stdexcept>
#include <iostream>
#include <glad/glad.h>
#include "OpenGLContext.hpp"

namespace SDLImGui
{

OpenGLContext::OpenGLContext(SDL_Window* sdlWindow)
    : glContext(SDL_GL_CreateContext(sdlWindow))
{
    if (!glContext)
    {
        throw std::runtime_error("Failure: SDL_GL_CreateContext");
    }

    SDL_GL_MakeCurrent(sdlWindow, glContext);
    SDL_GL_SetSwapInterval(1);

    gladLoadGL(); // Load GLAD so it configures OpenGL

    PrintOpenGLVersion();
}

OpenGLContext::~OpenGLContext()
{
    SDL_GL_DeleteContext(glContext);
}

void OpenGLContext::DrawOpenGLPrimitiveTriangle()
{
    if (!isShowTriangle)
        return;
        
    Vertex vertexA1 {0.0F, 0.2F, rescaleSize};
    Vertex vertexB1 {-0.1F, -0.1F, rescaleSize};
    Vertex vertexC1 {0.15F, -0.05F, rescaleSize};
    Vertex centroid {   (vertexA1.x + vertexB1.x + vertexC1.x)/3, 
                        (vertexA1.y + vertexB1.y + vertexC1.y)/3 };

    // glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glTranslatef(triangleShift[0], triangleShift[1], 0);

    glTranslatef(centroid.x, centroid.y, 0);
    glRotatef(rotationAngleDeg, 0, 0, 1);
    glTranslatef(-centroid.x, -centroid.y, 0);
    
    glBegin(GL_TRIANGLES);  
    glColor3f(triangleColour[0], triangleColour[1], triangleColour[2]);

    glVertex2f(vertexA1.x, vertexA1.y);
    glVertex2f(vertexB1.x, vertexB1.y);
    glVertex2f(vertexC1.x, vertexC1.y);
    glEnd();

    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0, 1, 0);
    glVertex2f(centroid.x, centroid.y);
    glEnd();
}

void OpenGLContext::PrintOpenGLVersion()
{
    std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GL_SHADING: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}

} // ~namespace SDLImGui
