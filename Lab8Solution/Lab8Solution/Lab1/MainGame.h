#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <AL/al.h>
#include <AL/alc.h>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Audio.h"

enum class GameState { PLAY, EXIT};

class MainGame {
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void InitializeSystems();
    void ProcessInput();
    void Menu();
    void Update();
    void DrawMenu();
    void DrawGame();
    void LinkBumpMapping();
    bool Collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
    void PlayAudio(unsigned int Source, glm::vec3 pos);
    void RestartGame();
    void LevelHandler();

    Display* _gameDisplay;
    GameState _gameState;
    Mesh mesh1;
    Mesh mesh2;
    Mesh mesh3;
    Mesh mesh4;
    Mesh mesh5;
    Camera myCamera;
    Shader ballShader;
    Shader bumpShader;
    Shader arrowShader;
    Texture texture1;
    Texture texture2;
    Texture texture3;
    Texture texture4;
    Texture texture5;
    Texture texture2normal;
    Audio* audioDevice;
    Transform transform;

    float speed;
    float rotation;
    float shotRotation;
    unsigned int applause;
    unsigned int backGroundMusic;
    bool isBallKicked;
    bool isGoal;
    int level;
};

