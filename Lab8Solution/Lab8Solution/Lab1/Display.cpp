#include "Display.h"

Display::Display()
    : sdlWindow(nullptr), glContext(nullptr), screenWidth(640.0f), screenHeight(420.0f) {}

Display::~Display() 
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(sdlWindow);
}

float Display::GetWidth() const { return screenWidth; }
float Display::GetHeight() const { return screenHeight; }

void Display::ReturnError(const std::string& errorString) 
{
    throw std::runtime_error(errorString);
}

void Display::SwapBuffer() 
{
    SDL_GL_SwapWindow(sdlWindow);
}

void Display::ClearDisplay(float r, float g, float b, float a) 
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::InitializeDisplay() 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        ReturnError("SDL initialization failed");
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                 static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);

    if (sdlWindow == nullptr) {
        ReturnError("Window creation failed");
    }

    glContext = SDL_GL_CreateContext(sdlWindow);

    if (glContext == nullptr) {
        ReturnError("OpenGL context creation failed");
    }

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        ReturnError("GLEW initialization failed");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}