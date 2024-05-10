#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <SDL/SDL.h>

class Camera
{
public:
	Camera();
	void InitializeCamera(const glm::vec3& position, float fov, float aspect, float nearClip, float farClip);
	glm::vec3 GetPosition() const;
	glm::mat4 GetViewProjection() const;
	glm::mat4 GetProjection() const;
	glm::mat4 GetView() const;
	void SetLook(glm::vec3 modelPos);
	void MoveForward(float amt);
	void MoveRight(float amt);
	void MoveLeft(float amt);
	void MoveBackward(float amt);
	void RotateRight(float amt);
	void RotateLeft(float amt);
	void Pitch(float angle);
	void RotateY(float angle);
	void HandleInput(float deltaTime);

private:
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
};

