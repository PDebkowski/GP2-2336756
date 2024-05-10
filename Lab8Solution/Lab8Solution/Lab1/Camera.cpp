#include "Camera.h"

Camera::Camera() {}

	void Camera::InitializeCamera(const glm::vec3& position, float fov, float aspect, float nearClip, float farClip)
	{
		this->position = position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->right = glm::vec3(1.0f, 0.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	glm::vec3 Camera::GetPosition() const
	{
		return this->position;
	}

	glm::mat4 Camera::GetViewProjection() const
	{
		return projection * glm::lookAt(position, position + forward, up);
	}

	glm::mat4 Camera::GetProjection() const
	{
		return projection;
	}

	glm::mat4 Camera::GetView() const
	{
		return glm::lookAt(position, position + forward, up);
	}

	void Camera::SetLook(glm::vec3 modelPos)
	{
		forward = glm::vec3(glm::normalize(modelPos - position));
	}

	void Camera::MoveForward(float amt)
	{
		position += forward * amt;
	}

	void Camera::MoveRight(float amt)
	{
		position += right * amt;
	}

	void Camera::MoveLeft(float amt)
	{
		position -= right * amt;
	}

	void Camera::MoveBackward(float amt)
	{
		position -= forward * amt;
	}

	void Camera::RotateRight(float amt)
	{
		position += glm::cross(up, forward) * amt;
	}

	void Camera::RotateLeft(float amt)
	{
		position -= glm::cross(up, forward) * amt;
	}

	void Camera::Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void Camera::RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

	void Camera::HandleInput(float deltaTime)
	{
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		const float cameraSpeed = 0.1f * deltaTime;
		const float rotationSpeed = 0.1f * deltaTime;

		if (keystate[SDL_SCANCODE_W])
		{
			MoveForward(cameraSpeed);
		}
		if (keystate[SDL_SCANCODE_S])
		{
			MoveBackward(cameraSpeed);
		}
		if (keystate[SDL_SCANCODE_A])
		{
			RotateLeft(rotationSpeed);
		}
		if (keystate[SDL_SCANCODE_D])
		{
			RotateRight(rotationSpeed);
		}
	}

