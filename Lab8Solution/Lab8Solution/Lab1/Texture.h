#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture();
	
	void Load(const std::string& fileName);
	void LoadNormals(const std::string& fileName);
	void Bind(unsigned int unit); // bind upto 32 textures
	GLuint GetID() { return textureHandler; }
	~Texture();

protected:
private:

	GLuint textureHandler;
};

