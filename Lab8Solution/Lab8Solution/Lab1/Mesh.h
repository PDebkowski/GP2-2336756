#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include <glm/gtx/transform.hpp>
#include <SDL/SDL.h>

struct Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& texCoord)
	{
		this->position = position;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &position; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Sphere
{
public:

	Sphere() : pos(glm::vec3(0.0f)), radius(0.0f) {}

	Sphere(glm::vec3& pos, float radius)
	{
		this->pos = pos;
		this->radius = radius;
	}

	glm::vec3 GetPos() { return pos; }
	float GetRadius() { return radius; }

	void SetPos(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void DrawVertexes();
	void LoadVertices(Vertex* vertices, unsigned int numVertices);
	void Draw();
	void Initialize(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void LoadModel(const std::string& filename);
	void InitializeModel(const IndexedModel& model);
	void UpdateSphereData(glm::vec3 pos, float radius);
	glm::vec3 GetSpherePos() { return meshSphere.GetPos(); }
	float GetSphereRadius() { return meshSphere.GetRadius(); }
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	void SetPosition(const glm::vec3& newPos);
	void SetRotation(const glm::vec3& newRot);
	void SetScale(const glm::vec3& newScale);
private:

	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere meshSphere;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};