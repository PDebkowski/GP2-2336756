#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL/SDL.h>

class Ball
{
public:
	Ball();
	void InitializeBall(const glm::vec3& pos);
	glm::vec3 GetPos() const;
	void RotateRight(float amt);
	void RotateLeft(float amt);
	void handleInput(float deltaTime);

private:
	glm::vec3 forward;
	glm::vec3 pos;
	glm::vec3 up;
	glm::vec3 right;
};

