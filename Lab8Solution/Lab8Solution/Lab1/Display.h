#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>

class Display {
public:
    Display();
    ~Display();

    void InitializeDisplay();
    void SwapBuffer();
    void ClearDisplay(float r, float g, float b, float a);

    float GetWidth() const;
    float GetHeight() const;

private:
    void ReturnError(const std::string& errorString);

    SDL_GLContext glContext;
    SDL_Window* sdlWindow;
    float screenWidth;
    float screenHeight;
};

