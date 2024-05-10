#include "Ball.h"

Ball::Ball() {}

void Ball::InitializeBall(const glm::vec3& pos)
{
	this->pos = pos;
	this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->right = glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::vec3 Ball::GetPos() const
{
	return this->pos;
}

void Ball::RotateRight(float amt)
{
	pos += glm::cross(up, forward) * amt;
}

void Ball::RotateLeft(float amt)
{
	pos -= glm::cross(up, forward) * amt;
}

void Ball::handleInput(float deltaTime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	const float rotationSpeed = 0.1f * deltaTime;

	
	if (keystate[SDL_SCANCODE_LEFT])
	{
		RotateLeft(rotationSpeed);
	}
	if (keystate[SDL_SCANCODE_RIGHT])
	{
		RotateRight(rotationSpeed);
	}
}
